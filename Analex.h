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
    bool pertence(string simbolo, const vector<string> conjunto);
    bool pertence(string simbolo, const vector<char> conjunto);
    string proximoSimbolo();
    void showError(int tipo, int linha);
    string getToken(int tipo, string atomo);
    int getPosInVector(string chave, vector<string> v);


    public:
    void analisar();

};