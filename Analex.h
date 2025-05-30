#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include<map>
using namespace std;

class Analex{
    private:
    //vector<string> TOKENS_ID;
    ifstream arquivo;
    ofstream arquivoSaida;
    bool pertence(string simbolo, const vector<string> conjunto);
    bool pertence(string simbolo, const vector<char> conjunto);
    string proximoSimbolo();
    string getToken(int tipo, string atomo);
    int getPosInVector(string chave, vector<string> v);
    bool openFiles(string caminhoArquivo);
    void closeFiles();


    public:
    void analisar(string caminhoArquivo);

};