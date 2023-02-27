#ifndef _NODE_H
#define _NODE_H

//CLASSE Nodo della lista-------------------------------------------------------------------------
template< class T >
class Node {
public:
    typedef T value_type;

    Node();     //COSTRUTTORE
    ~Node();    //DISTRUTTORE

	//OPERATORI--------------------------------
    value_type getValue() const;            //RESTITUISCE IL VALORE DEL NODO
    Node<value_type>* getpPrev() const;     //RESTITUISCE NODO PRECENDENTE
    Node<value_type>* getpNext() const;     //RESTITUISCE NODO SUCCESSIVO
    void setValue(value_type);              //IMPOSTA IL VALORE DEL NODO
    void setpPrev(Node<value_type>*);       //IMPOSTA NODO PRECENDENTE
    void setpNext(Node<value_type>*);       //IMPOSTA NODO SUCCESSIVO

private:
	T value;            //Valore contenuto nel nodo
	Node<T> * pPrev;    //Puntatore al nodo precedente
	Node<T> * pNext;    //Puntatore al nodo successivo
};

//COSTRUTTORE
template<class T>
Node<T>::Node() {
    pPrev=nullptr;
    pNext=nullptr;
}

//DISTRUTTORE
template<class T>
Node<T>::~Node() {}

//OPERATORI--------------------------------
//RESTITUISCE IL VALORE DEL NODO
template<class T>
T Node<T>::getValue() const{
    return(value);
}

//RESTITUISCE NODO PRECENDENTE
template<class T>
Node<T>* Node<T>::getpPrev() const{
    return(pPrev);
}

//RESTITUISCE NODO SUCCESSIVO
template<class T>
Node<T>* Node<T>::getpNext() const{
    return(pNext);
}

//IMPOSTA IL VALORE DEL NODO
template<class T>
void Node<T>::setValue(T val) {
    value=val;
}

//IMPOSTA NODO PRECENDENTE
template<class T>
void Node<T>::setpPrev(Node<T>* prev) {
    pPrev=prev;
}

//IMPOSTA NODO SUCCESSIVO
template<class T>
void Node<T>::setpNext(Node<T>* next) {
    pNext=next;
}

#endif