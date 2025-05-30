#include "AnaSint.h"
#include "Exceptions.h"
#include "Constantes.h"

void AnaSint::programa(){
    proximoAtomo();
    if(atomo == "prog"){
        identificador();

        proximoAtomo();

        if(atomo == ";"){
            bloco();
            proximoAtomo();
            if(atomo == "."){
                return;
            }
            else
                Exceptions::showError(2,linha,atomo);
        }
        else
            Exceptions::showError(2,linha,atomo);
    }
    else
        Exceptions::showError(2,linha,atomo);
}

void AnaSint::bloco(){
    proximoAtomo();
}

void AnaSint::parteDeclaracaoVariavies(){
    if(atomo == "v"){
        while(declaracaoVariaveis()){
            proximoAtomo();
            if(atomo != ";")
                Exceptions::showError(2,linha,atomo);
        }
    }
}

bool AnaSint::declaracaoVariaveis(){
    listaIdentificadores();
    proximoAtomo();
    if(atomo == ":"){
        proximoAtomo();
        if(atomo != "int" && atomo != "bool"){
            Exceptions::showError(2,linha,atomo);
            return false;
        }
    }
    else
        return false;

    return true;
}

void AnaSint::listaIdentificadores(){
    identificador();
    proximoAtomo();
    while(atomo == ","){
        identificador();
        proximoAtomo();
    }
}

void AnaSint::identificador(){
    if(!pertence(atomo, Constantes::TOKENS_ID)){
    }
    else{
        Exceptions::showError(2,linha,atomo);
    }
}

void AnaSint::proximoAtomo(){
    string aux = "";
    char c;
    while(c = static_cast<char>(arquivo.get()) != ' '){
        if(c == '\n'){
            linha++;
            break;
        }
        aux += string(1,c);
    }

    atomo = aux;
}

void AnaSint::analisar(string caminhoArquivo){
    
    if(!openFile(caminhoArquivo))
        return;

    linha = 1;
    programa();
}

bool AnaSint::pertence(string simbolo, const vector<string> conjunto){
    return (find(conjunto.begin(), conjunto.end(), simbolo) != conjunto.end());
}

bool AnaSint::openFile(string caminhoArquivo){
    arquivo.open(caminhoArquivo);

    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo de entrada!\n";
        return false;
    }

    return true;
}