#ifndef COPPIA_H
#define COPPIA_H

#include <iostream>
using namespace std;

template <class K, class V>
class Coppia {
    
public:
    typedef K Chiave;
    typedef V Valore;

    Coppia();                                   //COSTRUTTORE
	Coppia(Chiave, Valore);                     //COSTRUTTORE con valori
    Coppia(const Coppia<Chiave, Valore> &);     //COSTRUTTORE DI COPIA

    //OPERATORI--------------------------------
	Valore getValore();         //RESTITUISCE IL VALORE
	Chiave getChiave();         //RESTITUISCE LA CHIAVE
	void setValore(Valore&);    //IMPOSTA IL VALORE
	void setChiave(Chiave);     //IMPOSTA LA CHIAVE

	//SOVRACCARICO OPERATORE '='
	Coppia<Chiave, Valore>& operator=(const Coppia<Chiave, Valore> &);
    //SOVRACCARICO OPERATORE ==
    bool operator==(const Coppia<K, V> &pair);
    //SOVRACCARICO OPERATORE DI STAMPA <<
    friend ostream &operator<<(ostream &os, const Coppia<K, V> &Coppia) {
		os <<" <"<<Coppia.chiave<<", "<<Coppia.valore<<"> ";
		return (os);
	}


private:

	Chiave chiave;
	Valore valore;
};


//COSTRUTTORE
template<class K, class V> 
Coppia<K, V>::Coppia() {
}

//COSTRUTTORE con valori
template<class K, class V> 
Coppia<K, V>::Coppia(K k, V v) {
	chiave = k;
	valore = v;
}

//COSTRUTTORE DI COPIA
template<class K, class V> 
Coppia<K, V>::Coppia(const Coppia<K, V> & a) {
	chiave = a.chiave;
	valore = a.valore;
}

//RESTITUISCE LA CHIAVE
template<class K, class V> 
K Coppia<K, V>::getChiave() {
	return chiave;
}

//RESTITUISCE IL VALORE
template<class K, class V> 
V Coppia<K, V>::getValore() {
	return valore;
}

//IMPOSTA LA CHIAVE
template<class K, class V> 
void Coppia<K, V>::setChiave(K k) {
	chiave = k;
}

//IMPOSTA IL VALORE
template<class K, class V> 
void Coppia<K, V>::setValore(V &v) {
	valore = v;
}

//SOVRACCARICO OPERATORE '='
template<class K, class V> 
Coppia<K, V>& Coppia<K, V>::operator=(const Coppia<K, V> & a) {
	chiave = a.chiave;
	valore = a.valore;
	return *this;
}

//SOVRACCARICO OPERATORE ==
template<class K, class V> 
bool Coppia<K, V>::operator==(const Coppia<K, V> &pair) {
		return (chiave== pair.chiave) && (valore==pair.valore);
	}

#endif
