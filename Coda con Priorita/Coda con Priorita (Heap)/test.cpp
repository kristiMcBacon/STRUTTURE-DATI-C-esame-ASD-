#include "CodaPriorita.h"

int main () {
  CodaP < int > C, A1;

  C.inserisci (1);
  C.inserisci (12);
  C.inserisci (19);
  C.inserisci (7);
  C.cancellaMin ();
  C.inserisci (0);
  C.inserisci (11);
  C.cancellaMin ();
  C.inserisci (5);
  C.inserisci (21);
  C.inserisci (18);
  C.cancellaMin ();
  C.inserisci (3);
  C.cancellaMin ();
  
  A1.inserisci (1);
  A1.inserisci (12);
  A1.inserisci (19);
  A1.inserisci (7);
  A1.cancellaMin ();
  A1.inserisci (0);

A1=C;
C.stampaPrioriCoda();
  A1.stampaPrioriCoda();
  CodaP<int> A3(A1), A;
  //C.incoda(999);
  if(A3==C)
    cout<<"\nUguali\n";
  else 
    cout<<"\nDiversi\n";

  //C.~CodaP();
  C.stampaPrioriCoda();
  A1.stampaPrioriCoda();
  //D.stampaPrioriCoda();
}