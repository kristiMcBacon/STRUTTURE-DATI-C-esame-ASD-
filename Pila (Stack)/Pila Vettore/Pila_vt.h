#ifndef PILA_VT_H
#define PILA_VT_H

#include <iostream>
using namespace std;

template <class T>
class Pila_vt {
public:
  typedef T tipoelem;

  //COSTRUTTORI (IMPOSTA LA TESTA A 0)
  Pila_vt();        
  Pila_vt(int);
  //COSTRUTTORE DI COPIA
  Pila_vt(Pila_vt<T> &);
  //DISTRUTTORE
  ~Pila_vt(); 

  //OPERATORI--------------------------------
  bool pilaVuota() const;       //CONTROLLA SE LA PILA E' VUOTA
  tipoelem leggiPila() const;   //RESTITUISCE TESTA DELLA PILA
  void fuoriPila();             //RIMUOVE L'ELEMENTO IN TESTA
  void inPila(tipoelem);        //AGGIUNGE UN ELEMENTO IN TESTA

  //Altri OPERATORI--------------------------
  void stampaPila(Pila_vt<tipoelem>&);    //STAMPA LA PILA
  void svuotaPila();                      //SVUOTA LA PILA

  //SOVRACCARICO OPERATORI
	Pila_vt<T>& operator=(Pila_vt<T> &);  //SOVRACCARICO OPERATORE ASSEGNAZIONE =
	bool operator==(Pila_vt<T> &);      //SOVRACCARICO OPERATORE UGUAGLIANZA ==
  int dimPila() { return MAXLUNGH; };

private:
  tipoelem *elementi;
  int MAXLUNGH;
  int testa;

};

//____________________________________________________________________________________________________________

//COSTRUTTORE
template <class T>
Pila_vt<T>::Pila_vt() {
  elementi = new tipoelem[100]; // dimensione standard della pila
  MAXLUNGH = 100;
  testa=0;
}

//COSTRUTTORE con dimensione
template <class T>
Pila_vt<T>::Pila_vt(int N) {
  elementi = new tipoelem[N]; // dimensione N della pila
  MAXLUNGH = N;
  testa=0;
}

//COSTRUTTORE DI COPIA
template <class T>
Pila_vt<T>::Pila_vt(Pila_vt<T> &l) {	
  tipoelem b;

  elementi = new tipoelem[dimPila()]; // dimensione N della pila
  MAXLUNGH = dimPila();
  testa=0;

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
Pila_vt<T>::~Pila_vt() {
  delete[] elementi;
};

//OPERATORI--------------------------------
//CONTROLLA SE LA PILA E' VUOTA
template <class T>
bool Pila_vt<T>::pilaVuota() const {
  return testa==0;
}

//RESTITUISCE TESTA DELLA PILA
template <class T>
T Pila_vt<T>::leggiPila() const {
  return elementi[testa-1];
}

//RIMUOVE L'ELEMENTO IN TESTA
template <class T>
void Pila_vt<T>::fuoriPila() {
  if (!pilaVuota()) {
    testa--;
  }
  else {
    cout<<"nessun ELEMENTO nella pila"<<endl;
  }
}

//AGGIUNGE UN ELEMENTO IN TESTA
template <class T>
void Pila_vt<T>::inPila(tipoelem el) {
  if (testa==MAXLUNGH) {
    cout<<"raggiunta capacità massima della pila"<<endl;
  }
  else {
    elementi[testa]=el;
    testa++;
  }
}

//Altri OPERATORI--------------------------
//STAMPA LA PILA
template <class tipoelem>
void Pila_vt<tipoelem>::stampaPila(Pila_vt<tipoelem>& P){
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
void Pila_vt<tipoelem>::svuotaPila() {
  while(!pilaVuota())
    fuoriPila();
}

//SOVRACCARICO OPERATORI---------------------------------------------------------
//SOVRACCARICO OPERATORE =
template<class T>
Pila_vt<T>& Pila_vt<T>::operator=(Pila_vt<T>& l){
  tipoelem b;

  elementi = new tipoelem[dimPila()]; // dimensione N della pila
  MAXLUNGH = dimPila();
  testa=0;

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
bool Pila_vt<T>::operator==(Pila_vt<T> &l){	
  if(dimPila() != l.dimPila())
    return false;

  if(pilaVuota() && l.pilaVuota())
    return true;
  
  tipoelem a, b;

  if(!pilaVuota()) {
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
	return true;
}

#endif