#ifndef CELLA_H
#define CELLA_H

#include <iostream>

//DICHIARAZIONE CLASSE CELLA di Coda
template <class T>
class Cella {
public:
    typedef T tipoelem;
	typedef Cella<T>* posizione;

	//COSTRUTTORE
	Cella();
  	//DISTRUTTORE
  	~Cella();

  	//OPERATORI--------------------------------
  	tipoelem leggiCella() const;
  	void scriviCella(tipoelem);
  	Cella<T>* leggiSucc() const;
  	void scriviSucc(Cella<T>*);

    
private:
	tipoelem elem;
	Cella<tipoelem> *suc;
};




//COSTRUTTORE
template<class T>
Cella<T>::Cella() {
  suc=nullptr;
}

//DISTRUTTORE
template<class T>
Cella<T>::~Cella() {}

//OPERATORI--------------------------------
template<class T>
T Cella<T>::leggiCella() const {
  return elem;
}

template<class T>
void Cella<T>::scriviCella(tipoelem e) {
	elem=e;
}

template<class T>
Cella<T>* Cella<T>::leggiSucc() const {
  return suc;
}

template <class T>
void Cella<T>::scriviSucc(Cella<T>* c) {
  suc=c;
}

#endif