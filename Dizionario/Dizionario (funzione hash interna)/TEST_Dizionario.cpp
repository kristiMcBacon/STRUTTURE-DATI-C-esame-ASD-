#include "Dizionario.h"
#include "Coppia.h"
#include <iostream>

using namespace std;


int main(){
    Dizionario<string,int> d(100);
    Coppia<string, int> coppia("abc", 123);
    Coppia<string, int> coppia1("abc", 133);
    Coppia<string, int> coppia2("abcde", 223);
    cout<<"\nChiave-->"<<coppia.getChiave()<<", Valore-->"<<coppia.getValore()<<"\n\nUguali-->"<<(coppia1==coppia);

    d.inserisci(coppia);
     d.inserisci(coppia1);
      d.inserisci(coppia2);


    d.cancella("abcd");
    cout<<"\nAppartiene-->"<<d.appartiene("abc");
    int a=999;
    d.aggiorna("abc", a);
    cout<<"\nVal recuperato-->"<<d.recupera("abc");
    cout<<d.contienevalore(523);
    cout<<"\n---------------FINE---------------";
}