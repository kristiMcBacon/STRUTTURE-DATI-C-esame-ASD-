#include "linked_list.h"
#include "list_vector.h"
#include <iostream>

using namespace std;


int main(){

    cout<<"\n--------------------------------INIZIO---------------------";
    //Linked_list<int> L;
    List_vector<int> lista1, lista2, L;
    

    
    auto it=L.begin();
    for(int i=1;i<=10;i++){
        L.insert(i,it);
        it=L.next(it);
    }

    L.write(9,L.begin());
    
    for(int i=1;i<=3;i++){
    L.erase(L.begin());
    }

    cout<<"\n-stampa -->"<<L;
    List_vector<int> A=L;

    cout<<"\n-stampa -->"<<A;

    cout<<"\n--------------------------------FINE-----------------------";
    
}
