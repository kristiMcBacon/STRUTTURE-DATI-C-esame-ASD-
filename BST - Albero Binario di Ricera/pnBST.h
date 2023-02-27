#ifndef pnBST_H
#define pnBST_H

#include <iostream>
#include <string>
using namespace std;

//dichiarazione della classe pnBST
template <class K, class E>
class pnBST;

//CREO LA CLASSE NODO DELL'ALBERO BST
template <class K, class E>
class binstreenode  {
    friend class pnBST<K, E>;

public:
    binstreenode()
    {
        parent = nullptr;
        sx = nullptr;
        dx = nullptr;
    }
    binstreenode(K k, E l)
    {
        parent = nullptr;
        sx = nullptr;
        dx = nullptr;
        key = k;
        label = l;
    }

private:
    binstreenode<K, E> *parent; //PADRE
    binstreenode<K, E> *sx; //FIGLIO SINISTRO
    binstreenode<K, E> *dx; //FIGLIO DESTRO
    K key;  
    E label;  //VALORE NODO
};

//CREAZIONE CLASSE ALBERO BST
template <class K, class E>
class pnBST {
public:
    //DEFINISCO I TIPI
    typedef K key;                      //tipo chiave
    typedef E label;                    //tipo elemento
    typedef binstreenode<K, E>* node;   //tipo nodo

    pnBST();        //COSTRUTTORE
    ~pnBST();       //DISTRUTTORE

    //OPERATORI------------------------------------------------------------------------------------------
    void create();              //INIZIALIZZA LA RADICE DEL BST
    bool empty() const;         //VERO SE IL BST E' VUOTO 
    void insert(key, label);    //INSERISCE UN NODO CON L'ETICHETTA, IN BASE ALLA CHIAVE INDICATA
    void erase(key);            //ELIMINA IL NODO INDICATO
    node search(key) const;     //RESTITUISCE IL RIFERIMENTO DEL NODO CON CHIAVE 'k'
    node minimum(node) const;   //RESTITUISCE IL NODO CON CHIAVE MINIMA PARTEMDO DAL NODO 'n' (ovvero il nodo piu in basso a sinistra)
    node minimum() const;       //RESTITUISCE IL NODO CON CHIAVE MINIMA PARTEMDO DALLA RADICE (ovvero il nodo piu in basso a sinistra)
    node maximum(node) const;   //RESTITUISCE IL NODO CON CHIAVE MAGGIORE PARTEMDO DAL NODO 'n' (ovvero il nodo piu in basso a destra)
    node maximum() const;       //RESTITUISCE IL NODO CON CHIAVE MAGGIORE PARTENDO DALLA RADICE (ovvero il nodo piu in basso a destra)
    node predecessor(node) const;//RESTITUISCE IL NODO PRECENDENTE A QUELLO INDICATO (ovvero un nodo con una chiave minore e più vicino possibile di quella del nodo indicato)
    node successor(node) const; //RESTITUISCE IL NODO SUCCESSIVO A QUELLO INDICATO (ovvero un nodo con una chiave maggiore e più vicino possibile di quella del nodo indicato)

    //Altri OPERATORI--------------------------------------------------------------------------------------
    //MODIFICA L'ETICHETTA DI UN NODO IN BASE ALLA CHIAVE
    void modify(key, label);
    //COLLEGA UN NODO PADRE CON UN NODO FIGLIO (destro o sinisto, in base alla chiave)
    void link(node, node, key);
    //ELIMINA IL SOTTOALBERO CHE PARTE DAL NODO 'n'
    void erase_sub_tree(node);
    //ALLOCA UN NODO NELLA RADICE (chiave, etichetta)
    void ins_root(key, label);
    //ALLOCA UN NODO NELLA RADICE (vuoto)
    void ins_root();
    //VERO SE IL NODO SINISTRO DI 'n' E' VUOTO
    bool sx_empty(node) const;
    //VERO SE IL NODO DESTRO DI 'n' E' VUOTO
    bool dx_empty(node) const;
    //RESTITUISCE RIFERIMENTO ALLA RADICE
    node get_root() const;
    //VERO SE IL NODO 'n' E' UNA FOGLIA
    bool leaf(node) const;
    //RESTITUISCE L'ETICHETTA DEL NODO 'n'
    label read_label(node) const;
    //MODIFICA L'ETICHETTA DEL NODO INDICATO
    void write_label(node, label);
    //RESTITUISCE LA CHIAVE DEL NODO 'n'
    key read_key(node) const;
    //RESTITUISCE UN RIFERIMENTO AL FIGLIO SINISTRO DEL NODO INDICATO
    node get_sx(node) const;
    //RESTITUISCE UN RIFERIMENTO AL FIGLIO DESTRO DEL NODO INDICATO
    node get_dx(node) const;
    
