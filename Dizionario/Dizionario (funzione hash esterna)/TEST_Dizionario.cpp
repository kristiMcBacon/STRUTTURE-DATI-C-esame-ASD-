#include "Dizionario.h"
#include "Coppia.h"
#include <iostream>

using namespace std;


int main(){
    Dizionario<string,int> d(100);
    Coppia<string, int> coppia("abc", 123);
    Coppia<string, int> coppia1("abcd", 123);
    Coppia<string, int> coppia2("abcde", 223);
    cout<<"\nChiave-->"<<coppia.getChiave()<<", Valore-->"<<coppia.getValore()<<"\n\nUguali-->"<<(coppia1==coppia);

    d.inserisci(coppia);
     d.inserisci(coppia1);
      d.inserisci(coppia2);


    d.cancella("abc");
    cout<<"\nAppartiene-->"<<d.appartiene("abcd");
    int a=999;
    d.aggiorna("abc", a);
    cout<<"\nVal recuperato-->"<<d.recupera("abc")<<endl;
    cout<<d.contienevalore(123);
    cout<<"\n---------------FINE---------------";
}