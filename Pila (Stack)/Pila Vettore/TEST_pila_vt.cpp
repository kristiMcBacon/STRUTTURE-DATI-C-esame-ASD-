#include "Pila_vt.h"

using namespace std;

int main() {
    Pila_vt<int> P, A;
    P.inPila(3);
    P.inPila(13);
    //P.fuoriPila();
    P.stampaPila(P);
    
    
    cout<<"\n\n";
    P.inPila(9);
    //P.stampaPila(P);


    
    Pila_vt<int> A1(P);
    //P=A;
    //P.svuotaPila();
    if(P==A1)
        cout<<"\nUguali\n";
    else
        cout<<"\nDiversi\n";

    cout<<"\nstampa P->";P.stampaPila(P);
    cout<<"\nstampa A1->";P.stampaPila(A1);


}