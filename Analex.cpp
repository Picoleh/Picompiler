#include "Analex.h"
#include "Exceptions.h"
#include "Constantes.h"

int Analex::getPosInVector(string chave, vector<string> v){
    auto it = find(v.begin(), v.end(), chave);
    if (it != v.end())
        return distance(v.begin(), it);
    return -1;
}

string Analex::getToken(int tipo, string atomo){
    switch (tipo){
    case 0:  // Simbolos especiais
        return Constantes::TOKENS[atomo];
        break;
    case 1:{ // Identificadores
        int pos = getPosInVector(atomo, Constantes::TOKENS_ID);
        if(pos != -1)
            return "id" + to_string(pos);
        else{
            Constantes::TOKENS_ID.push_back(atomo);
            return "id" + to_string(Constantes::TOKENS_ID.size()-1);
        }
        break;
    }
    case 2: // Numeros
        return "num" + atomo;
        break;
    default:
        break;
    }

    return "";
}

bool Analex::pertence(string simbolo, const vector<string> conjunto){
    return (find(conjunto.begin(), conjunto.end(), simbolo) != conjunto.end());
}

bool Analex::pertence(string simbolo, const vector<char> conjunto){
    char c = simbolo[0];
    return (find(conjunto.begin(), conjunto.end(), c) != conjunto.end());
}

string Analex::proximoSimbolo(){
    return string(1,tolower(static_cast<char>(arquivo.get())));
}

void Analex::analisar(string caminhoArquivo){

    if(!openFiles(caminhoArquivo))
        return;

    int linha = 1;
    string simbolo = proximoSimbolo();
    while(!arquivo.eof()){
        string atomo = "";

        if(pertence(simbolo,Constantes::SIMBOLOS_ESPECIAIS)){
            atomo = simbolo;
            simbolo = proximoSimbolo();
            if(atomo == ":" && simbolo == "="){
                atomo = ":=";
                simbolo = proximoSimbolo();
            }

            if((atomo == "<" || atomo == ">") && simbolo == "="){
                atomo = atomo + simbolo;
                simbolo = proximoSimbolo();
            }

            arquivoSaida << getToken(0, atomo) << " ";
        }
        else if(pertence(simbolo, Constantes::LETRAS)){
            while(pertence(simbolo, Constantes::LETRAS) || pertence(simbolo, Constantes::DIGITOS)){
                atomo += simbolo;
                simbolo = proximoSimbolo();
            }
            if(pertence(atomo, Constantes::PALAVRAS_RESERVADAS))
                arquivoSaida << getToken(0, atomo) << " ";
            else
                arquivoSaida << getToken(1, atomo) << " ";
        }
        else if(pertence(simbolo, Constantes::DIGITOS)){
            while(pertence(simbolo, Constantes::DIGITOS)){
                atomo += simbolo;
                simbolo = proximoSimbolo();
            }

            if(pertence(simbolo, Constantes::LETRAS))
                Exceptions::showError(1,linha, atomo + simbolo);
            
            arquivoSaida << getToken(2, atomo) << " ";
        }
        else if(pertence(simbolo, Constantes::SIMBOLOS_COMUNS)){
            if(simbolo == "\n")
                linha++;
            if(simbolo != " ")
                arquivoSaida << simbolo;
            simbolo = proximoSimbolo();
        }
        else{
            Exceptions::showError(0, linha, atomo + simbolo);
            simbolo = proximoSimbolo();
        }

    }
}

bool Analex::openFiles(string caminhoArquivo){

    arquivo.open(caminhoArquivo);

    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo de entrada!\n";
        return false;
    }

    arquivoSaida.open("saidaAnalex.txt");
    if (!arquivoSaida) {
        cerr << "Erro ao abrir o arquivo de saida!\n";
        return false;
    }

    return true;
}

void Analex::closeFiles(){
    arquivo.close();
    arquivoSaida.close();
}