    //ALGORITMO DI VISITA----------------------------------------------------------
    //metodo che permette di leggere le chiavi di un BST in ordine crescente
    void inorder(node) const;

private:
    binstreenode<K, E> *root;
};
//____________________________________________________________________________________________________________

//COSTRUTTORE
template <class K, class E>
pnBST<K, E>::pnBST()  {
    this->create();
}

//DISTRUTTORE
template <class K, class E>
pnBST<K, E>::~pnBST() {
    if (!this->empty()) {
        //elimino il sotto albero radicato nella radice
        this->erase_sub_tree(root);
    }
    //elimino il nodo radice
    delete root;
    root = nullptr;
}

//OPERATORI------------------------------------------------------------------------------------------
//INIZIALIZZA LA RADICE DEL BST
template <class K, class E>
void pnBST<K, E>::create()  {
    root = nullptr;
}

//VERO SE IL BST E' VUOTO 
template <class K, class E>
bool pnBST<K, E>::empty() const {
    return (root == nullptr);
}

//INSERISCE UN NODO CON L'ETICHETTA, IN BASE ALLA CHIAVE INDICATA
template <class K, class E>
void pnBST<K, E>::insert(key k, label l)  {
    if(empty()) {
        root = new binstreenode<K, E>(k, l);
    }
    else {
    node parent = nullptr; //puntatore al genitore
    node n = root;         //puntatore alla radice
    
    //FA VIAGGIARE IL NODO DA INSERIRE SUL FIGLIO DESTRO O SINISTRO IN BASE AL VALORE DELLA CHIAVE (minore a sinistra, maggiore a destra), finchè non  si arriva su un nodo vuoto o non si trova un nodo con la stessa chiave
    while ((n != nullptr) && (n->key != k)) {
        parent = n;   //puntatore alla radice
        if (n != nullptr) {
            if (k < n->key) { //se la chiave è minore della chiave della radice va a sinistra
                n = n->sx;
            }
        }
        if (n != nullptr) {
            if (k > n->key) { //se la chiave è maggiore della chiave della radice va a destra
                n = n->dx;
            }
        }
    }
    //se la chiave e' uguale, modifico solo il dato  del nodo
    if ((n != nullptr) && (n->key == k))  {
        n->label = l;
    }
    else  {
        n = new binstreenode<K, E>(k, l); //crea nuovo nodo
        link(parent, n, k);     //lo collega al padre
        //if (parent == nullptr)  {   //se non ha un padre allora è la root
        //    root = n;
        //}
    }
    }
}

