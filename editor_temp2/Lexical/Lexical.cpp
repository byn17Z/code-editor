#include "Lexical.h"
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <filesystem>
#include <stack>

using namespace std;
using namespace HL;

// Global variable for lexical
vector<pair<int,string> > outputh;

// Global variable for comment
bool hasBeenCommenth = false;

// Global variable for error
bool hasErrorh = false;
int rowh = 1;

struct HL::Error {
    int row;       //The row of the error
    string message;     //Report what is the kind of the error
};

void HL::error(bool& hasError, string errorMessage, int row) {
    Error error1;
    hasError = true;
    error1.message = errorMessage;
    error1.row = row;
    // cout << "At row: " << row << ", " << errorMessage <<  endl;
}

void HL::getpair(int first, string second) {
    pair<int, string> answer;
    answer.first = first;
    answer.second = second;
    outputh.push_back(answer);
}

string keyWordh[27]= {"void", "int", "char", "float", "double", "bool", "string" \
                      "long", "short", "signed", "unsigned",\
                      "const", "inline",\
                      "for", "while", "if", "else",\
                      "switch", "case", "default", "break", "continue", "return",\
                      "struct",\
                      "std", \
                      "using", "namespace", "std"};

char whitespaceh[] = {' ', '\t', '\n', '\r'};

//There is only one single operator, '~'
char doubleOperatorh[] = {'+', '-', '*', '/', '%', '=', '!', '>', '<', '&', '|', '^'};

//There are two others: ' and ", cannot be written in the array
char delimiterh[] = {'.', ',', ';', '?', '#', ':'};

char bracketh[] = {'(', ')', '[', ']', '{', '}'};



// Declare the position and peek of the dealing input
bool HL::isKeyWord(string word) {
    for (const auto & i : keyWordh) {
        if (word == i) {
            return true;
        }
    }

    return false;
}

bool HL::isComment(string& input, int pos, char peek,bool& hasBeenComment) {
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
        getpair(2, input);
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

bool HL::isWhiteSpace(char ch) {
    for (int i = 0; i < 4; i ++) {
        if (ch == whitespaceh[i]) {
            return true;
        }
    }
    return false;
}

bool HL::isLetter(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return true;
    } else if (ch >= 'a' && ch <= 'z') {
        return true;
    } else if (ch == '_') {
        return true;
    }
    return false;

}

bool HL::isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

bool HL::isOperator(char ch) {
    if (ch == '~') {
        return true;
    }

    for (int i = 0; i < 12; i++) {
        if (ch == doubleOperatorh[i]) {
            return true;
        }
    }
    return false;
}

bool HL::isDelimiter(char ch) {
    for (int i = 0; i < 11; i++) {
        if (ch == delimiterh[i]) {
            return true;
        }
    }
    return false;
}

bool HL::isBracket(char ch) {
    for (int i = 0; i < 11; i++) {
        if (ch == bracketh[i]) {
            return true;
        }
    }
    return false;
}

bool HL::isString(char ch) {
    return (ch == '"');
}

bool HL::isChar(char ch) {
    return (ch == '\'');
}

void HL::singleGetToken(string& absolutePath);

void HL::dealWithWhiteSpace (int& pos, char peek) {
    if (peek == 32) {
        getpair(14, " ");
    } else if (peek == 9) {
        getpair(16, "\t");
    } else if (peek == 10) {
        getpair(15, "\n");
    } else if (peek == 13) {
        getpair(17, "\r");
    }
    pos += 1;
}

void HL::dealWithInclude(string& input, int& pos, string& filename) {// （已解决）希望可以：1、不处理include文件；2、把#include这一行的代码加进output里，key = "include"     --聂博毅 2024.11.28
    // input.pop_back();
    string str = "#";
    str += input;
    getpair(1, str);
    // getpair("\n", "\n");
    pos = input.length() + 2;
}

void HL::dealWithLetter(string& input, int& pos, char peek, bool& isInclude, string& filename) {
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
        getpair(3, str);
    } else if (str == "true" || str == "false") {
        getpair(4, str);
    } else if (str == "cout") {
        getpair(5, str);
    } else if (str == "cin") {
        getpair(6, str);
    } else {
        getpair(7, str);
    }
}

void HL::dealWithDigit(string& input, int& pos, char peek) {
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
    getpair(11, str);
}

void HL::dealWithComment(string& input, int& pos, char peek) {
    char next = input[pos + 1];
    // input.pop_back();
    if (peek == '/' && next == '/') {
        string str =input.substr(pos);
        getpair(2, str);
        // getpair("\n", "\n");
        pos = input.length() + 2;
        return;
    }

    hasBeenCommenth = true;
    string str;
    while (pos < input.length()) {
        peek = input[pos];
        if (peek == '*') {
            next = input[pos + 1];
            if (next == '/') {
                hasBeenCommenth = false;
                str += "*/";
                pos += 2;
                getpair(2, str);
                // input += '\n';
                return;
            }
        }
        str += peek;
        pos++;
    }
    getpair(2, str);
}

