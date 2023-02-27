#ifndef CODA_H
#define CODA_H

#include <iostream>
#include <assert.h>
using namespace std;

//CODA REALIZZATA TRAMITE VETTORE CIRCOLARE
template<class T>
class Coda {
public:
    typedef T tipoelem;

    Coda();             //COSTRUTTORE
    Coda(int);          //COSTRUTTORE con dim
    Coda(Coda<T>& l);   //COSTRUTTORE di copia
    ~Coda();            //DISTRUTTORE

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
    int dimCoda() { return dim; };

private:
    tipoelem* elementi; //Vettore di elementi
    int testa;          //Posizione primo elemento
    int lunghezza;      //Numero di elementi nella coda
    int dim;            //Dimensione Arrey
};

//____________________________________________________________________________________________________________

//COSTRUTTORE
template<class T>
Coda<T>::Coda() {
    dim = 100;
    elementi=new tipoelem[dim];
    testa = 0;
    lunghezza = 0;
}

//COSTRUTTORE  con dim
template<class T>
Coda<T>::Coda(int n) {
    dim = n;
    elementi=new tipoelem[dim];
    testa = 0;
    lunghezza = 0;
}

//COSTRUTTORE di copia
template<class T>
Coda<T>::Coda(Coda<T>& l){
    
    elementi=new tipoelem[l.dimCoda()];
    testa = 0;
    lunghezza = 0;

    int i=l.testa;
    int j=0;
    while(j<l.lunghezza) {
        incoda(l.elementi[i % dim]);
        i++;
        j++;
    }
}

//DISTRUTTORE
template<class T>
Coda<T>::~Coda() {
    delete[] elementi;
}

//OPERATORI-------------------------------- 

//CONTROLLA SE LA CODA E' VUOTA
template<class T>
bool Coda<T>::codavuota() const {
    return (lunghezza == 0);
}

//LEGGE E RESTITUISCE L'ELEMENTO IN ULTIMA POSIZIONE, OVVERO IL PRIMO INSERITO
template<class T>
T Coda<T>::leggicoda() const {
    assert(!codavuota());
    return elementi[testa];
}

//ELIMINA L'ULTIMO ELEMENTO DELLA CODA, OVVERO IL PRIMO INSERITO
template<class T>
void Coda<T>::fuoricoda() {
    assert(!codavuota());
    testa = (testa + 1) % dim;
    lunghezza--;
}

//INSERISCE UN ELEMENTO IN TESTA ALLA CODA
template<class T>
void Coda<T>::incoda(tipoelem e) {
    assert(lunghezza < dim);
    elementi[(testa + lunghezza) % dim] = e;
    lunghezza++;
}

//Altri OPERATORI--------------------------
//Stampa Coda
template<class T>
void Coda<T>::stampacoda() {
    cout<<"\n["; 
    int i=testa;
    int j=0;

    while(j<lunghezza) {
        cout<<elementi[i % dim]<<",";
        i++;
        j++;
    }
    cout<<"]";
}    

//SOVRACCARICO OPERATORI---------------------------------------------------------
//SOVRACCARICO OPERATORE =
template<class T>
Coda<T>& Coda<T>::operator=(Coda<T>& l){
    
    elementi=new tipoelem[l.dimCoda()];
    testa = 0;
    lunghezza = 0;

    int i=l.testa;
    int j=0;
    while(j<l.lunghezza) {
        incoda(l.elementi[i % dim]);
        i++;
        j++;
    }

    return *this;
}

//SOVRACCARICO OPERATORE ==
template<class T>
bool Coda<T>::operator==(Coda<T> &l){	

    if(codavuota() && l.codavuota())
        return true;
  
    int i=l.testa;
    int j=0;

    int i2=l.testa;
    int j2=0;

    if(size() == l.size()){
        while(j<l.lunghezza) {
            if(elementi[i2 % dim]!=l.elementi[i % l.dim])
                return false;
            i++;
            j++;

            i2++;
            j2++;
        }
    }
    else 
        return false;
    
	return true;
}

#endif
