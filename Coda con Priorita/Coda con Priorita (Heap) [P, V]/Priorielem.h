#ifndef _PRIORIELEM_H
#define _PRIORIELEM_H

#include <iostream>
#include <cstdlib>

using namespace std;

//tipo di elemento della coda con priorita
template<class X> class Priorielem {
public:
    typedef float priorita; //la priorità è di tipo numerico (valore minore=priorità più alta)
    typedef X tipoelem;

    //COSTRUTTORE
    Priorielem();
    Priorielem(const Priorielem&);
    Priorielem(priorita,tipoelem);

    //distruttore di default

    //METODI SET E GET
    void scrivipriorita(priorita);
    priorita leggipriorita() const;
    void scrivielem(tipoelem);
    tipoelem leggielem() const;

    //SOVRACCARICO OPERATORI
    void operator=(Priorielem);
    bool operator==(Priorielem);
    bool operator<(Priorielem);
    bool operator>(Priorielem);

private:
    priorita prior;     //Priorità
    tipoelem elem;      //Valore

};

//COSTRUTTORE generico
template <class X> Priorielem<X>::Priorielem() {
    prior=9999;
}

//COSTRUTTORE di copia
template <class X> Priorielem<X>::Priorielem(const Priorielem& p)  {
    prior=p.leggipriorita();
    elem=p.leggielem();
}

//COSTRUTTORE specifico
template <class X> Priorielem<X>::Priorielem(priorita p,tipoelem e) {
    prior=p;
    elem=e;
}

//METODI SET E GET
template <class X> void Priorielem<X>::scrivipriorita(priorita p) {
    prior=p;
}

template <class X> void Priorielem<X>::scrivielem(tipoelem e) {
    elem=e;
}

template <class X> float Priorielem<X>::leggipriorita() const {
    return(prior);
}

template <class X> X Priorielem<X>::leggielem() const {
    return(elem);
}

//SOVRACCARICO OPERATORI
//assegnamento
template <class X> void Priorielem<X>::operator=(Priorielem<X> p) {
    prior=p.leggipriorita();
    elem=p.leggielem();
}

//uguaglianza
template <class X> bool Priorielem<X>::operator==(Priorielem<X> p) {
    return (elem==p.leggielem());
}

//maggioranza (solo sulla priorità)
template <class X> bool Priorielem<X>::operator<(Priorielem<X> p) {
    return (prior<p.leggipriorita());
}

//minoranza (solo sulla priorità)
template <class X> bool Priorielem<X>::operator>(Priorielem<X> p) {
    return (prior>p.leggipriorita());
}

//sovraccarico output
template<class X> ostream& operator<<(ostream& os, const Priorielem<X>& p) {
    os<<"("<<p.leggipriorita()<<"|"<<p.leggielem()<<")";
    return(os);
}

#endif