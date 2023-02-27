#include <iostream>
#include <string>

using namespace std;

#include "Albero.h"

int main()
{
    cout << "\n--------------------------------INIZIO---------------------\n"
         << endl;

    Albero<int> A, B;
    Albero<int>::nodo n1, n2;

    //cout<<A.alberoVuoto()<<endl;

    A.insRadice(n1);
    A.scriviNodo(A.radice(), 0);
    n1=A.radice();

    //FIGLI DI 0 (root)
    A.insPrimoFiglio(n1, 20);
    A.insPrimoFiglio(n1, 21);

    //A.scriviNodo(A.primoFiglio(n1), 1);
    //A.scriviNodo(A.figlioSx(n1), 9);

    //FIGLI DI 21
    n1=A.primoFiglio(n1);
    A.insPrimoFiglio(n1, 30);
    A.insPrimoFiglio(n1, 31);

    //FIGLI DI 22
    n1=A.succFratello(n1);
    A.insPrimoFiglio(n1, 300);
    A.insPrimoFiglio(n1, 311);

    //A.~Albero();

    A.stampa();
    A.cancSottoAlbero(n1);
    A.stampa();

    //Costruzione B
    B.insRadice(n2);
    B.scriviNodo(B.radice(), 123);
    n2=B.radice();

    //FIGLI DI 0 (root)
    B.insPrimoFiglio(n2, 9);
    B.insPrimoFiglio(n2, 9);
    B.stampa();
    //
    n1= A.primoFiglio(A.primoFiglio(A.radice()));
    A.insSottoAlbero(n1, B);
    //A.~Albero();
    A.stampa();
    //
    cout<<"\nProfondità Albero-->"<<A.profondita();
    //
    cout<<"\nAltezza Albero-->"<<A.altezza();
    //








    cout << "\n--------------------------------FINE-----------------------";
}