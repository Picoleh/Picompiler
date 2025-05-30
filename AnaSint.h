#pragma once
#include <iostream>
#include <fstream>
#include<string>
#include<vector>
#include <algorithm>
using namespace std;

class AnaSint{
private:
    ifstream arquivo;
    string atomo;
    int linha;
    void proximoAtomo();
    void programa();
    void bloco();
    void parteDeclaracaoVariavies();
    bool declaracaoVariaveis();
    void listaIdentificadores();
    void identificador();
    void letra();
    void digito();
    bool pertence(string simbolo, const vector<string> conjunto);
    bool openFile(string caminhoArquivo);
public:
    void analisar(string caminhoArquivo);
};