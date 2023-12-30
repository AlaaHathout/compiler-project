#include <bits/stdc++.h>
using namespace std;

int main()
{
    cout << "Enter the string: ";
    string s; getline(cin, s);
    s += '<';

    cout << "\nEnter the grammar without any spaces:\n";
    string rule;
    vector<string> grammar;
    set<char> terminals, non_terminals;
    map<pair<char, char>, string> replaces;

    // Enter each rule and get its replaces
    while(cin >> rule){
        string str = "";
        int idx = 3;
        for(int i=3; i<(int)rule.length(); i++){
            if(rule[i] == '|'){
                reverse(str.begin(), str.end());
                replaces[{rule[0], rule[idx]}] = str;
                str = "";
                idx = i + 1;
            }
            else str += rule[i];
        }
        reverse(str.begin(), str.end());
        replaces[{rule[0], rule[idx]}] = str;
        grammar.push_back(rule);
        for(int i=0; i<(int)rule.length(); i++){
            if(rule[i] == '-' || rule[i] == '>' || rule[i] == '!') continue;
            if(rule[i] >= 'A' && rule[i] <= 'Z') non_terminals.insert(rule[i]);
            else terminals.insert(rule[i]);
        }
    }

    // < : end marker,   . : bottom of stack,   ! : null
    map<pair<char, char>, string> table;
    map<pair<char, char>, string> reps;
    map<pair<char, char>, int> null_mp;

    // full the tabel
    for(int i=0; i<(int)grammar.size(); i++){
        string cur_rule = grammar[i];
        for(int j=0; j<(int)cur_rule.length(); j++){
            if(cur_rule[j] == '!'){
                for(int k=0; k<(int)grammar.size(); k++){
                    for(int m=3; m<(int)grammar[k].length(); m++){
                        if(grammar[k][m] == cur_rule[0]){
                            if(m + 1 < (int)grammar[k].length() && (grammar[k][m+1] >= 'A' && grammar[k][m+1] <= 'Z')){
                                for(auto it=replaces.begin(); it!=replaces.end(); it++){
                                    if((it->first).first == grammar[k][m+1]){
                                        table[{cur_rule[0], (it->first).second}] = "pop retain";
                                        null_mp[{cur_rule[0], (it->first).second}] = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    table[{'.', '<'}] = "accept";
    for(auto it=terminals.begin(); it!=terminals.end(); it++) table[{'.', *it}] = "reject";
    for(auto it=non_terminals.begin(); it!=non_terminals.end(); it++) table[{*it, '<'}] = "reject";
    for(auto it=terminals.begin(); it!=terminals.end(); it++) table[{*it, '<'}] = "reject";

    for(auto it1=terminals.begin(); it1!=terminals.end(); it1++){
        for(auto it2=terminals.begin(); it2!=terminals.end(); it2++){
            if(*it1 == *it2) table[{*it1, *it2}] = "pop advance";
            else table[{*it1, *it2}] = "reject";
        }
    }

    for(auto it1=non_terminals.begin(); it1!=non_terminals.end(); it1++){
        for(auto it2=terminals.begin(); it2!=terminals.end(); it2++){
            bool f = 0;
            for(auto it=replaces.begin(); it!=replaces.end(); it++){
                if((it->first).first == *it1 && (it->first).second == *it2){
                    table[{*it1, *it2}] = "rep (" + (it -> second) + ") retain";
                    reps[{*it1, *it2}] = (it -> second);
                    f = 1;
                    break;
                }
            }
            if(!f){
                if(null_mp[{*it1, *it2}]) continue;
                table[{*it1, *it2}] = "reject";
            }
        }
    }

    // check if the string is accepted or rejected
    stack<char> st;
    st.push('.');
    st.push('S');
    int n = (int)s.length(), idx = 0;
    while(idx < n){
        string stored_str = table[{st.top(), s[idx]}];
        if(stored_str.find("rep") != -1){
            string replaced_str = reps[{st.top(), s[idx]}];
            st.pop();
            for(int i=0; i<(int)replaced_str.length(); i++) st.push(replaced_str[i]);
        }
        else if(stored_str == "pop retain") st.pop();
        else if(stored_str == "pop advance"){
            st.pop();
            idx++;
        }
        else if(stored_str == "reject"){
            cout << "Reject";
            return 0;
        }
        else if(stored_str == "accept"){
            cout << "Accept";
            return 0;
        }
    }
    cout << "Reject";

    return 0;
}