//ELIMINA IL NODO INDICATO
template <class K, class E>
void pnBST<K, E>::erase(key k)  {
    //cerco il nodo da eliminare
    node n = search(k); //riferimento nodo con chiave k
    if (n == nullptr) {
        return;     //il nodo da eliminare non esiste
    }

    //CASO 1 : il nodo da eliminare e' una foglia++++++++++++++++++++++++++++++++
    if (leaf(n))  {
        if (n != root)  {   
            if (n->parent->sx == n) {   //SE 'n' è il figlio sinistro
                n->parent->sx = nullptr;
            }
            else  {                     //SE 'n' è il figlio destro
                n->parent->dx = nullptr;
            }
        }
        else  {
            //il nodo da eliminare e' radice
            root = nullptr;
        }
        delete n;
        n = nullptr;
    } 
    //CASO 2: il nodo da eliminare ha due figli+++++++++++++++++++++++++++++++++++
    else if (!sx_empty(n) && !dx_empty(n))  {
        node s = minimum(n->dx);    //del figlio di destra (di n) trova il minimo (il nodo più a sinistra) 
        key tempkey = s->key;         //memorizzo la chiave del nodo 's'
        label templabel = s->label;   //memorizzo il valore del nodo 's'

        erase(s->key);  //APPLICA RICORSIVAMENTE QUESTA FUNZIONE

        //assegno al nodo da eliminare i valori (chiave, etichetta) del nodo 's'  
        n->key = tempkey; 
        n->label = templabel;
    }
    //CASO 3: il nodo da eliminare ha un solo figlio+++++++++++++++++++++++++++++
    else  { 
        //SALVA IL NODO FIGLIO IN 'child'
        node child = nullptr;
        if (!sx_empty(n) && dx_empty(n))  {  //SE 'n' ha solo un figlio sinistro
            child = n->sx;    //salva il figlio sinistro di 'n'
        }
        else  {                              //SE 'n' ha solo un figlio destro
            child = n->dx;    //salva il figlio destro di 'n'
        }

        //SOSTITUISCE IL NODO DA ELIMINARE (n), CON 'child'
        if (n != root)  {
            if (n == n->parent->sx) {        //SE 'n' è il figlio sinistro
                n->parent->sx = child;   //il nodo 'child' diventa il nuvo figlio sinistro del padre di 'n'
            }
            else  {                          //SE 'n' è il figlio destro
                n->parent->dx = child;   //il nodo 'child' diventa il nuvo figlio destro del padre di 'n'
            }
        }
        else  {                              //SE 'n' è la radice
            root = child;
        }
        delete n;
        n = nullptr;
    }
}

//RESTITUISCE IL RIFERIMENTO DEL NODO CON CHIAVE 'k'
template <class K, class E>
typename pnBST<K, E>::node pnBST<K, E>::search(key k) const {
    node n = root;
    while ((n != nullptr) && (n->key != k)) { //CONTINUA FINCHE LA CHIAVE E DIVERSA DA QUELLA DA TROVARE
        if (n != nullptr) {
            if (k < n->key) { //se la chiave da trovare è minore della chiave di 'n' si sposta a sinistra
                n = n->sx;
            }
        }
        if (n != nullptr) {
            if (k > n->key) { //se la chiave da trovare è maggiore della chiave di 'n' si sposta a destra
                n = n->dx;
            }
        }
    }
    return (n); //restituisce un nodo contenente la chiave oppure un nodo nullo
}

//RESTITUISCE IL NODO CON CHIAVE MINIMA (ovvero il nodo piu in basso a sinistra) PARTEMDO DALLA RADICE
template <class K, class E>
typename pnBST<K, E>::node pnBST<K, E>::minimum() const  {
    if (!this->empty()) {
        return (minimum(root));
    }
    else  {
        return (root);
    }
}

//RESTITUISCE IL NODO CON CHIAVE MINIMA (ovvero il nodo piu in basso a sinistra) PARTEMDO DAL NODO 'n'
template <class K, class E>
typename pnBST<K, E>::node pnBST<K, E>::minimum(node n) const {
    if (n->sx == nullptr) {
        return (n);
    }
    return (minimum(n->sx));    //richiama ricorsivamnete la funzione
}

//RESTITUISCE IL NODO CON CHIAVE MASSIMA (ovvero il nodo piu in basso a Destra) PARTENDO DALLA RADICE
template <class K, class E>
typename pnBST<K, E>::node pnBST<K, E>::maximum() const {
    if (!this->empty()) {
        return (maximum(root));
    }
    else  {
        return (root);
    }
}

//RESTITUISCE IL NODO CON CHIAVE MASSIMA (ovvero il nodo piu in basso a DESTRA) PARTENDO DAL NODO 'n'
template <class K, class E>
typename pnBST<K, E>::node pnBST<K, E>::maximum(node n) const {
    if (n->dx == nullptr) {
        return (n);
    }
    return (maximum(n->dx));
}

