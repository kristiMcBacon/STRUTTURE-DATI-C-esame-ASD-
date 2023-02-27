#include "Coda.h"
#include <error.h>

using namespace std;

int main() {

Coda<int> C, A;



int i=0;
while(i<=15) {
    C.incoda(i);
    i++;
}
C.stampacoda();

//cout<<"Elem-->"<<C.leggicoda();

//C.fuoricoda();
//C.incoda(999);

//cout<<"\n\nElem-->"<<C.leggicoda();

Coda<int> A1(C);

//C=A;
if(A1==C)
    cout<<"\nUguali\n";
else 
    cout<<"\nDiversi\n";

C.stampacoda();
A1.stampacoda();

cout<<"\n------------------------------FINE-----------------------\n";
}