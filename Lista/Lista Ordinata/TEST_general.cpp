#include "Order_list.h"
#include <iostream>

using namespace std;


int main(){

    cout<<"\n--------------------------------INIZIO---------------------";
    Order_list<int> L;
    

    
    auto it=L.begin();
    for(int i=1;i<=10;i++){
        L.insert(i);
    }

    L.insert(5);
    for(int i=1;i<=9;i++){
    L.erase(L.begin());
    }

    cout<<"\n-stampa -->"<<L;

    Order_list<int> A=L;
     cout<<"\n-stampa -->"<<A;

    cout<<"\n--------------------------------FINE-----------------------";
    
}