//RESTITUISCE IL NODO SUCCESSIVO A QUELLO INDICATO (ovvero un nodo con una chiave maggiore di quella del nodo indicato, e con un valore più vicino possibile)
template <class K, class E>
typename pnBST<K, E>::node pnBST<K, E>::successor(node n) const {
    if (n == nullptr) {
        return (n);               //SE il nodo è vuoto
    }

    /*SI CERCA NEL SOTTOALBERO DEL FIGLIO DESTRO PERCHE IL VALORE DELLA CHIAVE DEVE ESSERE MAGGIORE 
      DI QUELLO DEL NODO INDICATO, E DI QUESTI SI PRENDE QUELLO CON IL VALORE MINIMO*/
    if (n->dx != nullptr) {
        return (minimum(n->dx));  //SE ha un figlio destro restituisce il minimo del sottoalbero del figlio destro
    }

    /*SE NON HA UN FIGLIO DESTRO SI CERCA TRA I NODI SUPERIORI (i padri) QUELLO CHE E' UN FIGLIO DESTRO*/
    node parent = n->parent;
    while ((parent != nullptr)&&(n == parent->dx))  {//finche non si trova un padre che è un figlio destro
        n = parent;   //padre di 'n'
        parent = parent->parent;  //padre del padre
    }
    return (parent);
}

//RESTITUISCE IL NODO PRECENDENTE A QUELLO INDICATO (ovvero un nodo con una chiave minore di quella del nodo indicato, e con un valore più vicino possibile)
template <class K, class E>
typename pnBST<K, E>::node pnBST<K, E>::predecessor(node n) const {
    if (n == nullptr) {
        return (n);
    }
    /*SI CERCA NEL SOTTOALBERO DEL FIGLIO SINISTRO PERCHE IL VALORE DELLA CHIAVE DEVE ESSERE MINORE 
      DI QUELLO DEL NODO INDICATO, E DI QUESTI SI PRENDE QUELLO CON IL VALORE MAGGIORE*/
    if (n->sx != nullptr) {
        return (maximum(n->sx));  //SE ha un figlio sinistro restituisce il massimo del sottoalbero del figlio sinistro
    }

    /*SE NON HA UN FIGLIO SINISTRO SI CERCA TRA I NODI SUPERIORI (i padri) QUELLO CHE E' UN FIGLIO SINISTRO*/
    node parent = n->parent;
    while ((parent != nullptr) && (n == parent->sx))  {
        n = parent;
        parent = parent->parent;
    }
    return (parent);
}


//Altri OPERATORI--------------------------------------------------------------------------------------

//MODIFICA L'ETICHETTA DI UN NODO IN BASE ALLA CHIAVE
template <class K, class E>
void pnBST<K, E>::modify(key k, label l)  {
    if (!this->empty()) {
        node n = search(k); //CERCA RIFERIMENTO ALLA NODO CON CHIAVE 'k'
        if (n != nullptr) {
            n->label = l;   //modifica l'etichetta
        }
    }
}

//ALLOCA UN NODO NELLA RADICE (chiave, etichetta)
template <class K, class E>
void pnBST<K, E>::ins_root(key k, label l)  {
    if (this->empty())  {
        root = new binstreenode<K, E>(k, l);
    }
}

//ALLOCA UN NODO NELLA RADICE (vuoto)
template <class K, class E>
void pnBST<K, E>::ins_root()  {
    if (this->empty())  {
        root = new binstreenode<K, E>;
    }
}

//VERO SE IL NODO SINISTRO DI 'n' E' VUOTO
template <class K, class E>
bool pnBST<K, E>::sx_empty(node n) const  {
    return (n->sx == nullptr);
}

//VERO SE IL NODO DESTRO DI 'n' E' VUOTO
template <class K, class E>
bool pnBST<K, E>::dx_empty(node n) const  {
    return (n->dx == nullptr);
}

