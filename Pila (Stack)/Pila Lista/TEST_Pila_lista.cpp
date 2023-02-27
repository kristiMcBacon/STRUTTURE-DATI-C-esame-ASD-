#include "Pila.h"

using namespace std;

int main() {
    Pila<int> P, A1;
    P.inpila(3);
    P.inpila(13);
    P.fuoripila();
    P.stampa();
    
    cout<<"\n\n";
    P.inpila(9);
    P.inpila(1);
    P.inpila(90);
    A1.inpila(11);

    Pila<int> A2(P);

    P=A1;
    if(P==A2)
        cout<<"\nUguali\n";
    else
        cout<<"\nDiversi\n";

    A2.stampa();
    
    



}