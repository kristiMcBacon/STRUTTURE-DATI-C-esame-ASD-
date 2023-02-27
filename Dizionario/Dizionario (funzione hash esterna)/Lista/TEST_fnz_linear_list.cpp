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
    
    cout<<"\n-stampa -->"<<L;



    cout<<"_____________________________Test fnz linear_list________________________________";

    cout<<"\n-size()-->"<<L.size();

    L.push_front(1);
    L.push_back(19);
    cout<<"\n-stampa dopo push -->"<<L;

    L.pop_front();
    L.pop_back();
    cout<<"\n-stampa dopo pop -->"<<L;

    L.clear();
    cout<<"\n-stampa dopo clear -->"<<L;

    L.push_front(40);
    L.push_back(4);
    cout<<"\n-stampa dopo push -->"<<L;

    L.reverse();
    cout<<"\n-stampa dopo reverse -->"<<L;


    L.push_front(5);
    L.push_back(6);
    if(L.palindroma())
        cout<<"\nPalondorma";
    else 
        cout<<"\nNon è palindroma";

    L.remove(4);
    cout<<"\n-stampa -->"<<L;

    cout<<"\n-num_elements()-->"<<L.num_elements(L.begin(),L.last());

    L.exchange(L.begin(),L.last());
    cout<<"\n-stampa dopo excange -->"<<L;

    if(L.member(40))
        cout<<"\nAppartiene";
    else 
        cout<<"\nNon è Appartiene";


    cout<<"\n--------------------------------FINE-----------------------";
    
}