//RESTITUISCE RIFERIMENTO ALLA RADICE
template <class K, class E>
typename pnBST<K, E>::node pnBST<K, E>::get_root() const  {
    return (root);
}

//ELIMINA IL SOTTOALBERO CHE PARTE DAL NODO 'n'
template <class K, class E>
void pnBST<K, E>::erase_sub_tree(node n)  {
    if (n == nullptr) {
        return;
    }
    erase_sub_tree(n->sx);  //RICHIAMA RICORSIVAMENTE LA FUNZIONE SUL FIGLIO DI SINISTRA
    erase_sub_tree(n->dx);  //RICHIAMA RICORSIVAMENTE LA FUNZIONE SUL FIGLIO DI DESTRA


    //ELIMINA IL RIFERIMENTO DI 'n' DAL PADRE
    if (n != root)  { //SE 'n' E' DIVERSA DALLA RADICE
        node p = n->parent; //inserisce il padre di 'n'
        if (n == p->sx) {   //SE 'n' E IL FIGLIO SINISTRO
            p->sx = nullptr;
        }
        else if (n == p->dx)  { //SE 'n' E IL FIGLIO DESTRO
            p->dx = nullptr;
        }
    }
    else  {
        root = nullptr;
    }
    delete n;
    n = nullptr;
}

//VERO SE IL NODO 'n' E' UNA FOGLIA
template <class K, class E>
bool pnBST<K, E>::leaf(node n) const  {
    return ((n->sx == nullptr) && (n->dx == nullptr));
}

//RESTITUISCE L'ETICHETTA DEL NODO 'n'
template <class K, class E>
typename pnBST<K, E>::label pnBST<K, E>::read_label(node n) const {
    label label;  //DICHIARAZIONE ETICHETTA (tipo label)
    if (n != nullptr) {
        return (n->label);
    }
    return (label);
}

//RESTITUISCE LA CHIAVE DEL NODO 'n'
template <class K, class E>
typename pnBST<K, E>::key pnBST<K, E>::read_key(node n) const {
    key key;
    if (n != nullptr) {
        return (n->key);
    }
    return (key);
}

//MODIFICA L'ETICHETTA DEL NODO INDICATO
template <class K, class E>
void pnBST<K, E>::write_label(node n, label l)  {
    if (n != nullptr) {
        n->label = l;
    }
}

//RESTITUISCE UN RIFERIMENTO AL FIGLIO SINISTRO DEL NODO INDICATO
template <class K, class E>
typename pnBST<K, E>::node pnBST<K, E>::get_sx(node n) const  {
    if (n != nullptr) {
        return (n->sx);
    }
    else  {
        return (n);
    }
}

//RESTITUISCE UN RIFERIMENTO AL FIGLIO DESTRO DEL NODO INDICATO
template <class K, class E>
typename pnBST<K, E>::node pnBST<K, E>::get_dx(node n) const  {
    if (n != nullptr) {
        return (n->dx);
    }
    else  {
        return (n);
    }
}

//COLLEGA UN NODO PADRE CON UN NODO FIGLIO (destro o sinisto, in base alla chiave)
template <class K, class E>
void pnBST<K, E>::link(node parent, node child, key key)  {
    if (child != nullptr) {
        child->parent = parent;   //associa al nodo figlio l'indirizzo del padre
    }
    //in base alla chiave collega il nodo come figlio sinisto o desto al padre
    if (parent != nullptr)  {
        if (key < parent->key)  {
            parent->sx = child;
        }
        if (key > parent->key)  {
            parent->dx = child;
        }
    }
}

//ALGORITMO DI VISITA--------------------------------------------------------------------------
//metodo che permette di leggere le chiavi di un BST in ordine crescente
template <class K, class E>
void pnBST<K, E>::inorder(node n) const {
    if (n == nullptr) {
        return;
    }
    if(!sx_empty(n)) {
        inorder(n->sx); //CHIAMATA RICORSIVA SUL FIGLIO SINISTRO
    }
    
    cout << " " << read_key(n) << " ";      //esamino il nodo

    if(!sx_empty(n)) {
    inorder(n->dx);
    }
}

#endif