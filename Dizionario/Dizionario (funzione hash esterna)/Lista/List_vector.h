#ifndef _LIST_VECTOR_H
#define _LIST_VECTOR_H

#include "Linear_list.h"
#include <assert.h>

//CLASSE Lista con vettori, la posizione è di tipo 'int'--------------------------------------
template<class T>
class List_vector : public Linear_list<T, int>{
 public:
	typedef typename Linear_list<T, int>::value_type value_type;
	typedef typename Linear_list<T, int>::position position;

	//COSTRUTTORE
	List_vector();
	List_vector(int);
	//COSTRUTTORE DI COPIA
	List_vector(const List_vector<T>& );
	//DISTRUTTORE
	~List_vector();

	//OPERATORI--------------------------------
	bool empty() const;                         //VERO SE LA LISTA E' VUOTA =0
	value_type read(position) const;            //LEGGE L'ELEMENTO DELLA LISTA IN POSIZIONE P
	void write(const value_type &, position);   //MODIFICA L'ELEMENTO NELLA POSIZIONE INDICATA
	position begin() const;                     //RESTITUISCE LA POSIZIONE INIZIALE
	bool end(position) const;                   //RESTITUISCE VERO SE LA POSIZIONE INDICATA E' LA SUCCESSIVA ALL'ULTIMO ELEMENTO (ovvero la posizione dopo l'ultimo elemento)
	position next(position) const;              //RESTITUISCE LA POSIZIONE SUCCESSIVA (se si è arrivati alla fine restituisce la posizione passata in input)
	position previous(position) const;          //RESTITUISCE LA POSIZIONE PRECEDENTE (se si è gia arrivati all'inizio restituisce la posizione passata in input)
	void insert(const value_type &, position);  //INSERISCE UN ELEMENTO IN POSIZIONE 'p', SE LA LISTA E PIENA ALLOCA NUOVO SPAZIO PER IL NUOVO ELEMENTO DA INSERIRE
	void erase(position);                       //CANCELLA UN ELEMENTO IN POSIZIONE pos
    position last() const;                      //RESTITUISCE L'ULTIMA POSIZIONE DELLA LISTA

	//SOVRACCARICO OPERATORI
	List_vector<T>& operator=(const List_vector<T> &);  //SOVRACCARICO OPERATORE ASSEGNAZIONE =
	bool operator==(const List_vector<T> &) const;      //SOVRACCARICO OPERATORE UGUAGLIANZA ==

    //Altri OPERATORI--------------------------
    void get();                     //STAMPA LA DIM DELL'ARRAY E IL NUM DI ELEM

 private:
	void change_dimension(T*& , int , int );    //MODIFICA LA DIMENSIONE DELLA LISTA
	value_type* elements;                       //Puntatore all'elemento
	int length;                                 //Lunghezza lista, se la lista è vuota =0, il primo elem =1
	int array_dimension;                        //Dimensione array
};
//____________________________________________________________________________________________________________

//COSTRUTTORE
template<class T>
List_vector<T>::List_vector() {
  array_dimension = 10;
  this->elements = new T[array_dimension];
  this->length = 0;
}

//COSTRUTTORE con dimensione indicata
template<class T>
List_vector<T>::List_vector(int dim) {
  array_dimension = dim;
  this->elements = new T[array_dimension];
  this->length = 0;
}

//COSTRUTTORE DI COPIA
template<class T>
List_vector<T>::List_vector(const List_vector<T>& Lista) {
  this->array_dimension = Lista.array_dimension;
  this->length = Lista.length;
  this->elements = new T[array_dimension];
  for (int i=0; i<Lista.array_dimension; i++)
     this->elements[i] = Lista.elements[i];
}

//DISTRUTTORE
template< class T >
List_vector< T >::~List_vector(){
	delete[] elements;
}

//MODIFICA LA DIMENSIONE DELLA LISTA
template<class T>
void List_vector< T >::change_dimension(T*& a, int vecchiaDim, int nuovaDim){
  T* temp = new T[nuovaDim];
  int number;
  if (vecchiaDim < nuovaDim)
     number = vecchiaDim;
  else
     number = nuovaDim;

  for (int i=0; i<number; i++)
     temp[i]=a[i];
  delete [] a;
  a = temp;
}

