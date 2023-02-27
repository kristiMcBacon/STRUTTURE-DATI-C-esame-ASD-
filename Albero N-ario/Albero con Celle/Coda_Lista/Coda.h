#ifndef CODA_H
#define CODA_H

#include "Lista\Linked_list.h"

#include <assert.h>
#include <iostream>

//CODA REALIZZATA TRAMITE LISTA
template <class tipoelem> 
class Coda {
public:

    //OPERATORI--------------------------------   
    bool codavuota();           //CONTROLLA SE LA CODA E' VUOTA
    void incoda(tipoelem);      //INSERISCE UN ELEMENTO IN TESTA ALLA CODA
    tipoelem leggicoda();       //LEGGE E RESTITUISCE L'ELEMENTO IN ULTIMA POSIZIONE, OVVERO IL PRIMO INSERITO
    void fuoricoda();           //ELIMINA L'ULTIMO ELEMENTO DELLA CODA, OVVERO IL PRIMO INSERITO

    //Altri OPERATORI--------------------------
    void stampacoda();      //Stampa Coda

private:
    Linked_list<tipoelem> codaL;
};
//____________________________________________________________________________________________________________

//OPERATORI--------------------------------   
//CONTROLLA SE LA CODA E' VUOTA
template<class tipoelem>
bool Coda<tipoelem>::codavuota() {
    return(codaL.empty());
};

//INSERISCE UN ELEMENTO IN TESTA ALLA CODA
template<class tipoelem>
void Coda<tipoelem>::incoda(tipoelem elem) {
    typename Linked_list<tipoelem>::position pos=codaL.begin(); 
    
    while(!codaL.end(pos)) {
        pos=codaL.next(pos);
    }
    
    codaL.insert(elem,pos); 
};

//LEGGE E RESTITUISCE L'ELEMENTO IN ULTIMA POSIZIONE, OVVERO IL PRIMO INSERITO
template<class tipoelem> 
tipoelem Coda<tipoelem>::leggicoda() {
    assert(!codavuota());
        return(codaL.read(codaL.begin()));
};

//ELIMINA L'ULTIMO ELEMENTO DELLA CODA, OVVERO IL PRIMO INSERITO
template<class tipoelem>
void Coda<tipoelem>::fuoricoda() {
    typename Linked_list<tipoelem>::position pos=codaL.begin(); 
    assert(!codavuota());
        codaL.erase(pos); 
};

//Altri OPERATORI--------------------------
//Stampa Coda
template<class T>
void Coda<T>::stampacoda() {
    cout<<codaL;
}

#endif
