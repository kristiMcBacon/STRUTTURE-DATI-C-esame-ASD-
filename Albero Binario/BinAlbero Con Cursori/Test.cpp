#include <iostream>
#include <string>

using namespace std;

#include "BinAlbero.h"

int main()
{
    cout << "\n--------------------------------INIZIO---------------------\n"<< endl;

    BinAlbero<int> A, B;
    typename BinAlbero<int>::Nodo n1, n2;

    A.insRadice(n1);
    A.scriviNodo(A.radice(), 0);
    n1=A.radice();

    A.insFiglioDx(n1);
    A.insFiglioSx(n1);

    A.scriviNodo(A.figlioDx(n1), 1);
    A.scriviNodo(A.figlioSx(n1), 9);
    //A.~BinAlbero();
    cout<<A;




    cout << "\n--------------------------------FINE-----------------------";
}