#ifndef ARCO_H
#define ARCO_H

#include <iostream>
#include <cstdlib>
using namespace std;

//tipo dell'elemento che sara usato nella lista di Arco del grafo pesato

template<class nodo,class tipoPeso> 
class Arco {
public:

    //costruttori (generico di default)
    Arco();
    Arco(nodo,tipoPeso);
    ~Arco();   //distruttore di default

    //setter e getter
    void scrivinodo(nodo);
    nodo legginodo() const;
    void scrivipeso(tipoPeso);
    tipoPeso leggipeso() const;


private:
    nodo adiacente;     //riferimento al nodo adiacente
    tipoPeso peso;      //peso dell'arco

};

//costruttore generico
template <class nodo,class tipoPeso> 
Arco<nodo,tipoPeso>::Arco() 
{
}

//costruttore specifico
template <class nodo,class tipoPeso> 
Arco<nodo,tipoPeso>::Arco(nodo n,tipoPeso p) {
    adiacente=n;
    peso=p;
}

template <class nodo,class tipoPeso> 
Arco<nodo,tipoPeso>::~Arco() {
    //dtor
}

template <class nodo,class tipoPeso> 
void Arco<nodo,tipoPeso>::scrivinodo(nodo n) {
    adiacente=n;
}

template <class nodo,class tipoPeso> 
void Arco<nodo,tipoPeso>::scrivipeso(tipoPeso p) {
    peso=p;
}

template <class nodo,class tipoPeso> 
nodo Arco<nodo,tipoPeso>::legginodo() const {
    return(adiacente);
}

template <class nodo,class tipoPeso> 
tipoPeso Arco<nodo,tipoPeso>::leggipeso() const {
    return(peso);
}

//sovraccarico output
template<class nodo,class tipoPeso> 
ostream& operator<<(ostream& os, const Arco<nodo,tipoPeso>& a) {
    os<<"("<<a.legginodo()<<"|"<<a.leggipeso()<<")";
    return(os);
}

#endif