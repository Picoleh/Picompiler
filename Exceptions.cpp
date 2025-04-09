#include "Exceptions.h"

void Exceptions::showError(int tipo, int linha, string atomo){
    cerr << RED << "Error:" << RESET;
    switch (tipo)
    {
    case 0: // Simbolo desconhecido
        cerr <<" Simbolo desconhecido\n";
        break;
    case 1: // Identificador ou numero mal formado
        cerr << " Identificador ou numero mal formado\n";
        break;
    default:
        break;
    }

    if(atomo != ""){
        cout << linha << " | " << RED << atomo << RESET << "\n";
    }
}