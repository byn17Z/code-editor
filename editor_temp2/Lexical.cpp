/* 
读代码的时候发现一些地方可能有问题，因为编译器和编辑器都可能要处理编辑中的代码，需要较强的鲁棒性，有空的话希望可以继续测试/检查。
还有一些新的需求（highlight相关）：
1、“#include” 行的内容加进output里，key = "include"，不处理include的文件；
2、comment的内容（及前后标识符）加进output里， key = "comment"；如果是 “//” 的，行末的\n提出来作为单独一项\n加入output里；
如果这周没空的话我到时候要用的话就顺便把1、2写了，跟高亮相关的功能优先级可以往后排。
    --commented by 聂博毅 2024.11.28
*/

#include "Lexical.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <filesystem>
using namespace std;

// Global variable for lexical
vector<pair<string,string> > output;

// Global variable for comment
bool hasBeenComment = false;

// Global variable for error
bool hasError = false;
int row = 1;

struct Error {
    int row;       //The row of the error
    string message;     //Report what is the kind of the error
};

void error(bool& hasError, string errorMessage, int row) {
    Error error1;
    hasError = true;
    error1.message = errorMessage;
    error1.row = row;
    cout << "At row: " << row << ", " << errorMessage <<  endl;
}

void getpair(string first, string second) {
    pair<string, string> answer;
    answer.first = first;
    answer.second = second;
    output.push_back(answer);
}

string keyWord[27]= {"void", "int", "char", "float", "double", "bool", "string" \
                   "long", "short", "signed", "unsigned",\
                   "const", "inline",\
                   "for", "while", "if", "else",\
                   "switch", "case", "default", "break", "continue", "return",\
                   "struct",\
                   "std", \
                   "using", "namespace", "std"};

char whitespace[] = {' ', '\t', '\n', '\r'};

//There is only one single operator, '~'
char doubleOperator[] = {'+', '-', '*', '/', '%', '=', '!', '>', '<', '&', '|', '^'};

//There are two others: ' and ", cannot be written in the array
char delimiter[] = {'(', ')', '[', ']', '{', '}', '.', ',', ';', '?', '#', ':'};



// Declare the position and peek of the dealing input
bool isKeyWord(string word) {
    for (const auto & i : keyWord) {
        if (word == i) {
            return true;
        }
    }

    return false;
}

bool isComment(string& input, int pos, char peek,bool& hasBeenComment) {
    int length = input.size();
    if (length == 1) {
        if (hasBeenComment) {
            return true;
        } else {
            return false;
        }
    }
    char next = input[pos + 1];
    char last = input[length - 1];
    char ll = input[length - 2];
    if (peek == '/' && next == '/') {
        input.pop_back();
        getpair("comment", input);
        return true;
    } else if (peek == '/' && next == '*') {

        if (!(last == '/' && ll == '*')) {    // （已解决） " */ " 后可能还有有效代码        --聂博毅 2024.11.28
            hasBeenComment = true;
        }
        return true;
    } else if (hasBeenComment) {
        if (last == '/' && ll == '*') {
            hasBeenComment = false;
        }
        return true;
    }

    return false;
}

bool isWhiteSpace(char ch) {
    for (int i = 0; i < 4; i ++) {
        if (ch == whitespace[i]) {
            return true;
        }
    }
    return false;
}

bool isLetter(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return true;
    } else if (ch >= 'a' && ch <= 'z') {
        return true;
    } else if (ch == '_') {
        return true;
    }
    return false;

}

bool isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

bool isOperator(char ch) {
    if (ch == '~') {
        return true;
    }

    for (int i = 0; i < 12; i++) {
        if (ch == doubleOperator[i]) {
            return true;
        }
    }
    return false;
}

bool isDelimiter(char ch) {
    for (int i = 0; i < 11; i++) {
        if (ch == delimiter[i]) {
            return true;
        }
    }
    return false;
}

bool isString(char ch) {
    return (ch == '"');
}

bool isChar(char ch) {
    return (ch == '\'');
}

void singleGetToken(string& absolutePath);

void dealWithWhiteSpace (char peek) {
    if (peek == 32) {
        getpair(" ", " ");
    } else if (peek == 9) {
        getpair("\t", "\t");
    } else if (peek == 10) {
        getpair("\n", "\n");
    } else if (peek == 13) {
        getpair("\r", "\r");
    }
}

void dealWithInclude(string& input, int& pos, string& filename) {// （已解决）希望可以：1、不处理include文件；2、把#include这一行的代码加进output里，key = "include"     --聂博毅 2024.11.28
    input.pop_back();
    getpair("include", input);
    getpair("\n", "\n");
    pos = input.length() + 2;
}

void dealWithLetter(string& input, int& pos, char peek, bool& isInclude, string& filename) {
    string str;
    while (isLetter(peek) || isDigit(peek)) {
        if (pos >= input.length()) {
            pos += 1;
            break;
        }
        str += peek;
        pos += 1;
        peek = input[pos];
    }

    if (str == "include") {
        isInclude = true;
        dealWithInclude(input, pos, filename);
        return;
    }

    if (isKeyWord(str)) {
        getpair("KeyWord", str);
    } else if (str == "true" || str == "false") {
        getpair("BoolLiteral", str);
    } else if (str == "cout") {
        getpair("Output", str);
    } else if (str == "cin") {
        getpair("Input", str);
    } else {
        getpair("IDEN", str);
    }
}

void dealWithDigit(string& input, int& pos, char peek) {
    string str = "";
    string type = "int";
    while (isDigit(peek) || peek == '.') {
        if (pos >= input.length()) {
            pos += 1;
            break;
        } else {
            str += peek;
            pos += 1;
            peek = input[pos];
        }
    }
    getpair("NUM", str);
}

