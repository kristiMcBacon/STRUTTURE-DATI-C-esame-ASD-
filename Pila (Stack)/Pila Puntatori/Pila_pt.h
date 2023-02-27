#ifndef PILA_PT_H
#define PILA_PT_H

#include "Cella_Pila.h"
#include <iostream>
#include <assert.h>
using namespace std;

template <class T>
class Pila_pt: private Cella_pila<T>{
public:
    typedef T tipoelem;

    //COSTRUTTORE
    Pila_pt();
    //COSTRUTTORE DI COPIA
    Pila_pt(Pila_pt<T>&);
    //DISTRUTTORE
    ~Pila_pt();

    //OPERATORI--------------------------------
    bool pilaVuota() const;       //CONTROLLA SE LA PILA E' VUOTA
    tipoelem leggiPila() const;   //RESTITUISCE TESTA DELLA PILA
    void fuoriPila();             //RIMUOVE L'ELEMENTO IN TESTA
    void inPila(tipoelem);        //AGGIUNGE UN ELEMENTO IN TESTA

    //Altri OPERATORI--------------------------
    void stampaPila(Pila_pt<tipoelem>&);    //STAMPA LA PILA
    void svuotaPila();                      //SVUOTA LA PILA
	bool contiene(tipoelem) const;          //Verifica se un elemento e' già presente nella pila
    void quicksort(int *a, int lower, int upper);

    //SOVRACCARICO OPERATORI
	Pila_pt<T>& operator=(Pila_pt<T> &);  //SOVRACCARICO OPERATORE ASSEGNAZIONE =
	bool operator==(Pila_pt<T> &);      //SOVRACCARICO OPERATORE UGUAGLIANZA ==

private:
    Cella_pila<tipoelem>* testa;
  
};

//____________________________________________________________________________________________________________

//COSTRUTTORE
template <class T>
Pila_pt<T>::Pila_pt() {
  testa = nullptr;
}

//COSTRUTTORE DI COPIA
template <class T>
Pila_pt<T>::Pila_pt(Pila_pt<T>& l){
    
    testa = nullptr;

    tipoelem b;

    if(!l.pilaVuota()) {
    b=l.leggiPila();
    l.fuoriPila();

    *this=l;
    
    this->inPila(b);
    l.inPila(b);
  }
}

//DISTRUTTORE
template <class T>
Pila_pt<T>::~Pila_pt() {
    while (!pilaVuota())
        fuoriPila();
    delete testa;
};

//OPERATORI--------------------------------
//CONTROLLA SE LA PILA E' VUOTA
template <class T>
bool Pila_pt<T>::pilaVuota() const {
    return testa==nullptr;
}

//RESTITUISCE TESTA DELLA PILA
template <class T>
T Pila_pt<T>::leggiPila() const {
    assert(!pilaVuota());
    return testa->leggiCella();
}

//RESTITUISCE TESTA DELLA PILA
template <class T>
void Pila_pt<T>::fuoriPila() {
    assert(!pilaVuota());
    
    Cella_pila<tipoelem> *tmp = testa;
    testa = testa->leggiSucc();
    delete tmp;
}

//AGGIUNGE UN ELEMENTO IN TESTA
template <class T>
void Pila_pt<T>::inPila(tipoelem el) {
    Cella_pila<tipoelem> *tmp = new Cella_pila<tipoelem>();
    tmp->scriviCella(el);
    tmp->scriviSucc(testa);
    testa = tmp;
}

//Altri OPERATORI--------------------------
//STAMPA LA PILA
template <class tipoelem>
void Pila_pt<tipoelem>::stampaPila(Pila_pt<tipoelem>& P){
  if(!P.pilaVuota()) {
    tipoelem elem=P.leggiPila();
    cout<<"["<<elem<<"]";
    P.fuoriPila();
    stampaPila(P);
    P.inPila(elem);
  }
}

//SVUOTA LA PILA
template <class tipoelem>
void Pila_pt<tipoelem>::svuotaPila() {
  while(!pilaVuota())
    fuoriPila();
}

//Verifica se un elemento e' già presente nella pila
template <class T>
bool Pila_pt<T>::contiene(tipoelem el) const {
	bool trovato = false;
	if (!this->pilaVuota()) {
        Cella_pila<tipoelem> *tmp = new Cella_pila<tipoelem>();
		tmp = testa;
		while ((tmp != nullptr) && !trovato) {
			if (tmp->leggiCella() == el) {
				trovato = true;
			}
			tmp = tmp->leggiSucc();
		}
	}
	return (trovato);
}

//SOVRACCARICO OPERATORI---------------------------------------------------------
//SOVRACCARICO OPERATORE =
template<class T>
Pila_pt<T>& Pila_pt<T>::operator=(Pila_pt<T>& l){
    if(!pilaVuota()) {
        svuotaPila();
        testa = nullptr;
    }

    tipoelem b;

    if(!l.pilaVuota()) {
    b=l.leggiPila();
    l.fuoriPila();

    *this=l;
    
    this->inPila(b);
    l.inPila(b);
  }
  return *this;
}

//SOVRACCARICO OPERATORE ==
template<class T>
bool Pila_pt<T>::operator==(Pila_pt<T> &l){	
    
  if(pilaVuota() && l.pilaVuota())
    return true;
  
  tipoelem a, b;

  if(!pilaVuota() && !l.pilaVuota()) {
    a=leggiPila();
    b=l.leggiPila();

    if(a!=b)
      return false;
    this->fuoriPila();
    l.fuoriPila();

    *this==l;
    
    this->inPila(a);
    l.inPila(b);
  }
  else
    return false;

return true;
}

#endif