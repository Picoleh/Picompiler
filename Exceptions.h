#pragma once
#include<iostream>
using namespace std;

#define RESET   "\033[0m"    // Reseta para a cor padrão
#define RED     "\033[31m"   // Cor vermelha
#define GREEN   "\033[32m"   // Cor vermelha

class Exceptions{
private:
    
public:
    static void showLexicalError(int tipo, int linha, string atomo);
    static void showSyntaxError(int linha, string atomo, string expected);
};
