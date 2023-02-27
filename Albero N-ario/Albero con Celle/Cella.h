#ifndef CELLA_H
#define CELLA_H

#include <iostream>
using namespace std;

template <class T>
class Cella {
public:
    typedef T tipoelem;

    Cella();            //COSTRUTTORE
    Cella(tipoelem);    //COSTRUTTORE DI COPIA
    ~Cella();           //DISTRUTTORE

    //OPERATORI--------------------------------
    //METODI SET
    void setEtichetta(tipoelem);
    void setPrimoFiglio(Cella*);
    void setFratelloSucc(Cella*);
    void setPadre(Cella*);

    //METODI GET
    Cella* getPrimoFiglio();
    tipoelem getEtichetta();
    Cella* getFratelloSucc();
    Cella* getPadre();

    //SOVRACCARICO OPERATORI------------------------------
    bool operator==(Cella);         //SOVRACCARICO OPERATORE UGUAGLIANZA ==
    void operator = (const Cella&);      //SOVRACCARICO OPERATORE ASSEGNAZIONE =

private:
    tipoelem etichetta;
    Cella* primoFiglio;
    Cella* fratelloSucc;
    Cella* padre;
};

//COSTRUTTORE
template <class T> Cella<T>::Cella() {
    T elemento;
    this->etichetta=elemento;
    this->primoFiglio=NULL;
    this->fratelloSucc=NULL;
    this->padre=NULL;
}

//DISTRUTTORE
template <class T> Cella<T>::~Cella() {}

//COSTRUTTORE DI COPIA
template <class T> Cella<T>::Cella(tipoelem a){
    this->etichetta=a;
    this->primoFiglio=NULL;
    this->fratelloSucc=NULL;
    this->padre=NULL;
}

//OPERATORI--------------------------------
//METODI SET
template <class T> void Cella<T>::setEtichetta(tipoelem a) {
    this->etichetta=a;
}

template <class T> void Cella<T>::setPrimoFiglio(Cella* a) {
    this->primoFiglio=a;
}

template <class T> void Cella<T>::setFratelloSucc(Cella* a) {
    this->fratelloSucc=a;
}

template <class T> void Cella<T>::setPadre(Cella* a) {
    this->padre=a;
}

//METODI GET
template <class T> T Cella<T>::getEtichetta() {
    return etichetta;
}

template <class T> Cella<T>* Cella<T>::getPrimoFiglio() {
    return primoFiglio;
}

template <class T> Cella<T>* Cella<T>::getFratelloSucc() {
    return fratelloSucc;
}

template <class T> Cella<T>* Cella<T>::getPadre() {
    return padre;
}

//SOVRACCARICO OPERATORE UGUAGLIANZA ==
template <class T> bool Cella<T>::operator==(Cella a) {
    return (this->etichetta==a.getEtichetta());
}

//SOVRACCARICO OPERATORE ASSEGNAZIONE =
template <class T>
void Cella<T>::operator=(const Cella<T>& c ){
    etichetta = c.etichetta;
    padre = c.padre;
    primoFiglio = c.primoFiglio;
    fratelloSucc = c.fratelloSucc;
}

#endif