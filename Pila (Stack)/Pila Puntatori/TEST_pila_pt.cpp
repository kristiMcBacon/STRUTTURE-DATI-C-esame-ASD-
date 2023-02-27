#include "Pila_pt.h"

using namespace std;

int main() {
    Pila_pt<int> P, A, P1;
    P.inPila(3);
    P.inPila(13);
    P.fuoriPila();
    P.stampaPila(P);
    
    P.svuotaPila();
    cout<<"\n\n";
    P.inPila(9);
    P.inPila(1);
    P.inPila(90);
    P.inPila(61);

    A.inPila(9);
    A.inPila(1);
    A.inPila(90);
    A.inPila(10);

    Pila_pt<int> P2(P);
    P.stampaPila(P);cout<<"\n";
    A.stampaPila(A);
    //P=P1;
    if(P==A)
        cout<<"\nUguali\n";
    else
        cout<<"\nDiversi\n";
    
    P.stampaPila(P);cout<<"\n";
    A.stampaPila(A);
    cout<<"\n\n";

    cout<<P.contiene(9);



}