void HL::dealWithOperator(string& input, int& pos, char peek) {
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
        getpair(10, "~");
        pos += 1;
        return;
    }

    //Deal with the double operator
    char next = input[pos + 1];
    if (next == '=' && pos != input.size()) {
        str += "=";
        getpair(10, str);
        pos ++;
    } else if (next == peek && pos != input.size()) {
        str += peek;
        getpair(10, str);
        pos ++;
    } else {
        getpair(10, str);
    }
    pos ++;
}

void HL::dealWithDelimiter(int& pos, char peek) {
    pos += 1;
    string str;
    str += peek;
    if (str != "#") {
        getpair(8, str);
    }
}

void HL::dealWithBracket(int& pos, char peek) {
    pos += 1;
    string str;
    str += peek;
    getpair(9, str);
}

void HL::dealWithString(string&input, int&pos, char peek) {
    string str = "";
    if (pos == input.size() - 1) {
        getpair(12, "");
        pos += 1;
        string message = "You can't put \" at the end of the line.";
        error(hasErrorh, message, rowh);
        return;
    }
    pos++;
    peek = input[pos];
    while (peek != '"' && pos < input.length()-1) {        // （已解决）可能出现一行内找不到另一个 " 的可能性，这一行结束还找不到的话要跳出循环，并报错    --聂博毅 2024.11.28
        str += peek;
        pos += 1;
        peek = input[pos];
    }

    if (peek != '"' && pos == input.length()-1) {
        str += peek;
        string message = "There should be another \" for the string";
        error(hasErrorh, message, rowh);
    }
    pos += 1;
    getpair(12, str);
}

void HL::dealWithChar(string&input, int&pos, char peek) {
    if (pos >= input.length()-1) {
        getpair(13, "");
        pos += 1;
        return;
    }
    string str = "";
    str += input[pos + 1];

    if (str == "\\") {
        char curr = input[pos + 2];
        if (curr == 't' || curr == 'n' || curr == 'r' || curr == '\\' || curr == '"' || curr == '\'') {
            str += curr;
            getpair(13, str);
            if (pos + 3 > input.length()-1 || input[pos + 3] != '\'') {
                getpair(13, str);
                pos += 3;
                string message = "There should be another \' for the character";
                error(hasErrorh, message, rowh);
            }
            pos += 4;        // （+4是整个char后面一位，在words中处理）pos+=4后超出index的情况可以处理吗？    --聂博毅 2024.11.28
            return;        // (已解决）这里return之前，最好保证找到另一个 ' ，否则报错    --聂博毅 2024.11.28
        } else {
            getpair(13, "");
            pos += 2;
            string message = "There cannot be two characters in a char. ";
            error(hasErrorh, message, rowh);
            return;
        }
    }

    if (/*pos == input.size()*/ pos + 2 > input.length()-1 || input[pos + 2] != '\'' /*|| pos + 2 < input.length()*/) {        // （已解决）pos+2好像可能超出index？（以及words函数里while条件好像已经保证了pos<input.size()？只是顺便提一嘴）    --聂博毅 2024.11.28
        getpair(13, str);
        pos += 2;
        string message = "There cannot be two characters in a char. ";
        error(hasErrorh, message, rowh);
        return;
    }
    pos += 3;
    getpair(13, str);
}


void HL::words(string input, bool& hasBeenComment, bool& hasError, int row, string& filename) {
    if (input.length() == 0) {
        return;
    }
    bool isInclude;
    int pos = 0;
    char peek;
    while (pos <= input.length() - 1) {
        peek = input[pos];
        if (isWhiteSpace(peek)) {
            dealWithWhiteSpace(pos, peek);
        }
        else if (hasBeenComment) {    // （已解决）希望可以把comment里的内容也加进output里，key="comment"     --聂博毅 2024.11.28
            dealWithComment(input, pos, peek);
        } else if (isLetter(peek)) {
            dealWithLetter(input, pos, peek, isInclude, filename);
        } else if (isDigit(peek)) {
            dealWithDigit(input, pos, peek);
        } else if (isOperator(peek)) {
            dealWithOperator(input, pos, peek);
        } else if (isBracket(peek)) {
            dealWithBracket(pos, peek);
        } else if (isDelimiter(peek)) {
            dealWithDelimiter(pos, peek);
        } else if (isString(peek)) {
            dealWithString(input, pos, peek);
        } else if (isChar(peek)) {
            dealWithChar(input, pos, peek);
        } else {pos++;};

        // if (hasError || isInclude) {
        //     break;
        // }
    }
}

void HL::singleGetToken(string& filename) {
    string line;
    ifstream file(filename);
    if (!file.is_open()) {
        // std::cerr << "Have error opening:  " << filename << std::endl;
        return;
    }
    while (getline(file, line)) {
        // line += '\n';
        words(line, hasBeenCommenth, hasErrorh, rowh, filename);
        getpair(18, "\n");
        // if (hasError) {break;}
        rowh++;
    }
    file.close();
}

