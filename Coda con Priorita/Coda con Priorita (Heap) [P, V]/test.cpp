#include "CodaPriorita.h"

int main () {
  CodaP < int > C, A, E;

  CodaP<int>::tipoelem e1(1,10);
	CodaP<int>::tipoelem e2(2,20);
	CodaP<int>::tipoelem e3(3,30);

	C.inserisci(e1);
	C.inserisci(e3);
	C.inserisci(e2);

	//A=C;
	CodaP < int > A1(C);

	if(A1==E) 
		cout<<"\nUguali\n";
	else
		cout<<"\nDiversi\n";

  A1.stampaPrioriCoda();
  C.stampaPrioriCoda();
}