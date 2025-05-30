#include "AnaSint.h"
#include "Exceptions.h"

ifstream arquivo;
char simbolo;
int linha;

void AnaSint::programa(){
    string gabarito = "program";
    for(int i=0; i < gabarito.size(); i++){
        if(simbolo != gabarito[i]){
            Exceptions::showError(2,linha,"Sintax Error");
            return;
        }
        simbolo = proximoSimbolo();
    }

    identificador();
    simbolo = proximoSimbolo();
    if(simbolo == ';'){
        bloco();
        simbolo = proximoSimbolo();
        if(simbolo != '.'){
            Exceptions::showError(2, linha, "doideira");
            return;
        }
    }
    else{
        Exceptions::showError(2,linha,"sla vei");
        return;
    }
}

void AnaSint::identificador(){
    
}

void AnaSint::bloco(){
    
}

char AnaSint::proximoSimbolo(){
    char c = static_cast<char>(arquivo.get());
    if(c == '\n'){
        linha++;
        return proximoSimbolo();
    }
    else
        return tolower(c);
}

void AnaSint::analisar(){
    string nomeArquivo = "Trab1_Compiladores.txt";
    arquivo.open(nomeArquivo);

    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo de entrada!\n";
        return;
    }
    linha = 1;
    simbolo = proximoSimbolo();

}