#include "Order_list.h"
#include <iostream>

using namespace std;


int main(){

    cout<<"\n--------------------------------INIZIO---------------------";
    Order_list<int> L;
    
    auto it=L.begin();
    for(int i=1;i<=10;i++){
        L.insert(i);
        it=L.next(it);
    }
    
    cout<<"\n-stampa -->"<<L;



    cout<<"_____________________________Test altre funzioni________________________________";

    cout<<"\n-size()-->"<<L.size();

    L.pop_front();
    L.pop_back();
    cout<<"\n-stampa dopo pop -->"<<L;

    if(L.palindroma())
        cout<<"\nPalondorma";
    else 
        cout<<"\nNon è palindroma";

    L.remove(4);
    cout<<"\n-stampa -->"<<L;

    cout<<"\n-num_elements()-->"<<L.num_elements(L.begin(),L.last());

    L.clear();
    cout<<"\n-stampa dopo clear -->"<<L;

    L.insert(4);
    L.insert(40);
    cout<<"\n-stampa dopo insert -->"<<L;
    if(L.member(40))
        cout<<"\nAppartiene";
    else 
        cout<<"\nNon è Appartiene";


    cout<<"\n--------------------------------FINE-----------------------";
    
}
