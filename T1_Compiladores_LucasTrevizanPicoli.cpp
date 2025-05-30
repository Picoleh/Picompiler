/*
- Lucas Trevizan Pícoli
- Windows
- Compilado com g++ 13.2.0 no Visual Studio Code
- Como as classes estão em arquivos separados, talvez seja necessário compilá-las ao mesmo tempo
- usando g++ *.cpp -o nomeExe
*/

#include "Analex.h"
#include "AnaSint.h"
using namespace std;

int main(){
    Analex analex;
    analex.analisar("Trab1_Compiladores.txt");

    

    return 0;
}