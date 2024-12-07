//
// Created by 马宸泽 on 2024/10/21.
//

#include "APIOfLexical_debugver.h"
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <utility>
using namespace std;

bool hasBeenCommentd = false;
vector<pair<string, string> > outputd;

void DB::getpair(string first, string second) {
    pair<string, string> answer;
    answer.first = first;
    answer.second = second;
    outputd.push_back(answer);
}

string keyWordd[26] = { "void", "int", "char", "float", "double", "bool", "string" \
                   "long", "short", "signed", "unsigned",\
                   "const", "inline",\
                   "for", "while", "if", "else",\
                   "switch", "case", "default", "break", "continue", "return",\
                   "main", "include",\
                   "struct",\
                   "std" };
char whitespaced[] = { ' ', '\t', '\n', '\r' };

//There is only one single operator, '~'
char doubleOperatord[] = { '+', '-', '*', '/', '%', '=', '!', '>', '<', '&', '|', '^' };

//There are two others: ' and ", cannot be written in the array
char delimiterd[] = { '(', ')', '[', ']', '{', '}', ',', ';', '?', '#', ':' };



// Declare the position and peek of the dealing input
bool DB::isKeyWord(string word) {
    for (int i = 0; i < 26; i++) {
        if (word == keyWordd[i]) {
            return true;
        }
    }

    return false;
}

bool DB::isComment(string& input, int pos, char peek, bool& hasBeenCommentd) {
	if (pos >= input.size() - 1) {
		return false;
	}
    char next = input[pos + 1];
    char last = input[input.size() - 1];
    char ll = input[input.size() - 2];
    if (peek == '/' && next == '/') {
        return true;
    }
    else if (peek == '/' && next == '*') {

        if (!(last == '/' && ll == '*')) {
            hasBeenCommentd == true;
        }
        return true;
    }
    else if (hasBeenCommentd) {
        if (last == '/' && ll == '*') {
            hasBeenCommentd = false;
        }
        return true;
    }

    return false;
}

bool DB::isWhiteSpace(char ch) {
    for (int i = 0; i < 4; i++) {
        if (ch == whitespaced[i]) {
            return true;
        }
    }
    return false;
}

bool DB::isLetter(char ch) {
	if (ch == '.') {
		return true;
	}
    else if (ch >= 'A' && ch <= 'Z') {
        return true;
    }
    else if (ch >= 'a' && ch <= 'z') {
        return true;
    }
    else if (ch == '_') {
        return true;
    }
    return false;

}

bool DB::isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

bool DB::isOperator(char ch) {
    if (ch == '~') {
        return true;
    }

    for (int i = 0; i < 12; i++) {
        if (ch == doubleOperatord[i]) {
            return true;
        }
    }
    return false;
}

bool DB::isDelimiter(char ch) {
    for (int i = 0; i < 11; i++) {
        if (ch == delimiterd[i]) {
            return true;
        }
    }
    return false;
}

bool DB::isString(char ch) {
    return (ch == '"');
}

bool DB::isChar(char ch) {
    return (ch == '\'');
}



void DB::dealWithLetter(string& input, int& pos, char peek) {
    string str = "";
    while (isLetter(peek) || isDigit(peek)) {
        if (pos >= input.length()) {
            pos += 1;
            break;
        }
        else {
            str += peek;
            pos += 1;
            peek = input[pos];
        }
    }

    if (isKeyWord(str)) {
        getpair("KeyWord", str);
    }
    else if (str == "true" || str == "false") {
        getpair("BoolLiteral", str);
    }
    else {
        getpair("IDEN", str);
    }

}

void DB::dealWithDigit(string& input, int& pos, char peek) {
    string str = "";
    string type = "int";
    while (isDigit(peek) || peek == '.') {
        if (pos >= input.length()) {
            pos += 1;
            break;
        }
        else {
            str += peek;
            pos += 1;
            peek = input[pos];
        }
    }
    getpair("NUM", str);
}

void DB::dealWithOperator(string& input, int& pos, char peek) {
    string str = "";
    str += peek;
    if (peek == '~' || pos >= input.length()) {
        getpair("OP", "~");
        pos += 1;
        return;
    }

    //Deal with the double operator
    char next = input[pos + 1];
    if (next == '=') {
        str += "=";
        getpair("OP", str);
        pos++;
    }
    else if (next == peek) {
        str += peek;
        getpair("OP", str);
        pos++;
    }
    else {
        getpair("OP", str);
    }
    pos++;
    return;
}

void DB::dealWithDelimiter(int& pos, char peek) {
    pos += 1;
    string str = "";
    str += peek;
    getpair("SEP", str);
}

void DB::dealWithString(string& input, int& pos, char peek) {
    string str = "";
    pos++;
    peek = input[pos];
    while (peek != '"') {
        str += peek;
        pos += 1;
        peek = input[pos];
    }
    pos += 1;
    getpair("STR", str);
}

void DB::dealWithChar(string& input, int& pos, char peek) {
    string str = "";
    str += input[pos + 1];
    pos += 3;
    getpair("CHAR", str);
}


void DB::words(string input, bool& hasBeenCommentd) {
    if (input.length() == 0) {
        return;
    }


    int pos = 0;
    char peek;
    while (pos <= input.length() - 1) {
        peek = input[pos];
        if (isWhiteSpace(peek)) { pos += 1; }
        else if (isComment(input, pos, peek, hasBeenCommentd)) {
            return;
        }
        else if (isLetter(peek)) {
            dealWithLetter(input, pos, peek);
        }
        else if (isDigit(peek)) {
            dealWithDigit(input, pos, peek);
        }
        else if (isOperator(peek)) {
            dealWithOperator(input, pos, peek);
        }
        else if (isDelimiter(peek)) {
            dealWithDelimiter(pos, peek);
        }
        else if (isString(peek)) {
            dealWithString(input, pos, peek);
        }
        else if (isChar(peek)) {
            dealWithChar(input, pos, peek);
        }
    }
}

vector<pair<string, string> > DB::gettoken(string filename) {
    fstream file;
    string line;
    int l = 0;
    file.open(filename.c_str());
    if (!file.is_open()) {
        // cerr << "Error opening file: " << filename << endl;
        return {};
    }
    while (getline(file, line)) {
        getpair("startofline", to_string(++l));
        words(line, hasBeenCommentd);
    }
    file.close();
    return outputd;
}