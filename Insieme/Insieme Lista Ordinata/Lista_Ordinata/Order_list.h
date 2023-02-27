#ifndef _ORDER_LIST_H
#define _ORDER_LIST_H

#include "Node.h"
#include <iostream>
#include <ostream>

using namespace std;


//CLASSE Lista con puntatori doppi, circolare, composta da nodi------------------------------------------------------
template<class T>
class Order_list{       //la posizione è di tipo: puntatore a un nodo<T>
public:
	typedef T value_type;
	typedef Node<T>* position;

	//COSTRUTTORI
	Order_list();
	//COSTRUTTORE DI COPIA
	Order_list(const Order_list<T>& );
	//DISTRUTTORE
	~Order_list();

	//OPERATORI--------------------------------
	bool empty() const;                         //VERO SE LA LISTA E' VUOTA
	value_type read(position) const;            //LEGGE L'ELEMENTO DELLA LISTA IN POSIZIONE P
	position begin() const;                     //RESTITUISCE LA POSIZIONE INIZIALE
	bool end(position) const;                   //RESTITUISCE VERO SE LA POSIZIONE INDICATA E' LA SUCCESSIVA ALL'ULTIMO ELEMENTO (ovvero la posizione dopo l'ultimo elemento)
	position next(position) const;              //RESTITUISCE LA POSIZIONE SUCCESSIVA (se si è arrivati alla fine restituisce il puntatore alla testa)
	position previous(position) const;          //RESTITUISCE LA POSIZIONE PRECEDENTE (se si è gia arrivati all'inizio restituisce il puntatore alla testa)
	void insert(const value_type &);  			//INSERISCE UN ELEMENTO IN POSIZIONE 'p'
	void erase(position);                       //CANCELLA UN ELEMENTO IN POSIZIONE pos

	position last() const;              		//RESTITUISCE IL PUNTATORE ALL'ULTIMO NODO DELLA LISTA
    int size() const {return length;};  		//RESTITUISCE LA LUNGHEZZA

	//SOVRACCARICO OPERATORI
	Order_list<T>& operator=(const Order_list<T>&);   //SOVRACCARICO OPERATORE ASSEGNAZIONE =
	bool operator==(const Order_list<T> &) const;      //SOVRACCARICO OPERATORE UGUAGLIANZA ==

    friend ostream &operator<<(ostream &os, const Order_list<T> &l) {
	    Order_list<T>::position p;
	    p = l.begin();
	    os << "[";
	    while (!l.end(p)) {
		    if (p != l.begin()) {
			    os << ", " << l.read(p);
		    }
		    else {
			    os << l.read(p);
		    }
		    p = l.next(p);
	    }
	    os << "]" << endl;
	    return (os);
    }


    //Altri OPERATORI--------------------------
    void get();                         //STAMPA IL NUM DI ELEM

	//Rimuove l'elemento in testa alla lista
	void pop_front();
	//Rimuove l'elemento in fondo alla lista
	void pop_back();
	//Pulisce la lista e restituisce una lista vuota priva di elementi
	void clear();
	//Restituisce vero se una lista e' palindroma
	bool palindroma() const;
	//Rimuove un item dalla lista
	void remove(value_type);
	//Calcola il numero di elementi compresi fra le posizioni p1 e p2
	int num_elements(position, position);
	//Restituisce vero se l'elemento appartiene alla lista
	bool member(value_type) const;


 private:
	Node<T> * pHead;   //Puntatore alla testa della lista
	int length;             //Lunghezza lista, se la lista è vuota =0, il primo elem =1
};
//____________________________________________________________________________________________________________

//COSTRUTTORE
template< class T >
Order_list< T >::Order_list() {
	pHead = new Node<T>;
	pHead->setpNext(pHead);
	pHead->setpPrev(pHead);
	length = 0;
}

//COSTRUTTORE DI COPIA
template< class T >
Order_list<T>::Order_list(const Order_list<T>& L) {
    //inizializzo lo stato
    length = 0;
	pHead = new Node<T>;
	pHead->setpNext(pHead);
	pHead->setpPrev(pHead);

    //se non è vuoto copio gli elementi del secondo oggetto nel primo
	if (!L.empty()) {
		position p = L.last();
		for (int i=0; i < L.length; i++) {
			insert(L.read(p));
			p = L.previous(p);
		}
	}
}

//DISTRUTTORE
template< class T >
Order_list< T >::~Order_list(){
    //cancello tutti gli elementi nella lista
	while(!empty())
		erase(begin());

	delete pHead;
}

//OPERATORI--------------------------------
//VERO SE LA LISTA E' VUOTA
template< class T >
bool Order_list< T >::empty() const {
	return(pHead == pHead->getpNext());
}

