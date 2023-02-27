#ifndef INSIEME_H
#define INSIEME_H

#include "Lista\Linked_list.h"

template <class tipoelem>
class Insieme {
public:
    typedef typename Linked_list<tipoelem>::position posizione;

	Insieme(const Insieme&);    //COSTRUTTORE DI COPIA
    Insieme();                  //COSTRUTTORE

    //OPERATORI--------------------------------
	bool insiemevuoto() const;                      //VERO SE L'INSIEME E' VUOTO
	bool appartiene(const tipoelem& e) const;       //VERO L'ELEMENTO INSERITO E' PRESENTE NELL'INSIEME
	void inserisci(const tipoelem& e);              //INSERISCE UN ELEMENTO NELL'INSIEME
	void cancella(const tipoelem& e);               //RIMUOVE UN ELEMENTO DALL'INSIEME

    //OPERATORI INSIEMISTICI-------------------
    //UNIONE: L'insieme conterrè gli elementi dell'insieme iniziale e l'insieme 'i'
	Insieme<tipoelem> unione(const Insieme& i);
    //INTERSEZIONE: L'insieme conterrè tutti e soli gli elementi presenti sia nell'insieme iniziale che in i.
	Insieme<tipoelem> intersezione(const Insieme& i);    
    //DIFFERENZA: L'insieme conterrè tutti e soli gli elementi iniziali che non appartengono anche a i.
	Insieme<tipoelem> differenza(const Insieme& i);

    //SOVRACCARICO OPERATORI
	bool operator==(Insieme<tipoelem> &);               //SOVRACCARICO OPERATORE UGUAGLIANZA ==         

    //Altri OPERATORI--------------------------
    void stampa() const;

private:
	Linked_list<tipoelem> setlist;
};
//____________________________________________________________________________________________________________

//COSTRUTTORE
template <class TipoElem>
Insieme<TipoElem>::Insieme() { }

//COSTRUTTORE DI COPIA
template <class tipoelem>
Insieme<tipoelem>::Insieme(const Insieme<tipoelem>& i) {
    setlist=Linked_list<tipoelem>(i.setlist);
}

//OPERATORI--------------------------------
//VERO SE L'INSIEME E' VUOTO
template <class tipoelem>
bool Insieme<tipoelem>::insiemevuoto() const {
    return setlist.empty();
}

//VERO L'ELEMENTO INSERITO E' PRESENTE NELL'INSIEME
template <class tipoelem>
bool Insieme<tipoelem>::appartiene(const tipoelem& e) const {
    return (setlist.member(e));
}

//INSERISCE UN ELEMENTO NELL'INSIEME
template <class tipoelem>
void Insieme<tipoelem>::inserisci(const tipoelem& e) {
    if (!appartiene(e))
        setlist.insert(e, setlist.begin());
}

//RIMUOVE UN ELEMENTO DALL'INSIEME
template <class tipoelem>
void Insieme<tipoelem>::cancella(const tipoelem& e) {
    setlist.remove(e);
}

//OPERATORI INSIEMISTICI-------------------
//UNIONE: L'insieme conterrè gli elementi dell'insieme iniziale e l'insieme 'C'
template <class tipoelem>
Insieme<tipoelem> Insieme<tipoelem>::unione(const Insieme<tipoelem>& i) {
    Insieme<tipoelem> A=i;
    posizione p = setlist.begin();
    i.stampa();
    
    while (!setlist.end(p)) {
		A.inserisci(setlist.read(p));
        p = setlist.next(p);
    }
    return(A);
}

//INTERSEZIONE: L'insieme conterrè tutti e soli gli elementi presenti sia nell'insieme iniziale che in i.
template <class tipoelem>
Insieme<tipoelem> Insieme<tipoelem>::intersezione(const Insieme<tipoelem>& i) {
    Insieme<tipoelem> A;
    posizione p = setlist.begin();

    if(insiemevuoto() || i.insiemevuoto())
        return A;
    
    while(!setlist.end(p)) {
        if(i.appartiene(setlist.read(p)) )
             A.inserisci(setlist.read(p));
        p = setlist.next(p);
    }

    return A;
}

//DIFFERENZA: L'insieme conterrè tutti e soli gli elementi iniziali che non appartengono anche a i.
template <class tipoelem>
Insieme<tipoelem> Insieme<tipoelem>::differenza(const Insieme<tipoelem>& i) {
    Insieme<tipoelem> A;
    posizione p = setlist.begin();

	while(!setlist.end(p)) {
		if(!i.appartiene(setlist.read(p)))
		    A.inserisci(setlist.read(p));
		p = i.setlist.next(p);
	}
    return A;
}

//Altri OPERATORI--------------------------
template <class tipoelem>
void Insieme<tipoelem>::stampa() const {
    cout<<setlist;
}

//SOVRACCARICO OPERATORI---------------------------------------------------------
//SOVRACCARICO OPERATORE ==
template<class tipoelem>
bool Insieme<tipoelem>::operator==(Insieme<tipoelem> &l){	
 return(l.setlist==this->setlist);
}

#endif

