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
    bool listaIdentificadores();
    void parteDeclaracaoSubRotinas();
    bool declaracaoProcedimento();
    bool declaracaoFuncao();
    void parametrosFormais();
    void secaoParametrosFormais();
    bool comandoComposto();
    bool comando();
    bool comandoSemRotulo();
    bool atribuicao();
    bool chamadaProcedimento();
    bool comandoCondicional();
    bool comandoRepetitivo();
    void listaExpressoes();
    void expressao();
    bool relacao();
    void expressaoSimples();
    bool termo();
    bool fator();
    bool variavel();
    bool chamadaFuncao();
    bool identificador();
    void letra();
    bool numero();
    bool pertence(string simbolo, vector<string> conjunto);
    bool openFile(string caminhoArquivo);
public:
    void analisar(string caminhoArquivo);
};