#include "AnaSint.h"
#include "Exceptions.h"
#include "Constantes.h"

void AnaSint::programa(){
    proximoAtomo();
    if(atomo == "prog"){
        proximoAtomo();
        if(identificador()){
            proximoAtomo();
    
            if(atomo == ";"){
                bloco();
                if(atomo == "."){
                    return;
                }
                else
                    Exceptions::showSyntaxError(linha, atomo, ".");
            }
            else
                Exceptions::showSyntaxError(linha, atomo, ";");
        }
        else
            Exceptions::showSyntaxError(linha, atomo, "Identifier");
    }
    else
        Exceptions::showSyntaxError(linha, atomo, "program");
}

void AnaSint::bloco(){
    parteDeclaracaoVariavies();
    parteDeclaracaoSubRotinas();
    comandoComposto();
}

void AnaSint::parteDeclaracaoVariavies(){
    proximoAtomo();
    if(atomo == "v"){
        int qtd = 0;
        while(declaracaoVariaveis()){
            qtd++;
            proximoAtomo();
            if(atomo != ";")
                Exceptions::showSyntaxError(linha,atomo, ";");
        }

        if(qtd == 0)
            Exceptions::showSyntaxError(linha,atomo, "Variable(s) declaration");
    }
}

bool AnaSint::declaracaoVariaveis(){
    proximoAtomo();
    if(listaIdentificadores()){
        // Para sair da função anterior, ja leu-se o proximoAtomo()
        if(atomo == ":"){
            proximoAtomo();
            if(atomo != "int" && atomo != "bool"){
                Exceptions::showSyntaxError(linha,atomo, "primitive type");
                return false;
            }
        }
        else{
            Exceptions::showSyntaxError(linha, atomo, ":");
            return false;
        }
    
        return true;
    }
    else
        return false;
}

bool AnaSint::listaIdentificadores(){
    if(identificador()){
        proximoAtomo();
        while(atomo == ","){
            proximoAtomo();
            if(identificador())
                proximoAtomo();
            else{
                Exceptions::showSyntaxError(linha,atomo, "Identifier");
                return false;
            }
        }
        return true;
    }
    else
        return false;
}

void AnaSint::parteDeclaracaoSubRotinas(){
    bool houveDeclaracaoSub = true;
    while(houveDeclaracaoSub){
        houveDeclaracaoSub = false;
        // Ja leu-se o proximoAtomo()
        if(declaracaoProcedimento()){
            houveDeclaracaoSub = true;
             // Ja leu-se o proximoAtomo()
            if(atomo == ";")
                proximoAtomo();
            else
                Exceptions::showSyntaxError(linha,atomo,";");
        }
        // Ja leu-se o proximoAtomo()
        if(declaracaoFuncao()){
            houveDeclaracaoSub = true;
            proximoAtomo();
            if(atomo == ";")
                proximoAtomo();
            else
                Exceptions::showSyntaxError(linha,atomo,";");
        }
    }
}

bool AnaSint::declaracaoProcedimento(){
    if(atomo == "proc"){
        proximoAtomo();
        if(identificador()){
            parametrosFormais();
            // Para sair da função anterior, ja leu-se o proximoAtomo()
            if(atomo == ";"){
                bloco();
                return true;
            }
            else{
                Exceptions::showSyntaxError(linha,atomo, ";");
                return false;
            }
        }
        else{
            Exceptions::showSyntaxError(linha,atomo,"Identifier");
            return false;
        }
    }
    else
        return false;
}

bool AnaSint::declaracaoFuncao(){
    if(atomo == "func"){
        proximoAtomo();
        if(identificador()){
            parametrosFormais();
            // Para sair da função anterior, ja leu-se o proximoAtomo()
            if(atomo == ":"){
                proximoAtomo();
                if(identificador()){
                    proximoAtomo();
                    if(atomo == ";"){
                        bloco();
                        return true;
                    }
                    else{
                        Exceptions::showSyntaxError(linha, atomo, ";");
                        return false;
                    }
                }
                else{
                    Exceptions::showSyntaxError(linha,atomo,"Identifier");
                    return false;
                }
            }
            else{
                Exceptions::showSyntaxError(linha,atomo,":");
                return false;
            }
        }
        else{
            Exceptions::showSyntaxError(linha,atomo,"Identifier");
            return false;
        }
    }
    else
        return false;
}

void AnaSint::parametrosFormais(){
    proximoAtomo();
    if(atomo == "("){
        secaoParametrosFormais();
        proximoAtomo();
        while(atomo == ";"){
            secaoParametrosFormais();
            proximoAtomo();
        }

        if(atomo == ")")
            proximoAtomo();
        else
            Exceptions::showSyntaxError(linha,atomo,")");
    }
}

