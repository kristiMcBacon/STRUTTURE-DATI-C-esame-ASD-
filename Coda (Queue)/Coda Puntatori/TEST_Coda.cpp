#include "Coda.h"

using namespace std;

int main() {

Coda<int> C, A1;



int i=0;
while(i<=15) {
    C.incoda(i);
    i++;
}



cout<<"Elem-->"<<C.leggicoda();

//C.fuoricoda();
C.incoda(999);

//cout<<"\n\nElem-->"<<C.leggicoda();
A1=C;

Coda<int> D(A1);
//C.incoda(999);
if(A1==D)
    cout<<"\nUguali\n";
else 
    cout<<"\nDiversi\n";

C.stampacoda();
A1.stampacoda();


}