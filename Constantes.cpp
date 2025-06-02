#include "Constantes.h"

namespace Constantes {
    const vector<char> LETRAS = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    const vector<char> DIGITOS = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    const vector<string> SIMBOLOS_ESPECIAIS = {".", ";", ",", "(", ")", ":", "=", "<", ">", "+", "-", "*", ":=", "(*", "*)"};
    const vector<string> PALAVRAS_RESERVADAS = {"program", "label", "var", "procedure", "function", "begin", "end", "if", "then", "else", "while", "do", "or", "and",
     "div", "not", "read", "write", "integer", "boolean"};
    const vector<string> TOKENS_RESERVADOS = {"prog", "lbl", "v", "int", "bool", "proc", "rd", "wrt", "fn", "beg", "end", "if", "then", "el", "while", "do", "or", "and", "/", "not"};
    const vector<string> SIMBOLOS_COMUNS = {" ", "", "\t", "\n"};

    map<string,string> TOKENS = {
        {".","."}, {";",";"}, {",",","}, {"(","("}, {")",")"}, {":",":"}, {"=", "="}, {"+","+"}, {"-", "-"}, {"*", "*"},
        {":=", ":="}, {"<=", "<="}, {">=", ">="}, {"program", "prog"}, {"label", "lbl"}, {"var", "v"}, {"integer", "int"},
        {"boolean", "bool"} ,{"procedure", "proc"}, {"read", "rd"}, {"write", "wrt"}, {"function", "fn"}, {"begin", "beg"},
        {"end", "end"}, {"if", "if"}, {"then", "then"}, {"else", "el"}, {"while", "while"}, {"do", "do"}, {"or", "or"},
        {"and", "and"}, {"div", "/"}, {"not", "not"}
    };

    vector<string> TOKENS_ID;
    vector<string> IDS;
}