#include <bits/stdc++.h>
using namespace std;

bool is_operator(char c){
    return (c == '=') || (c == '>') || (c == '<') || (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '&') || (c == '|') || (c == '^') || (c == '%') || (c == '?') || (c == '!') || (c == '~');
}

bool is_special_character(char c){
    return (c == '{') || (c == '}') || (c == '(') || (c == ')') || (c == '[') || (c == ']') || (c == '.') || (c == ':') || (c == ';') || (c == ',');
}

bool is_keyword(string s){
    vector<string> kewWords = {"if", "else", "switch", "case", "int", "float", "double", "for", "do", "while", "char", "String", "short", "boolean", "long", "byte", "signed", "unsigned", "void", "return", "break", "continue", "public", "private", "static", "class", "main", "args", "import", "Scanner", "new", "true", "false"};
    for(int k=0; k<(int)kewWords.size(); k++){
        if(s == kewWords[k]) return true;
    }
    return false;
}

int main()
{
    cout << "Enter the expression you want to get its tokens:\n";
    string expression;
    while(getline(cin, expression)){
        int n = (int)expression.length(), i = 0;
        while(i < n){
            char curChar = expression[i];
            if(curChar == '=' && (expression[i+1] == '=' && i + 1 < n)){
                cout << "==   Operator\n";
                i += 2;
            }
            else if(curChar == '<' && (expression[i+1] == '=' && i + 1 < n)){
                cout << "<=   Operator\n";
                i += 2;
            }
            else if(curChar == '>' && (expression[i+1] == '=' && i + 1 < n)){
                cout << ">=   Operator\n";
                i += 2;
            }
            else if(curChar == '!' && (expression[i+1] == '=' && i + 1 < n)){
                cout << "!=   Operator\n";
                i += 2;
            }
            else if(curChar == '/' && (expression[i+1] == '/' && i + 1 < n)) break; // comment
            else if(curChar == '/' && (expression[i+1] == '*' && i + 1 < n)){ /* comment */
                i += 2;
                while(expression[i] != '*') i++;
                i += 2;
            }
            else if(curChar == '\''){ // 'a'
                cout << "\'   Special character\n";
                i++;
                cout << expression[i] << "   Character constant\n";
                i++;
                cout << "\'   Special character\n";
                i++;
            }
            else if(curChar == '\"'){ // "..."
                cout << "\"   Special character\n";
                i++;
                string str = "";
                while(expression[i] != '\"'){
                    str += expression[i];
                    i++;
                }
                cout << str << "   String constant\n";
                cout << "\"   Special character\n";
                i++;
            }
            else if(is_operator(curChar)){
                cout << curChar << "   Operator\n";
                i++;
            }
            else if((curChar >= '0' && curChar <= '9') || curChar == '.'){ // numeric constant
                string num = "";
                num += curChar;
                int j = i + 1; // 5 or 5.5 or 5e3 or 5e+3 or 5e-3
                for(; j<n; j++){
                    if((expression[j] >= '0' && expression[j] <= '9') || expression[j] == '.' || expression[j] == 'e' || ((expression[j] == '+' || expression[j] == '-') && (expression[j-1] == 'e' && j - 1 >= 0))){
                        num += expression[j];
                    }
                    else break;
                }
                i = j;
                cout << num << "   Numeric constant\n";
            }
            else if(is_special_character(curChar)){
                cout << curChar << "   Special character\n";
                i++;
            }
            // keyword, identifier, print, or input
            else if((curChar >= 'a' && curChar <= 'z') || (curChar >= 'A' && curChar <= 'Z') || curChar == '_' || curChar == '$'){
                if(curChar == 'S'){ // print
                    string print_syntaxes[] = {"System.out.println", "System.out.printf", "System.out.print"};
                    bool ok = 0;
                    for(int j=0; j<3; j++){
                        bool f = 1;
                        for(int k=i; k<min((int)print_syntaxes[j].length(), n); k++){
                            if(expression[k] != print_syntaxes[j][k]){
                                f = 0;
                                break;
                            }
                        }
                        if(f){
                            cout << print_syntaxes[j] << "   Keyword\n";
                            i += (int)print_syntaxes[j].length();
                            ok = 1;
                            break;
                        }
                    }
                    if(ok) continue;
                }
                string input_syntax = "System.in"; // input
                int idx = i;
                bool flag = 1;
                for(int j=0; j<(int)input_syntax.length(); j++){
                    if(expression[idx] == input_syntax[j]){
                        idx++;
                        if(idx == n) break;
                    }
                    else{
                        flag = 0;
                        break;
                    }
                }
                if(flag){
                    i += (int)input_syntax.length();
                    cout << input_syntax << "   Keyword\n";
                    continue;
                } // keyword or identifier
                string str = "";
                str += curChar;
                int j = i + 1;
                for(; j<n; j++){
                    if((expression[j] >= 'A' && expression[j] <= 'Z') || (expression[j] >= 'a' && expression[j] <= 'z') || expression[j] == '_' || expression[j] == '$'){
                        str += expression[j];
                    }
                    else break;
                }
                cout << str << (is_keyword(str) ? "   Keyword\n" : "   Identifier\n");
                i = j;
            }
            else i++;
        }
        cout << "\n";
    }

    return 0;
}