vector<pair<int,string> > HL::gettoken(string filename) {
    outputh.clear();
    string originalDir = std::filesystem::current_path().string();
    filesystem::path newDir = std::filesystem::path(filename).parent_path();
    filesystem::current_path(newDir);
    filesystem::path path(filename);
    filename = path.filename().string();
    singleGetToken(filename);
    filesystem::current_path(originalDir);
    return outputh;
}




/*
 * KEYS & COLOR
 * 1include: PURPLE
 * 2comment: GREEN
 * 3KeyWord: BLUE
 * 4BoolLiteral: YELLOW
 * 5Output: PURPLE
 * 6Input: PURPLE
 * 7IDEN: WHITE
 * 8SEP: WHITE
 * 9BKT: YELLOW, PURPLE, BLUE
 * 10OP: WHITE
 * 11NUM: PURPLE
 * 12STR, 13CHAR: ORANGE
 * 14SPACE, 15BSn, 16BSt, 17BSr
 * 18control cahnge of line
 */

string HL::highlightHTML(string filename) {
    vector<pair<int,string> > tokens = gettoken(filename);
    string str = "";
    stack<string> bktStack;

    for (int i = 0; i < tokens.size(); i++) {
        switch(tokens[i].first) {

        case 1: //include: PURPLE
            str += "<span style=\"color: purple;\">";
            str += tokens[i].second;
            str += "</span>";
            break;

        case 2: //comment: GREEN
            str += "<span style=\"color: green;\">";
            str += tokens[i].second;
            str += "</span>";
            break;

        case 3: //KeyWord: BLUE
            str += "<span style=\"color: blue;\">";
            str += tokens[i].second;
            str += "</span>";
            break;

        case 4: //BoolLiteral: YELLOW
            str += "<span style=\"color: yellow;\">";
            str += tokens[i].second;
            str += "</span>";
            break;

        case 5: //Output: PURPLE
            str += "<span style=\"color: purple;\">";
            str += tokens[i].second;
            str += "</span>";
            break;

        case 6: //Input: PURPLE
            str += "<span style=\"color: purple;\">";
            str += tokens[i].second;
            str += "</span>";
            break;

        case 7: //IDEN: WHITE
            str += "<span style=\"color: white;\">";
            str += tokens[i].second;
            str += "</span>";
            break;

        case 8: //SEP: WHITE
            str += "<span style=\"color: white;\">";
            str += tokens[i].second;
            str += "</span>";
            break;

        case 9 : //BKT: YELLOW, PURPLE, BLUE
            str += "<span style=\"color: yellow;\">";
            str += tokens[i].second;
            str += "</span>";
            // if (tokens[i].second == "(" || tokens[i].second == "[" || tokens[i].second == "{") {
            //     bktStack.push(tokens[i].second);
            //     switch(bktStack.size()%3) {
            //     case 1:
            //         str += "<span style=\"color: yellow;\">";
            //         str += tokens[i].second;
            //         str += "</span>";
            //         break;
            //     case 2:
            //         str += "<span style=\"color: purple;\">";
            //         str += tokens[i].second;
            //         str += "</span>";
            //         break;
            //     case 0:
            //         str += "<span style=\"color: blue;\">";
            //         str += tokens[i].second;
            //         str += "</span>";
            //         break;
            //     }
            // } else {
            //     if (
            //         (tokens[i].second == ")" && bktStack.top() == "(") ||
            //         (tokens[i].second == "]" && bktStack.top() == "[") ||
            //         (tokens[i].second == "}" && bktStack.top() == "{")
            //         ) {
            //         switch(bktStack.size()%3) {
            //         case 1:
            //             str += "<span style=\"color: yellow;\">";
            //             str += tokens[i].second;
            //             str += "</span>";
            //         case 2:
            //             str += "<span style=\"color: purple;\">";
            //             str += tokens[i].second;
            //             str += "</span>";
            //         case 0:
            //             str += "<span style=\"color: blue;\">";
            //             str += tokens[i].second;
            //             str += "</span>";
            //         }
            //         bktStack.pop();
            //     } else {
            //         str += "<span style=\"color: yellow;\">";
            //         str += tokens[i].second;
            //         str += "</span>";
            //     }
            // }
            break;

        case 10: //OP: WHITE
            str += "<span style=\"color: white;\">";
            str += tokens[i].second;
            str += "</span>";
            break;

        case 11: //NUM: PURPLE
            str += "<span style=\"color: purple;\">";
            str += tokens[i].second;
            str += "</span>";
            break;

        case 12: //STR: ORANGE
            str += "<span style=\"color: orange;\">";
            str += "\"";
            str += tokens[i].second;
            str += "\"";
            str += "</span>";
            break;

        case 13: //CHAR: ORANGE
            str += "<span style=\"color: orange;\">";
            str += "\'";
            str += tokens[i].second;
            str += "\'";
            str += "</span>";
            break;

        case 14: case 15: case 16: case 17: //SPACE\n\t\r
            str += tokens[i].second;
            // str += " ";
            break;

        case 18: // \n
            str += "<br>";
            break;

        default:
            break;
        }
    }

    return str;
}
