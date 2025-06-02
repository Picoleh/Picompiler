#include "Exceptions.h"

void Exceptions::showLexicalError(int tipo, int linha, string atomo){
    cerr << RED << "Lexical Error:" << RESET;
    switch (tipo){
        case 0: // Simbolo desconhecido
            cerr <<" Simbolo desconhecido\n";
            break;
        case 1: // Identificador ou numero mal formado
            cerr << " Identificador ou numero mal formado\n";
            break;
        default:
            break;
    }

    if(atomo != ""){
        cout << linha << " | " << RED << atomo << RESET << "\n";
    }
}

void Exceptions::showSyntaxError(int linha, string atomo, string expected){
    cerr << RED << "Syntax Error:\n" << RESET;

    cerr << linha << " | " << RED << atomo << RESET << "\n" << "Expected: " << GREEN << expected << RESET << "\n";
}