void AnaSint::secaoParametrosFormais(){
    proximoAtomo();
    if(atomo == "v")
        proximoAtomo();
    
    if(listaIdentificadores()){
        // Para sair da função anterior, ja leu-se o proximoAtomo()
        if(atomo == ":"){
            proximoAtomo();
            if(atomo != "int" && atomo != "bool"){
                Exceptions::showSyntaxError(linha,atomo, "primitive type");
            }
        }
        else{
            Exceptions::showSyntaxError(linha, atomo, ":");
        }
    }
    else{
        Exceptions::showSyntaxError(linha, atomo, "Identifier(s)");
    }
}

bool AnaSint::comandoComposto(){
    // Ja leu-se o proximoAtomo()
    if(atomo == "beg"){
        comando();
        //proximoAtomo();
        while(atomo == ";"){
            if(comando())
                proximoAtomo();
        }

        if(atomo == "end")
            proximoAtomo();
        else
            Exceptions::showSyntaxError(linha,atomo,"end");

        return true;
    }
    else
        return false;
}

bool AnaSint::comando(){
    // numero?

    return comandoSemRotulo();
}

bool AnaSint::comandoSemRotulo(){
    proximoAtomo();

    if(identificador()){
        proximoAtomo();
        if(!atribuicao())
            chamadaProcedimento();
        return true;
    }

    if(comandoComposto() || comandoCondicional() || comandoRepetitivo())
        return true; 

    return false;
}

bool AnaSint::atribuicao(){    
    if(atomo == ":="){
        expressao();
        return true;
    }
    return false;
}

bool AnaSint::variavel(){
    return identificador();
}

void AnaSint::expressao(){
    expressaoSimples();
    if(relacao())
        expressaoSimples();
}

void AnaSint::expressaoSimples(){
    proximoAtomo();
    if(atomo == "+" || atomo == "-"){
        proximoAtomo();
    }

    if(termo()){   
        while (true){
            //proximoAtomo();
            if(atomo == "+" || atomo == "-" || atomo == "or"){
                proximoAtomo();
                termo();
            }
            else
                break;
        }
    }
    
}

bool AnaSint::termo(){
    if(fator()){
        while(true){
            proximoAtomo();
            if(atomo == "*" || atomo == "/" || atomo == "and"){
                proximoAtomo();
                fator();
            }
            else
               break;
        }
        return true;
    }
    return false;
}

bool AnaSint::fator(){
    if(variavel() || numero() || chamadaFuncao())
        return true;

    if(atomo == "("){
        expressao();
        // proximoAtomo();
        if(atomo == ")"){
            return true;
        }
        else{
            Exceptions::showSyntaxError(linha, atomo, ")");
        }
    }

    if(atomo == "not"){
        return fator();
    }

    return false;
}

bool AnaSint::chamadaFuncao(){
    return false;
}

bool AnaSint::chamadaProcedimento(){
    if(atomo == "("){
        listaExpressoes();
        //proximoAtomo();
        if(atomo == ")"){
            return true;
        }
        else{
            Exceptions::showSyntaxError(linha, atomo, ")");
            return false;
        }
    }
    return true;
}

void AnaSint::listaExpressoes(){
    expressao();
    while (true){
        if(atomo == ","){
            proximoAtomo();
            expressao();
        }
        else
            break;
    }
}

bool AnaSint::comandoRepetitivo(){
    if(atomo == "while"){
        expressao();
        //proximoAtomo();
        if(atomo == "do"){
            comandoSemRotulo();
        }

        return true;
    }
    else{
        return false;
    }
}

bool AnaSint::comandoCondicional(){
     if(atomo == "if"){
        expressao();
        //proximoAtomo();
        if(atomo == "then"){
            comandoSemRotulo();
            //proximoAtomo();
            if(atomo == "el"){
                comandoSemRotulo();
            }

        }
        return true;
    }
    else
        return false;
}

bool AnaSint::relacao(){
    return atomo == "=" || atomo == "<>" || atomo == "<" || atomo == "<=" || atomo == ">=" || atomo == ">";
}

bool AnaSint::identificador(){
    if(pertence(atomo, Constantes::IDS) || atomo == "rd" || atomo == "wrt")
        return true;
    else
        return false;
}

bool AnaSint::numero(){
    return atomo.find("num") != string::npos;
}

void AnaSint::proximoAtomo(){
    string aux = "";
    while(!arquivo.eof()){
        char c = static_cast<char>(arquivo.get());
        if(c == ' ')
            break;
        if(c == '\n'){
            linha++;
            continue;
        }
        if(c == '\t')
            continue;
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

bool AnaSint::pertence(string simbolo, vector<string> conjunto){
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