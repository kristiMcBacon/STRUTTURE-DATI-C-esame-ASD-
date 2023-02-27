#ifndef _DIZIONARIO_H
#define _DIZIONARIO_H

#include "Coppia.h"
#include "Hash.h"
#include "Lista/Linked_list.h"

template <class K, class V>
class Dizionario : private Hash<K>, private Coppia<K, V>{

public:
    typedef K chiave;
    typedef V valore;
    typedef typename Linked_list<Coppia<chiave, valore>>::position posizione; 
    

    Dizionario();               //COSTRUTTORE
    Dizionario(unsigned int);   //COSTRUTTORE con dim
    ~Dizionario();              //DISTRUTTORE

    //OPERATORI--------------------------------
    bool dizionariovuoto ();                //VERO SE IL DIZIONARIO E' VUOTO
    bool appartiene(const chiave&);         //VERO SE LA CHIAVE E' PRESENTE NELLA TABELLA
    void inserisci(Coppia<chiave, valore>&); //INSERISCE UNA COPPIA NEL DIZIONARIO
    void cancella(const chiave&);           //ELIMINA LA COPPIA CON LA CHIAVE INDICATA
    valore recupera(const chiave&);         //RESTITUISCE IL VALORE RELATIVO ALLA CHIAVE INDICATA (se esiste)

    void aggiorna(const chiave&, valore&);  //AGGIORNA IL VALORE COLLEGATO ALLA CHIAVE
    bool contienevalore(const valore&);     //VERO SE IL DIZIONARIO CONTIENE IL VALORE INDICATO
    int numeroCoppie() { return num_elem;};
    

private:
    Linked_list< Coppia<chiave, valore> >* table;   //Tabella Hash con liste di trabocco
    Hash<string> hash;                              //Funzione hash
    int num_elem;                                   //Num coppie nel dizionario
    unsigned int dim;                               //Dimensione tabella (divisore)
};
//____________________________________________________________________________________________________________


//COSTRUTTORE
template<class K, class V>
Dizionario<K,V>::Dizionario() {
    dim = 100;
    num_elem = 0;
    table = new Linked_list< Coppia<K, V> >[dim];
}

//COSTRUTTORE con dim
template<class K, class V>
Dizionario<K,V>::Dizionario(unsigned int dimensione) {
    dim = dimensione;
    num_elem = 0;
    table = new Linked_list< Coppia<K, V> >[dim];
}

//DISTRUTTORE
template<class K, class V>
Dizionario<K,V>::~Dizionario() {
    delete[] table;
}           
//OPERATORI--------------------------------

//VERO SE IL DIZIONARIO E' VUOTO
template<class K, class V>
bool Dizionario<K,V>::dizionariovuoto () {
    return(num_elem==0);
}

//VERO SE LA CHIAVE E' PRESENTE NELLA TABELLA
template<class K, class V>
bool Dizionario<K,V>::appartiene(const chiave& key) {
    bool trovato = false;
    posizione iter; 
    unsigned int pos = hash.H(key, dim); //Funzione hash sullla chiave per trovare la posizione 
    iter = table[pos].begin();  //Home backet della chiave

    while (!table[pos].end(iter) && !trovato) { 
        if (key == table[pos].read(iter).getChiave())   //Se non viene trovato nell'home backet si scorre la lista di trabocco
            trovato = true;
        iter = table[pos].next(iter);
    }
    return trovato;
}

//INSERISCE UNA COPPIA NEL DIZIONARIO
template<class K, class V>
void Dizionario<K,V>::inserisci(Coppia<chiave, valore>& c) {
    unsigned int h= hash.H(c.getChiave(), dim);
    posizione pos = table[h].begin();
    table[h].insert(c, pos);
    num_elem++;
} 

//ELIMINA LA COPPIA CON LA CHIAVE INDICATA
template<class K, class V>
void Dizionario<K,V>::cancella(const chiave& key) {
    posizione iter;
    bool trovato = false;
    unsigned int pos = hash.H(key, dim);
    iter = table[pos].begin();

    while (!table[pos].end(iter) && !trovato) {
        if (key == table[pos].read(iter).getChiave())
            trovato = true;
        else
            iter = table[pos].next(iter);
    }

    if (trovato) {
        table[pos].erase(iter);
        num_elem--;
    }
}

//RESTITUISCE IL VALORE RELATIVO ALLA CHIAVE INDICATA (se esiste)
template<class K, class V>
V Dizionario<K,V>::recupera(const chiave& key) {
    bool trovato = false;
    V elem;
    unsigned int pos = hash.H(key, dim);
    posizione iter = table[pos].begin();

    while (!table[pos].end(iter) && !trovato) {
        if (key == table[pos].read(iter).getChiave()) {
            trovato = true;
            elem = table[pos].read(iter).getValore();
        }
        iter = table[pos].next(iter);
    }
    return elem;
}      

//AGGIORNA IL VALORE COLLEGATO ALLA CHIAVE
template<class K, class V>
void Dizionario<K,V>::aggiorna(const chiave& key, valore& elem) {
    cancella(key);
    Coppia<K, V> c(key, elem);
    inserisci(c);
}

//VERO SE IL DIZIONARIO CONTIENE IL VALORE INDICATO
template<class K, class V>
bool Dizionario<K,V>::contienevalore(const valore& elem) {
    bool trovato= false;
    int pos=0;
    posizione iter;
    
    if (!dizionariovuoto()) {
        //Controllo nella tabella
        while (pos<dim && !trovato) {
            iter = table[pos].begin();
            //Controllo nella lista di trabocco
            while (!table[pos].end(iter) && !trovato) {
                if( elem == table[pos].read(iter).getValore())
                    trovato = true;
                iter = table[pos].next(iter);
            }
        pos++;
        }
    }
    return (trovato);
}

#endif