void dealWithComment(string& input, int& pos, char peek) {
    char next = input[pos + 1];
    input.pop_back();
    if (peek == '/' && next == '/') {
        string str =input.substr(pos);
        getpair("comment", str);
        getpair("\n", "\n");
        pos = input.length() + 2;
        return;
    }

    hasBeenComment = true;
    string str;
    while (pos < input.length()) {
        peek = input[pos];
        if (peek == '*') {
            next = input[pos + 1];
            if (next == '/') {
                hasBeenComment = false;
                str += "*/";
                pos += 2;
                getpair("comment", str);
                input += '\n';
                return;
            }
        }
        str += peek;
        pos++;
    }
    getpair("comment", str);
}

void dealWithOperator(string& input, int& pos, char peek) {
    if (peek == '/') {
        char next1 = input[pos + 1];
        if (next1 == '*' || next1 == '/') {
            dealWithComment(input, pos, peek);
            return;
        }
    }

    string str;
    str += peek;
    if (peek == '~' || pos >= input.length()) {
        getpair("OP", "~");
        pos += 1;
        return;
    }

    //Deal with the double operator
    char next = input[pos + 1];
    if (next == '=' && pos != input.size()) {
        str += "=";
        getpair("OP", str);
        pos ++;
    } else if (next == peek && pos != input.size()) {
        str += peek;
        getpair("OP", str);
        pos ++;
    } else {
        getpair("OP", str);
    }
    pos ++;
}

void dealWithDelimiter(int& pos, char peek) {
    pos += 1;
    string str;
    str += peek;
    if (str != "#") {
        getpair("SEP", str);
    }
}

void dealWithString(string&input, int&pos, char peek) {
    string str = "";
    if (pos == input.size() - 1) {
        string message = "You can't put \" at the end of the line.";
        error(hasError, message, row);
        return;
    }
    pos++;
    peek = input[pos];
    while (peek != '"' && pos < input.length()) {        // （已解决）可能出现一行内找不到另一个 " 的可能性，这一行结束还找不到的话要跳出循环，并报错    --聂博毅 2024.11.28
        str += peek;
        pos += 1;
        peek = input[pos];
    }

    if (peek != '\"') {
        string message = "There should be another \" for the string";
        error(hasError, message, row);
    }
    pos += 1;
    getpair("STR", str);
}

void dealWithChar(string&input, int&pos, char peek) {
    string str = "";
    str += input[pos + 1];
    if (str == "\\") {
        char curr = input[pos + 2];
        if (curr == 't' || curr == 'n' || curr == 'r' || curr == '\\' || curr == '"' || curr == '\'') {
            str += curr;
            getpair("CHAR", str);
            if (input[pos + 3] != '\'') {
                string message = "There should be another \' for the character";
                error(hasError, message, row);
            }
            pos += 4;        // （+4是整个char后面一位，在words中处理）pos+=4后超出index的情况可以处理吗？    --聂博毅 2024.11.28
            return;        // (已解决）这里return之前，最好保证找到另一个 ' ，否则报错    --聂博毅 2024.11.28
        } else {
            string message = "There cannot be two characters in a char. ";
            error(hasError, message, row);
            return;
        }
    }

    if (pos == input.size() || input[pos + 2] != '\'' || pos + 2 < input.length()) {        // （已解决）pos+2好像可能超出index？（以及words函数里while条件好像已经保证了pos<input.size()？只是顺便提一嘴）    --聂博毅 2024.11.28
        string message = "There cannot be two characters in a char. ";
        error(hasError, message, row);
        return;
    }
    pos += 3;
    getpair("CHAR", str);
}


void words(string input, bool& hasBeenComment, bool& hasError, int row, string& filename) {
    if (input.length() == 0) {
        return;
    }
    bool isInclude;
    int pos = 0;
    char peek;
    while (pos <= input.length() - 1) {
        peek = input[pos];
        if (isWhiteSpace(peek)) {
            dealWithWhiteSpace(peek);
            pos += 1;
        }
        else if (hasBeenComment) {    // （已解决）希望可以把comment里的内容也加进output里，key="comment"     --聂博毅 2024.11.28
            dealWithComment(input, pos, peek);
        } else if (isLetter(peek)) {
            dealWithLetter(input, pos, peek, isInclude, filename);
        } else if (isDigit(peek)) {
            dealWithDigit(input, pos, peek);
        } else if (isOperator(peek)) {
            dealWithOperator(input, pos, peek);
        } else if (isDelimiter(peek)) {
            dealWithDelimiter(pos, peek);
        } else if (isString(peek)) {
            dealWithString(input, pos, peek);
        } else if (isChar(peek)) {
            dealWithChar(input, pos, peek);
        }
        if (hasError || isInclude) {
            break;
        }
    }
}

void singleGetToken(string& filename) {
    string line;
    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Have error opening:  " << filename << std::endl;
        return;
    }
    while (getline(file, line)) {
        line += '\n';
        words(line, hasBeenComment, hasError, row, filename);
        if (hasError) {break;}
        row++;
    }
    file.close();
}

vector<pair<string,string> > gettoken(string filename) {
    output.clear();
    string originalDir = std::filesystem::current_path().string();
    filesystem::path newDir = std::filesystem::path(filename).parent_path();
    filesystem::current_path(newDir);
    filesystem::path path(filename);
    filename = path.filename().string();
    singleGetToken(filename);
    filesystem::current_path(originalDir);
    return output;
}