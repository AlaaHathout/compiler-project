#include <bits/stdc++.h>
using namespace std;

map<char,int>mp;
bool isValidPattern(string pattern){
    for(int i=0;i<(int)pattern.size();i++){
        if(pattern[i]!='+' && pattern[i]!='*' && pattern[i]!='(' && pattern[i]!=')' && !mp[pattern[i]])  return false;
    }
    return (!(pattern[0]=='+' || pattern[0]=='*' || (int)pattern.find("++")!=-1 || (int)pattern.find("**")!=-1 || (int)pattern.find("+*")!=-1 || (int)pattern.find("*+")!=-1));
}

int main()
{
    cout<<"Enter the alphabets: ";
    string alphabets;  getline(cin, alphabets);
    for(int i=0;i<(int)alphabets.size();i++){
        if(alphabets[i]!=' ' && alphabets[i]!=',')  mp[alphabets[i]]++;
    }

    cout<<"Enter a regular expression pattern: ";
    string RE_pattern;  getline(cin, RE_pattern);
    if(!isValidPattern(RE_pattern)){
        cout<<"Invalid regular expression!";
        return 0;
    }
    for(int i=0;i<(int)RE_pattern.size();i++){
        if(RE_pattern[i]=='+')  RE_pattern[i]='|';
    }

    cout<<"Enter an input string: ";
    string input_string;  getline(cin, input_string);

    try{
        regex pattern(RE_pattern);
        if(regex_match(input_string, pattern))  cout<<"The input string matches the pattern";
        else  cout<<"The input string doesn't match the pattern";
    }catch(const regex_error& err){
        cout<<"Invalid regular expression!";
    }

    return 0;
}
