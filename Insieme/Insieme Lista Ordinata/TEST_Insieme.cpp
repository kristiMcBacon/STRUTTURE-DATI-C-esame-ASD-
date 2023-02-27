#include "Insieme.h"
#include <iostream>

using namespace std;


int main(){

Insieme<int> i1,i2,u;

for (int i = 0; i < 10; i++) {
    i1.inserisci(i);
    i2.inserisci(i+9);
}
i1=i2;
i1.stampa();
i2.stampa();

cout<<"-Differenza-->";
u=i1.intersezione(i2);
u.stampa();

Insieme<int> i3(u);
i3=i2;

if(i2==i3) 
    cout<<"\nUguali\n";
else
    cout<<"\nDiversi\n";
i3.stampa();
i2.stampa();



}