#include "Analex.h"

const vector<char> LETRAS = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
const vector<char> DIGITOS = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
const vector<string> SIMBOLOS_ESPECIAIS = {".", ";", ",", "(", ")", ":", "=", "<", ">", "+", "-", "*", ":=", "(*", "*)"};
const vector<string> PALAVRAS_RESERVADAS = {"program", "label", "var", "procedure", "function", "begin", "end", "if", "then", "else", "while", "do", "or", "and",
     "div", "not", "read", "write", "integer"};
const vector<string> SIMBOLOS_COMUNS = {" ", "", "\t", "\n"};
map<string,string> TOKENS = {{".","pt"}, {";","ptvig"}, {",","vig"}, {"(","ap"}, {")","fp"}, {":","dpt"}, {"=", "ig"}, {"+","soma"}, {"-", "menos"}, {"*", "multi"},
 {":=", "atrib"}, {"<=", "<="}, {">=", ">="}, {"program", "prog"}, {"label", "lbl"}, {"var", "v"}, {"integer", "int"}, {"procedure", "proc"}, {"read", "rd"},
 {"write", "wrt"}, {"function", "fn"}, {"begin", "beg"}, {"end", "end"}, {"if", "if"},
 {"then", "then"}, {"else", "el"}, {"while", "while"}, {"do", "do"}, {"or", "or"}, {"and", "and"}, {"div", "/"}, {"not", "not"}};

vector<string> TOKENS_ID;
ifstream arquivo;
ofstream arquivoSaida;

int Analex::getPosInVector(string chave, vector<string> v){
    auto it = find(v.begin(), v.end(), chave);
    if (it != v.end())
        return distance(v.begin(), it);
    return -1;
}

string Analex::getToken(int tipo, string atomo){
    switch (tipo){
    case 0:  // Simbolos especiais
        return TOKENS[atomo];
        break;
    case 1:{ // Identificadores
        int pos = getPosInVector(atomo, TOKENS_ID);
        if(pos != -1)
            return "id" + to_string(pos);
        else{
            TOKENS_ID.push_back(atomo);
            return "id" + to_string(TOKENS_ID.size()-1);
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

void Analex::showError(int tipo, int linha){
    switch (tipo)
    {
    case 0: // Simbolo desconhecido
        cerr << "Error: Simbolo desconhecido\nLinha: " << linha << "\n";
        break;
    case 1: // Identificador ou numero mal formado
        cerr << "Error: identificador ou numero mal formado\nLinha: " << linha << "\n";
        break;
    default:
        break;
    }
}

void Analex::analisar(){
    string nomeArquivo = "Trab1_Compiladores.txt";
    arquivo.open(nomeArquivo);

    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo de entrada!\n";
        return;
    }

    arquivoSaida.open("saida.txt");
    if (!arquivoSaida) {
        cerr << "Erro ao abrir o arquivo de saida!\n";
        return;
    }

    int linha = 1;
    string simbolo = proximoSimbolo();
    while(!arquivo.eof()){
        string atomo = "";

        if(pertence(simbolo,SIMBOLOS_ESPECIAIS)){
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
        else if(pertence(simbolo, LETRAS)){
            while(pertence(simbolo, LETRAS) || pertence(simbolo,DIGITOS)){
                atomo += simbolo;
                simbolo = proximoSimbolo();
            }
            if(pertence(atomo, PALAVRAS_RESERVADAS))
                arquivoSaida << getToken(0, atomo) << " ";
            else
                arquivoSaida << getToken(1, atomo) << " ";
        }
        else if(pertence(simbolo, DIGITOS)){
            while(pertence(simbolo, DIGITOS)){
                atomo += simbolo;
                simbolo = proximoSimbolo();
            }

            if(pertence(simbolo, LETRAS))
                showError(1,linha);
            
            arquivoSaida << getToken(2, atomo) << " ";
        }
        else if(pertence(simbolo, SIMBOLOS_COMUNS)){
            if(simbolo == "\n")
                linha++;
            if(simbolo != " ")
                arquivoSaida << simbolo;
            simbolo = proximoSimbolo();
        }
        else{
            showError(0, linha);
            simbolo = proximoSimbolo();
        }

    }

    arquivo.close();
    arquivoSaida.close();
}
