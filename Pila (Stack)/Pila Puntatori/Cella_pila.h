#ifndef CELLA_PILA_H
#define CELLA_PILA_H

#include <iostream>
using namespace std;

template <class T>
class Cella_pila {
public:
  typedef T tipoelem;

  //COSTRUTTORE
  Cella_pila();
  //DISTRUTTORE
  ~Cella_pila();

  //OPERATORI--------------------------------
  tipoelem leggiCella() const;
  void scriviCella(tipoelem);
  Cella_pila<T>* leggiSucc()const;
  void scriviSucc(Cella_pila<T>*);

private:
  tipoelem elem;
  Cella_pila<tipoelem> *suc;

};


//COSTRUTTORE
template<class T>
Cella_pila<T>::Cella_pila() {
  suc=nullptr;
}

//DISTRUTTORE
template<class T>
Cella_pila<T>::~Cella_pila() {}

//OPERATORI--------------------------------
template<class T>
T Cella_pila<T>::leggiCella()const {
  return elem;
}

template<class T>
void Cella_pila<T>::scriviCella(tipoelem e) {
  elem=e;
}

template<class T>
Cella_pila<T>* Cella_pila<T>::leggiSucc()const {
  return suc;
}

template <class T>
void Cella_pila<T>::scriviSucc(Cella_pila<T>* c) {
  suc=c;
}


#endif