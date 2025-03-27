#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;

const vector<char> LETRAS = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
const vector<char> DIGITOS = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
const vector<string> SIMBOLOS_ESPECIAIS = {".", ";", ",", "(", ")", ":", "=", "<", ">", "+", "-", "*", ":=", "(*", "*)"};
const vector<string> PALAVRAS_RESERVADAS = {"program", "label", "var", "procedure", "function", "begin", "end", "if", "then", "else", "while", "do", "or", "and", "div", "not"};
ifstream arquivo;


bool pertence(string simbolo, const vector<string> conjunto){
    return (find(conjunto.begin(), conjunto.end(), simbolo) != conjunto.end());
}

bool pertence(string simbolo, const vector<char> conjunto){
    char c = simbolo[0];
    return (find(conjunto.begin(), conjunto.end(), c) != conjunto.end());
}

string proximoSimbolo(){
    return string(1,tolower(static_cast<char>(arquivo.get())));
}

void showError(int tipo, int linha){
    switch (tipo)
    {
    case 0: // Simbolo desconhecido
        cerr << "Error: Simbolo desconhecido\nLinha: " << linha << "\n";
        break;
    case 1: // Identificador ou numero mal formado
        cerr << "Error: identificador ou numero mal formado\nLinha" << linha << "\n";
    default:
        break;
    }
}

void analisadorLexico(){
    int linha = 0;
    while(!arquivo.eof()){
        string atomo = "";
        string simbolo = proximoSimbolo();

        while(simbolo == "\n"){
            simbolo = proximoSimbolo();
            linha++;
        }

        if(pertence(simbolo,SIMBOLOS_ESPECIAIS)){
            atomo = simbolo;
            simbolo = proximoSimbolo();
            if(atomo == ":" && simbolo == "="){
                atomo = ":=";
                simbolo = proximoSimbolo();
            }

            // get Token(atomo);
        }
        else if(pertence(simbolo, LETRAS)){
            while(pertence(simbolo, LETRAS) || pertence(simbolo,DIGITOS)){
                atomo += simbolo;
                simbolo = proximoSimbolo();
            }
            if(pertence(atomo, PALAVRAS_RESERVADAS))
                //getToken pal
            else
                // get Token id
        }
        else if(pertence(simbolo, DIGITOS)){
            while(pertence(simbolo, DIGITOS)){
                atomo += simbolo;
                simbolo = proximoSimbolo();
            }

            if(pertence(simbolo, LETRAS))
                showError(1,linha);
            
            // get Token num
        }
        else{
            showError(0, linha);
        }
    }
}

int main(){
    string nomeArquivo = "teste.txt";
    arquivo.open(nomeArquivo);

    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo!\n";
        return -1;
    }

    analisadorLexico();

    arquivo.close();

    return 0;
}