//OPERATORI--------------------------------------------------------------
//VERO SE LA LISTA E' VUOTA
template<class T>
bool List_vector<T>::empty() const {
    return(length == 0);
}

//LEGGE L'ELEMENTO DELLA LISTA IN POSIZIONE P
template<class T>
typename List_vector<T>::value_type List_vector<T>::read(position p) const {
	assert( !((p < 1) || (p > length)) );
		return(elements[p-1]);
    //else 
    //    return -1;
}

//MODIFICA L'ELEMENTO NELLA POSIZIONE INDICATA
template<class T>
void List_vector<T>::write(const value_type &a, position p) {
  if ( (p > 0) && (p < length+1))
    elements[p-1] = a;
}

//RESTITUISCE LA POSIZIONE INIZIALE
template< class T >
typename List_vector< T >::position List_vector< T >::begin() const {
	return(1);
}

//RESTITUISCE VERO SE LA POSIZIONE INDICATA E' LA SUCCESSIVA ALL'ULTIMO ELEMENTO (ovvero la posizione dopo l'ultimo elemento)
template< class T >
bool List_vector< T >::end(position p) const {
	if ( (0 < p) && (p <= length+1)) 
		return(p == length+1);
	else
		return(false);
}

//RESTITUISCE LA POSIZIONE SUCCESSIVA (se si è arrivati alla fine restituisce la posizione passata in input)
template< class T >
typename List_vector< T >::position List_vector< T >::next(position p) const {
	if ( (0 < p) && (p < length+1))
		return(p+1);
	else
		return(p);
}

//RESTITUISCE LA POSIZIONE PRECEDENTE (se si è gia arrivati all'inizio restituisce la posizione passata in input)
template< class T >
typename List_vector< T >::position List_vector< T >::previous(position p) const {
	if ( (1 < p) && (p < length+1))
		return(p-1);
	else
		return(p);
}

//INSERISCE UN ELEMENTO IN POSIZIONE 'p', SE LA LISTA E PIENA ALLOCA NUOVO SPAZIO PER IL NUOVO ELEMENTO DA INSERIRE
template< class T >
void List_vector< T >::insert(const value_type &a, position p){
  if (length == array_dimension) {
    change_dimension(elements, array_dimension, array_dimension*2);
    array_dimension = array_dimension*2;
  }

  if ( (0 < p) && (p <= length+1)) {
		for (int i=length; i>=p; i--)
			elements[i] = elements[i-1];

		elements[p-1]=a;
		length++;
	}
}

//CANCELLA UN ELEMENTO IN POSIZIONE POS
template< class T >
void List_vector< T >::erase(position p){
  if ( (0 < p) && ( p < length + 1))
    if (!empty()) {
		for (int i=p-1;i<(length-1);i++)
			elements[i]=elements[i+1];
		length--;
	}
}

//RESTITUISCE L'ULTIMA POSIZIONE DELLA LISTA
template <class T>
typename List_vector<T>::position List_vector<T>::last() const {
	position pos = begin();
	while (!end(next(pos))) {
		pos = next(pos);
	}
	return (pos);
}

//SOVRACCARICO OPERATORI---------------------------------------------------------
//SOVRACCARICO OPERATORE =
template<class T>
List_vector<T>& List_vector<T>::operator=(const List_vector<T>& l){
	if (this != &l) {
		this->array_dimension = l.array_dimension;
		this->length = l.length;

		delete this->elements;
		this->elements = new T[array_dimension];

		for (int i=0; i<l.array_dimension; i++)
			this->elements[i] = l.elements[i];
	}
	return *this;
}

//SOVRACCARICO OPERATORE ==
template<class T>
bool List_vector<T>::operator==(const List_vector<T> &l) const{
	if (l.length != this->length)
		return false;
		
    for (int i=0; i<this->length; i++) {
        if (this->elements[i] != l.elements[i])
			return false;
    }
	return true;
}

//Altri OPERATORI--------------------------

//STAMPA LA DIM DELL'ARRAY E IL NUM DI ELEM
template<class T>
void List_vector<T>::get() {
    cout<<"\n\n Dim Arrey-->"<<array_dimension;
    cout<<"\n Dim Num elem-->"<< length;
}


#endif