//LEGGE L'ELEMENTO DELLA LISTA IN POSIZIONE p
template< class T >
typename Order_list< T >::value_type
Order_list< T >::read(position p) const {
	if(!end(p))
		return(p->getValue());
	else return -1;
}

//RESTITUISCE LA POSIZIONE INIZIALE
template< class T >
typename Order_list< T >::position
Order_list< T >::begin() const {
	return (pHead->getpNext());
}

//RESTITUISCE VERO SE LA POSIZIONE INDICATA E' LA SUCCESSIVA ALL'ULTIMO ELEMENTO (ovvero la posizione dopo l'ultimo elemento)
template< class T >
bool Order_list< T >::end(position p) const {
	return(p == pHead);
}

//RESTITUISCE LA POSIZIONE SUCCESSIVA (se si è arrivati alla fine restituisce il puntatore alla testa)
template< class T >
typename Order_list< T >::position
Order_list< T >::next(position p) const {
    if(p!=pHead)
	    return(p->getpNext());
	else return (p);
}

//RESTITUISCE LA POSIZIONE PRECEDENTE (se si è gia arrivati all'inizio restituisce il puntatore alla testa)
template< class T >
typename Order_list< T >::position Order_list< T >::previous(position p) const {
	if (p != pHead)
		return(p->getpPrev());
	else return (p);
}

//INSERISCE UN ELEMENTO IN POSIZIONE 'p'
template< class T >
void Order_list< T >::insert(const value_type &a){
    position p = begin();
    if(!empty())
        while(read(p) < a && !end(p))
            p = next(p);


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
void Order_list< T >::erase(position p){
	if (!empty() && !end(p)){
		(p->getpPrev())->setpNext(p->getpNext());
		(p->getpNext())->setpPrev(p->getpPrev());
		delete p;
		length--;
	}
}

//RESTITUISCE IL PUNTATORE ALL'ULTIMO NODO DELLA LISTA
template< class T >
typename Order_list<T>::position Order_list<T>::last() const {
	return (pHead->getpPrev());
}


//SOVRACCARICO OPERATORI
//SOVRACCARICO OPERATORE ASSEGNAZIONE =
template<class T>
Order_list<T>& Order_list<T>::operator=(const Order_list<T>& L){
	if (this != &L){

		pHead = new Node<T>;
		pHead->setpNext(pHead);
		pHead->setpPrev(pHead);
		length = 0;

		if (!L.empty()) {
            position p = L.last();
			for (int i=0; i < L.size(); i++) {
				insert(L.read(p));
				p = L.previous(p);
			}
		}
	}
	return *this;
}

//SOVRACCARICO OPERATORE UGUAGLIANZA ==
template<class T>
bool Order_list<T>::operator==(const Order_list<T> &L) const{
	
	if (L.size() != size())
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
void Order_list<T>::get() {
    cout<<"\n Dim Num elem-->"<< length;
}

//Rimuove l'elemento in testa alla lista
template <class T>
void Order_list<T>::pop_front() {
	erase(begin());
}

//Rimuove l'elemento in fondo alla lista
template <class T>
void Order_list<T>::pop_back() {
	erase(last());
}

//Pulisce la lista e restituisce una lista vuota priva di elementi
template <class T>
void Order_list<T>::clear() {
	while (!this->empty()) {
		this->pop_front();
	}
}

//Restituisce vero se una lista e' palindroma
template <class T>
bool Order_list<T>::palindroma() const {
	if (this->size() < 2) {
		return (true);
	}
	else {
		//verfico se la lista e' palindroma
		bool flag = true;
		auto prev = last();
		for (auto curr = begin(); !end(curr) && (flag); curr = next(curr)) {
			if (read(curr) != read(prev)) {
				flag = false;
			}
			prev = previous(prev);
		}
		return (flag);
	}
}

//Rimuove un item dalla lista
template <class T>
void Order_list<T>::remove(value_type el) {
	bool found = false;
	auto pos = begin();
	while (!end(pos) && !found) {
		if (read(pos) == el) {
			found = true;
		}
		else {
			pos = next(pos);
		}
	}
	if (found) {
		this->erase(pos);
	}
}

//Calcola il numero di elementi compresi fra le posizioni p1 e p2
template <class T>
int Order_list<T>::num_elements(position p1, position p2) {
	int n = 0;
	auto pos = p1;
	while (!end(pos) && next(pos) != p2) {
		n++;
		pos = next(pos);
	}
	return (n);
}

//Restituisce vero se l'elemento appartiene alla lista
template <class T>
bool Order_list<T>::member(value_type el) const {
	bool found = false;
	if (!empty()) {
		for (auto i = begin(); !end(i) && !found; i = next(i)) {
			if (read(i) == el) {
				found = true;
			}
		}
	}
	return (found);
}

#endif