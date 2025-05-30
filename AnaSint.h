#pragma once
#include <iostream>
#include <fstream>
#include<string>
using namespace std;

class AnaSint{
private:
    char proximoSimbolo();
    void programa();
    void identificador();
    void bloco();
public:
    void analisar(string );
};