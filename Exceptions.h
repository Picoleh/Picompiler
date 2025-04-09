#pragma once
#include<iostream>
using namespace std;

#define RESET   "\033[0m"    // Reseta para a cor padrão
#define RED     "\033[31m"   // Cor vermelha

class Exceptions{
private:
    
public:
    static void showError(int tipo, int linha, string atomo);
};
