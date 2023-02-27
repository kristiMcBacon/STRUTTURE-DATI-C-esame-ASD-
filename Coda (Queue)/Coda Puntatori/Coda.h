#ifndef CODA_H
#define CODA_H

#include "Cella.h"

#include <iostream>
#include <assert.h>

using namespace std;

//CODA REALIZZATA TRAMITE PUNTATORI (Celle)
template <class T>
class Coda: private Cella<T>{
public:
    typedef T tipoelem;
    typedef Cella<T>* posizione;
    
    Coda();                     //COSTRUTTORE
    Coda(Coda<T>&);   //COSTRUTTORE DI COPIA
    ~Coda();                    //DISTRUTTORE

    //OPERATORI--------------------------------        
    bool codavuota() const;         //CONTROLLA SE LA CODA E' VUOTA
    tipoelem leggicoda() const;     //LEGGE E RESTITUISCE L'ELEMENTO IN ULTIMA POSIZIONE, OVVERO IL PRIMO INSERITO
    void incoda(tipoelem);          //INSERISCE UN ELEMENTO IN TESTA ALLA CODA
    void fuoricoda();               //ELIMINA L'ULTIMO ELEMENTO DELLA CODA, OVVERO IL PRIMO INSERITO

    //Altri OPERATORI--------------------------
    void stampacoda();      //Stampa Coda 
    int size() { return lunghezza; }

    //SOVRACCARICO OPERATORI
	Coda<T>& operator=(Coda<T> &);   //SOVRACCARICO OPERATORE ASSEGNAZIONE =
	bool operator==(Coda<T> &);      //SOVRACCARICO OPERATORE UGUAGLIANZA ==

private:
    posizione testa;    //Puntatore alla cella testa della coda
    posizione fondo;    //Puntatore alla cella fondo della coda
    int lunghezza;      //num. elem della coda
};

//____________________________________________________________________________________________________________

//COSTRUTTORE
template <class tipoelem>
Coda<tipoelem>::Coda() {
    testa=nullptr;
    fondo=nullptr;
    lunghezza = 0;
}

//COSTRUTTORE di copia
template<class T>
Coda<T>::Coda(Coda<T>& l){
    testa=nullptr;
    fondo=nullptr;
    lunghezza = 0;

    posizione temp=new Cella<tipoelem>;
    temp=l.testa;
    int j=0;

    while(j<l.lunghezza) {
        incoda( temp->leggiCella() );
        temp=temp->leggiSucc();
        j++;
    }
}

//DISTRUTTORE
template <class tipoelem>
Coda<tipoelem>::~Coda() {
    while(!codavuota()) {
        fuoricoda();
    }
}

//OPERATORI-------------------------------- 

//CONTROLLA SE LA CODA E' VUOTA
template <class tipoelem>
bool Coda<tipoelem>::codavuota() const {
    return (testa==nullptr);
}

//LEGGE E RESTITUISCE L'ELEMENTO IN ULTIMA POSIZIONE, OVVERO IL PRIMO INSERITO
template <class tipoelem>
tipoelem Coda<tipoelem>::leggicoda() const {
    assert(!codavuota());
    return testa->leggiCella();
}

//ELIMINA L'ULTIMO ELEMENTO DELLA CODA, OVVERO IL PRIMO INSERITO
template <class tipoelem>
void Coda<tipoelem>::fuoricoda() {
    assert(!codavuota());
	posizione temp=testa;
	testa=testa->leggiSucc();
	delete temp;
    lunghezza--;
}

//INSERISCE UN ELEMENTO IN TESTA ALLA CODA
template <class tipoelem>
void Coda<tipoelem>::incoda(tipoelem e) {
	posizione temp=new Cella<tipoelem>;
    temp->scriviCella(e);
	temp->scriviSucc(nullptr);

	if(!codavuota()){
		fondo->scriviSucc(temp);
		fondo=temp;
	}else{
	    testa=temp;
	    fondo=temp;
	}
    lunghezza++;
}

//Altri OPERATORI--------------------------
//Stampa Coda
template<class T>
void Coda<T>::stampacoda() {
    posizione temp=new Cella<tipoelem>;
    temp=testa;
    int j=0;
    cout<<"\n[";

    while(j<lunghezza) {
        cout<<temp->leggiCella()<<",";
        temp=temp->leggiSucc();
        j++;
    }
    cout<<"]";
}    

//SOVRACCARICO OPERATORI---------------------------------------------------------
//SOVRACCARICO OPERATORE =
template<class T>
Coda<T>& Coda<T>::operator=(Coda<T>& l){
    testa=nullptr;
    fondo=nullptr;
    lunghezza = 0;

    posizione temp=new Cella<tipoelem>;
    temp=l.testa;
    int j=0;

    while(j<l.lunghezza) {
        incoda( temp->leggiCella() );
        temp=temp->leggiSucc();
        j++;
    }
    return *this;
}

//SOVRACCARICO OPERATORE ==
template<class T>
bool Coda<T>::operator==(Coda<T> &l){	

    if(codavuota() && l.codavuota())
        return true;

    if(size() == l.size()){
        posizione temp=new Cella<tipoelem>;
        temp=testa;

        posizione temp2=new Cella<tipoelem>;
        temp2=l.testa;

        int j=0;

        while(j<l.lunghezza) {
            if(temp->leggiCella() != temp2->leggiCella())
                return false;
            temp=temp->leggiSucc();
            temp2=temp2->leggiSucc();
            j++;
        }
    }
    else 
        return false;
    
	return true;
}


#endif