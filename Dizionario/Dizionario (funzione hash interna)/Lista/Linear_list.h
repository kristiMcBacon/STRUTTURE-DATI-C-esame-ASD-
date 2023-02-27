#ifndef _LINEAR_LIST_H
#define _LINEAR_LIST_H

#include <iostream>
#include <ostream>

using namespace std;

//CLASSE astratta Lista Linare------------------------------------------------------------------------
template<class T, class P>
class Linear_list{
public:
	typedef T value_type;   //tipo del oggetto salvato nella lista
	typedef P position;     //posizione

	//OPERATORI---------------------------------
	virtual bool empty() const = 0;                         //VERO SE LA LISTA E' VUOTA =0
	virtual value_type read(position) const = 0;            //LEGGE L'ELEMENTO DELLA LISTA IN POSIZIONE p
	virtual void write(const value_type &, position) = 0;   //MODIFICA L'ELEMENTO NELLA POSIZIONE INDICATA
	virtual position begin() const = 0;                     //RESTITUISCE LA POSIZIONE INIZIALE
	virtual bool end(position) const = 0;                   //RESTITUISCE VERO SE LA POSIZIONE INDICATA E' LA SUCCESSIVA ALL'ULTIMO ELEMENTO (ovvero la posizione dopo l'ultimo elemento)
	virtual position next(position) const = 0;              //RESTITUISCE LA POSIZIONE SUCCESSIVA (se si è arrivati alla fine restituisce ...)
	virtual position previous(position) const = 0;          //RESTITUISCE LA POSIZIONE PRECEDENTE (se si è gia arrivati all'inizio restituisce ...)
	virtual void insert(const value_type &, position) = 0;  //INSERISCE UN ELEMENTO IN POSIZIONE 'p', SE LA LISTA E PIENA ALLOCA NUOVO SPAZIO PER IL NUOVO ELEMENTO DA INSERIRE
	virtual void erase(position pos) = 0;                   //CANCELLA UN ELEMENTO IN POSIZIONE pos
	virtual position last() const = 0;						//RESTITUISCE L'ULTIMA POSIZIONE DELLA LISTA

	//FUNZIONI DI SERVIZIO---------------------
	//Restituisce la lunghezza della lista ovvero il numero di elementi
	int size() const;
	//Inserisce un item v in testa alla lista
	void push_front(value_type);
	//Inserisce un elemento v in fondo alla lista, il valore viene quindi inserito nella posizione successiva all'ultimo elemento
	void push_back(value_type);
	//Rimuove l'elemento in testa alla lista
	void pop_front();
	//Rimuove l'elemento in fondo alla lista
	void pop_back();
	//Pulisce la lista e restituisce una lista vuota priva di elementi
	void clear();
	//Inverte gli elementi di una lista
	void reverse();
	//Restituisce vero se una lista e' palindroma
	bool palindroma() const;
	//Rimuove un item dalla lista
	void remove(value_type);
	//Calcola il numero di elementi compresi fra le posizioni p1 e p2
	int num_elements(position, position);
	//Scambia l'elemento in posizione p1 con quello in posizione p2
	void exchange(position, position);
	//Restituisce vero se l'elemento appartiene alla lista
	bool member(value_type) const;

    //SOVRACCARICO OPERATORE STAMPA: che permette di stampare tutti gli elementi di una lista
	friend ostream &operator<<(ostream &os, const Linear_list<T, P> &l) {
		Linear_list<T, P>::position p;
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
};

//FUNZIONI DI SERVIZIO---------------------

//Restituisce la lunghezza della lista ovvero il numero di elementi
template <class T, class P>
int Linear_list<T, P>::size() const {
	int count = 0;
	for (auto pos = begin(); !end(pos); pos = next(pos)) {
		read(pos);
		count++;
	}
	return (count);
}

//Inserisce un item v in testa alla lista
template <class T, class P>
void Linear_list<T, P>::push_front(value_type el) {
	insert(el, begin());
}

//Inserisce un elemento v in fondo alla lista, il valore viene quindi inserito nella posizione successiva all'ultimo elemento
template <class T, class P>
void Linear_list<T, P>::push_back(value_type el) {
	insert(el, next(last()) );
}

//Rimuove l'elemento in testa alla lista
template <class T, class P>
void Linear_list<T, P>::pop_front() {
	erase(begin());
}

//Rimuove l'elemento in fondo alla lista
template <class T, class P>
void Linear_list<T, P>::pop_back() {
	erase(last());
}

//Pulisce la lista e restituisce una lista vuota priva di elementi
template <class T, class P>
void Linear_list<T, P>::clear() {
	while (!this->empty()) {
		this->pop_front();
	}
}

//Inverte gli elementi di una lista
template <class T, class P>
void Linear_list<T, P>::reverse() {
	auto poslast = last();
	int lunghezza_media = this->size() / 2;
	int i = 0;
	for (auto pos = begin(); !end(pos) && (i < lunghezza_media); pos = next(pos)) {
		T temp = read(pos);
		write(read(poslast), pos);
		write(temp, poslast);
		poslast = previous(poslast);
		i++;
	}
}

//Restituisce vero se una lista e' palindroma
template <class T, class P>
bool Linear_list<T, P>::palindroma() const {
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
template <class T, class P>
void Linear_list<T, P>::remove(value_type el) {
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
template <class T, class P>
int Linear_list<T, P>::num_elements(position p1, position p2) {
	int n = 0;
	auto pos = p1;
	while (!end(pos) && next(pos) != p2) {
		n++;
		pos = next(pos);
	}
	return (n);
}

//Scambia l'elemento in posizione p1 con quello in posizione p2
template <class T, class P>
void Linear_list<T, P>::exchange(position p1, position p2) {
	if (!empty() && (p1 != p2)) {
		T temp = read(p1);
		write(read(p2), p1);
		write(temp, p2);
	}
}

//Restituisce vero se l'elemento appartiene alla lista
template <class T, class P>
bool Linear_list<T, P>::member(value_type el) const {
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