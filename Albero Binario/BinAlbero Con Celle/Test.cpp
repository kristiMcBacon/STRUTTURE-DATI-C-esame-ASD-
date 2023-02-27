#include <iostream>
#include <string>

using namespace std;

#include "BinAlbero.h"

int main()
{
    cout << "\n--------------------------------INIZIO---------------------\n"
         << endl;

    BinAlbero<int> A, B, C, B1;

    // Albero vuoto
    cout << (A.alberovuoto()) << endl;
    // Costruisce albero A------------------------------
    A.insradice();
    A.insfiglioDx(A.radice());
    A.insfiglioSx(A.radice());

    A.scrivinodo(A.radice(), 11);
    A.scrivinodo(A.figlioDx(A.radice()), 1);
    A.scrivinodo(A.figlioSx(A.radice()), 9);
    // Stampa
    cout << "-A-->";
    A.stampa();

    // Costruzione albero B-----------------------------
    B.insradice();
    B.insfiglioDx(B.radice());
    B.insfiglioSx(B.radice());

    B.scrivinodo(B.radice(), 22);
    B.scrivinodo(B.figlioDx(B.radice()), 10);
    B.scrivinodo(B.figlioSx(B.radice()), 90);
    // Stampa
    cout << "-B-->";
    B.stampa();
    //-----------------------------------------------------------------------------------

    B.cancsottoalbero(B.figlioDx(B.radice()));
    cout << "\nCancellazione SottoAlbero\nB-->";
    B.stampa();
    //
    C.costralbero(A, B);
    C.scrivinodo(C.radice(), 0);
    cout << "\nCostruzione C\nC-->";
    C.stampa();
    //
    cout << "\nFoglia? -->" << (B.foglia(B.figlioSx(B.radice()))) << endl;
    cout << "Foglia? -->" << (B.foglia(B.radice())) << endl;
    //
    cout << "\nProfondità C-->" << C.profondita();
    cout << "\nC-->";
    C.stampa();
    //
    B1=B;
    //
    cout<<"\n\nInserisco B a destra di C";
    C.insSub_dx(C.figlioDx(C.radice()), B);
    cout << "\nC-->";
    C.stampa();
    //
    cout<<"\n\nCancella foglie pari di C";
    C.cancFoglie_pari();
    cout << "\nC-->";
    C.stampa();
    //
    cout<<"\n\nMutation A e C";
    cout << "\nA-->";
    A.stampa();
    cout << "C-->";
    C.stampa();
    C.mutation(C.figlioDx(C.radice()), C.figlioDx(A.radice()), A);
    cout << "\nA-->";
    A.stampa();
    cout << "C-->";
    C.stampa();
    //
    A = B1;
    B1.~BinAlbero();
    cout << "\nA-->"<<A;

    //A.stampa();

    cout << "\n--------------------------------FINE-----------------------";
}