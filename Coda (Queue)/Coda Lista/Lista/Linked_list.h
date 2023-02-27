#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include "Linear_list.h"
#include "Node.h"

#include <assert.h>

//CLASSE Lista con puntatori doppi, circolare, composta da nodi------------------------------------------------------
template< class T >
class Linked_list : public Linear_list<T, Node<T>*>, private Node<T>{       //la posizione è di tipo: puntatore a un nodo<T>
public:
	typedef typename Linear_list<T, Node<T>*>::value_type value_type;
	typedef typename Linear_list<T, Node<T>*>::position position;

	//COSTRUTTORI
	Linked_list();
	//COSTRUTTORE DI COPIA
	Linked_list(const Linked_list<T>& );
	//DISTRUTTORE
	~Linked_list();

	//OPERATORI--------------------------------
	bool empty() const;                         //VERO SE LA LISTA E' VUOTA
	value_type read(position) const;            //LEGGE L'ELEMENTO DELLA LISTA IN POSIZIONE P
	void write(const value_type &, position);   //MODIFICA L'ELEMENTO NELLA POSIZIONE INDICATA
	position begin() const;                     //RESTITUISCE LA POSIZIONE INIZIALE
	bool end(position) const;                   //RESTITUISCE VERO SE LA POSIZIONE INDICATA E' LA SUCCESSIVA ALL'ULTIMO ELEMENTO (ovvero la posizione dopo l'ultimo elemento)
	position next(position) const;              //RESTITUISCE LA POSIZIONE SUCCESSIVA (se si è arrivati alla fine restituisce il puntatore alla testa)
	position previous(position) const;          //RESTITUISCE LA POSIZIONE PRECEDENTE (se si è gia arrivati all'inizio restituisce il puntatore alla testa)
	void insert(const value_type &, position);  //INSERISCE UN ELEMENTO IN POSIZIONE 'p'
	void erase(position);                       //CANCELLA UN ELEMENTO IN POSIZIONE pos

	position last() const;              		//RESTITUISCE IL PUNTATORE ALL'ULTIMO NODO DELLA LISTA
    int size() const {return length;};  		//RESTITUISCE LA LUNGHEZZA

	//SOVRACCARICO OPERATORI
	Linked_list<T>& operator=(const Linked_list<T>&);   //SOVRACCARICO OPERATORE ASSEGNAZIONE =
	bool operator==(const Linked_list<T> &) const;      //SOVRACCARICO OPERATORE UGUAGLIANZA ==

    //Altri OPERATORI--------------------------
    void get();				//STAMPA IL NUM DI ELEM

 private:
	Node<T> * pHead;   //Puntatore alla testa della lista
	int length;             //Lunghezza lista, se la lista è vuota =0, il primo elem =1
};
//____________________________________________________________________________________________________________

//COSTRUTTORE
template< class T >
Linked_list< T >::Linked_list() {
	pHead = new Node<T>;
	pHead->setpNext(pHead);
	pHead->setpPrev(pHead);
	length = 0;
}

//COSTRUTTORE DI COPIA
template< class T >
Linked_list< T >::Linked_list(const Linked_list<T>& L) {
    //inizializzo lo stato
    length = 0;
	pHead = new Node<T>;
	pHead->setpNext(pHead);
	pHead->setpPrev(pHead);

    //se non è vuoto copio gli elementi del secondo oggetto nel primo
	if (!L.empty()) {
		position p = L.last();
		for (int i=0; i < L.length; i++) {
			insert(L.read(p), begin());
			p = L.previous(p);
		}
	}
}

//DISTRUTTORE
template< class T >
Linked_list< T >::~Linked_list(){
    //cancello tutti gli elementi nella lista
	while(!empty())
		erase(begin());

	delete pHead;
}

//VERO SE LA LISTA E' VUOTA
template< class T >
bool Linked_list< T >::empty() const {
	return(pHead == pHead->getpNext());
}

//LEGGE L'ELEMENTO DELLA LISTA IN POSIZIONE p
template< class T >
typename Linked_list< T >::value_type
Linked_list< T >::read(position p) const {
	assert(!end(p));
		return(p->getValue());
}

//MODIFICA L'ELEMENTO NELLA POSIZIONE INDICATA
template< class T >
void Linked_list< T >::write(const value_type &a, position p) {
	assert(!end(p));
        p->setValue(a);
}

//RESTITUISCE LA POSIZIONE INIZIALE
template< class T >
typename Linked_list< T >::position
Linked_list< T >::begin() const {
	return (pHead->getpNext());
}

//RESTITUISCE VERO SE LA POSIZIONE INDICATA E' LA SUCCESSIVA ALL'ULTIMO ELEMENTO (ovvero la posizione dopo l'ultimo elemento)
template< class T >
bool Linked_list< T >::end(position p) const {
	return(p == pHead);
}

//RESTITUISCE LA POSIZIONE SUCCESSIVA (se si è arrivati alla fine restituisce il puntatore alla testa)
template< class T >
typename Linked_list< T >::position
Linked_list< T >::next(position p) const {
    if(p!=pHead)
	    return(p->getpNext());
	else return (p);
}

//RESTITUISCE LA POSIZIONE PRECEDENTE (se si è gia arrivati all'inizio restituisce il puntatore alla testa)
template< class T >
typename Linked_list< T >::position Linked_list< T >::previous(position p) const {
	if (p != pHead)
		return(p->getpPrev());
	else return (p);
}

//INSERISCE UN ELEMENTO IN POSIZIONE 'p'
template< class T >
void Linked_list< T >::insert(const value_type &a, position p){
	position t = new Node<T>;
	t->setValue(a);
	t->setpNext(p);
	t->setpPrev(p->getpPrev());
	
	(p->getpPrev())->setpNext(t);
	p->setpPrev(t);

	length++;
}

//CANCELLA UN ELEMENTO IN POSIZIONE pos
template< class T >
void Linked_list< T >::erase(position p){
	if(!empty() && !end(p)){
		(p->getpPrev())->setpNext(p->getpNext());
		(p->getpNext())->setpPrev(p->getpPrev());
		delete p;
		length--;
	}
}

//RESTITUISCE IL PUNTATORE ALL'ULTIMO NODO DELLA LISTA
template< class T >
typename Linked_list< T >::position
Linked_list< T >::last() const {
	return (pHead->getpPrev());
}


//SOVRACCARICO OPERATORI
//SOVRACCARICO OPERATORE ASSEGNAZIONE =
template<class T>
Linked_list<T>& Linked_list<T>::operator=(const Linked_list<T>& L){
	if (this != &L){
		length = 0;

		pHead = new Node<T>;
		pHead->setpNext(pHead);
		pHead->setpPrev(pHead);

		if (!L.empty()) {
            position p = L.last();
			for (int i=0; i < L.size(); i++) {
				insert(L.read(p), begin());
				p = L.previous(p);
			}
		}
	}
	return *this;
}

//SOVRACCARICO OPERATORE UGUAGLIANZA ==
template<class T>
bool Linked_list<T>::operator==(const Linked_list<T> &L) const{
	if (L.size() != length)
		return false;

	position p, pL;
	p = begin();
	pL = L.begin();
	while (!end(p)){
		if (p->getValue() != pL->getValue())
			return false;
		p = p->getpNext();
		pL = pL->getpNext();
	}
	return true;
}

//Altri OPERATORI--------------------------

//STAMPA IL NUM DI ELEM
template<class T>
void Linked_list<T>::get() {
    cout<<"\n Dim Num elem-->"<< length;
}

#endif
