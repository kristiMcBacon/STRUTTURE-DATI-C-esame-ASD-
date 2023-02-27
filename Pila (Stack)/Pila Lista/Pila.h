#ifndef _PILA_H
#define _PILA_H

#include<assert.h>

#include "Lista\Linked_list.h"

template <class T>
class Pila {
public:
    typedef T tipoelem;

    //OPERATORI---------------------------------
    bool pilavuota() const;
    tipoelem leggipila() const;
    void fuoripila();
    void inpila(tipoelem elem);

    //FUNZIONI DI SERVIZIO---------------------
    void stampa();

    //SOVRACCARICO OPERATORI
	Pila<T>& operator=(Pila<T> &);  //SOVRACCARICO OPERATORE ASSEGNAZIONE =
	bool operator==(Pila<T> &);      //SOVRACCARICO OPERATORE UGUAGLIANZA ==

private:
    Linked_list<tipoelem> pila;
};

template <class T>
bool Pila<T>::pilavuota() const {
	return pila.empty();
}

template <class T>
T Pila<T>::leggipila() const {   
    assert(!pilavuota());
	return pila.read(pila.bigin());
}

template <class T>
void Pila<T>::fuoripila() {   
    assert(!pilavuota());
    auto first = pila.begin();
	pila.erase(first);
}

template <class T>
void Pila<T>::inpila(tipoelem el) {
    auto first = pila.begin();
	pila.insert(el,first);
}

//FUNZIONI DI SERVIZIO---------------------
template <class T>
void Pila<T>::stampa() {
    cout<<pila;
}

//SOVRACCARICO OPERATORI---------------------------------------------------------
//SOVRACCARICO OPERATORE =
template<class T>
Pila<T>& Pila<T>::operator=(Pila<T>& l){
    this->pila= Linked_list<T>(l.pila);
  return *this;
}

//SOVRACCARICO OPERATORE ==
template<class T>
bool Pila<T>::operator==(Pila<T> &l){	
 return(l.pila==this->pila);
}

#endif
