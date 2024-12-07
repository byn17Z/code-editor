#ifndef LEXICAL_H
#define LEXICAL_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <filesystem>
using namespace std;
namespace HL {

// Use the absolute path for the file.
// vector<pair<int,string> > output;
// bool hasBeenComment = false;
// bool hasError = false;
// int row = 1;
struct Error;
void error(bool& hasError, string errorMessage, int row);
void getpair(int first, string second);
// string keyWord[27] = {"void", "int", "char", "float", "double", "bool", "string" \
//                       "long", "short", "signed", "unsigned",\
//                       "const", "inline",\
//                       "for", "while", "if", "else",\
//                       "switch", "case", "default", "break", "continue", "return",\
//                       "struct",\
//                       "std", \
//                       "using", "namespace", "std"};
// char whitespace[] = {' ', '\t', '\n', '\r'};
// char doubleOperator[] = {'+', '-', '*', '/', '%', '=', '!', '>', '<', '&', '|', '^'};
// char delimiter[] = {'.', ',', ';', '?', '#', ':'};
// char bracket[] = {'(', ')', '[', ']', '{', '}'};
bool isKeyWord(string word);
bool isComment(string& input, int pos, char peek,bool& hasBeenComment) ;
bool isWhiteSpace(char ch);
bool isLetter(char ch);
bool isDigit(char ch);
bool isOperator(char ch);
bool isDelimiter(char ch);
bool isBracket(char ch);
bool isString(char ch);
bool isChar(char ch);
void singleGetToken(string& absolutePath);
void dealWithWhiteSpace (int& pos, char peek);
void dealWithInclude(string& input, int& pos, string& filename);
void dealWithLetter(string& input, int& pos, char peek, bool& isInclude, string& filename);
void dealWithDigit(string& input, int& pos, char peek);
void dealWithComment(string& input, int& pos, char peek);
void dealWithOperator(string& input, int& pos, char peek);
void dealWithDelimiter(int& pos, char peek);
void dealWithBracket(int& pos, char peek);
void dealWithString(string&input, int&pos, char peek);
void dealWithChar(string&input, int&pos, char peek);
void words(string input, bool& hasBeenComment, bool& hasError, int row, string& filename);
vector<pair<int,string> > gettoken(string filename);
string highlightHTML(string filename);

}

#endif // WIDGET_H
