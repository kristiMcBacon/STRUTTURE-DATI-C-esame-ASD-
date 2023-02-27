#ifndef ALBERO_H
#define ALBERO_H

#include "Lista\List_vector.h"
#include "Exception.h"

using namespace std;

#define MAXnodi 100

template<class I>
class Albero{
public:
	typedef I item;
	typedef int nodo;

    Albero();       //COSTRUTTORE
    //~Albero();      //DISTRUTTORE

    //OPERATORI------------------------------------------------------------------------------------------
	bool alberoVuoto() const;       //VERO SE NON CI SONO NODI NELL'ALBERO
    void insRadice(nodo);           //INSERISCO LA RADICE
    nodo radice() const;            //RIFERIMENTO ALLA RADICE
    nodo padre(nodo) const;         //RESTITUISCE RIFERIMENTO AL PADRE

    bool foglia(nodo) const;              //VERO SE IL NODO INDICATO NON HA FIGLI
    nodo primoFiglio(nodo) const;         //RESTITUISCE IL PRIMO FIGLIO DEL NODO INDICATO
    bool ultimoFratello(nodo) const;      //VERO SE IL NODO NON HA PIù FRATELLI
    nodo succFratello(nodo) const;        //RESTITUISCE IL FRATELLO SUCCESSIOVO DEL NODO INDICATO

    //void insPrimoSottoAlbero(nodo, Albero<I> &);    //INSERISCE UN ALBERO COME PRIMO FIGLIO DEL NODO
    //void insSottoAlbero(nodo, Albero<I> &);         //INSERISCE UN ALBERO COME FRATELLO SUCCESSIVO DEL NODO
    void cancSottoAlbero(nodo);                     //CANCELLA IL SOTTOALBERO CHE PARTE DAL NODO INDICATO (anche il NODO)

    void scriviNodo(nodo, item);    //SCRIVE L'ETICHETTA DEL NODO
    item leggiNodo(nodo) const;           //RITORNA ETICHETTA NODO

    void insPrimoFiglio(nodo, item);   //INSERISCE UN NODO COME PRIMO FIGLIO DI n
    void insFratello(nodo, item);      //INSERISCE UN NODO COME FRATELLO DI n

    //OPERATORI Stampa--------------------------------------------------------------------------------------
    void stampa() const;        //STAMPA

	void copia(nodo n, nodo n2, Albero<I> &albero);

 private:
    typedef List_vector<int>::position position_list;
    //Struttura
	struct Record {
		item e;
		bool used;
		List_vector<int> figli;		
	};
	
	Record nodi[MAXnodi];   //Nodi
	nodo _radice;           //
	int numNodi;            //

};
//____________________________________________________________________________________________________________

//COSTRUTTORE
template <class I>
Albero<I>::Albero() {
	numNodi = 0;
	for (int i=0; i< MAXnodi;i++){
		nodi[i].used = false;
		//nodi[i].figli;
	}
};

//DISTRUTTORE

//OPERATORI------------------------------------------------------------------------------------------
//VERO SE NON CI SONO NODI NELL'ALBERO
template <class I>
bool Albero<I>::alberoVuoto() const{
	return(numNodi == 0);
}

//INSERISCO LA RADICE
template <class I>
void Albero<I>::insRadice (nodo n){
	if (alberoVuoto()){
		_radice = 0;
		nodi[0].used = true;
		numNodi++;
	}
}

//RIFERIMENTO ALLA RADICE
template <class I>
typename Albero<I>::nodo Albero<I>::radice() const{
	return _radice;
}

//RESTITUISCE RIFERIMENTO AL PADRE
template <class I>
typename Albero<I>::nodo Albero<I>::padre (nodo n) const{
	position_list child;		
	int p;

	for (int i=0; i < MAXnodi; i++) {
		if (!nodi[i].figli.empty()) {
			child = nodi[i].figli.begin();
			bool found = false;

			while (!nodi[i].figli.end(child) && !found) {
				if (nodi[i].figli.read(child) == n) {
					found = true;
					p = i;
				}
				child = nodi[i].figli.next(child);
			}
			if (found)
				return(i);
		}
	}
    return (n);     //Restituisce il nodo se non è stato trovato il padre
}

//VERO SE IL NODO INDICATO NON HA FIGLI
template <class I>
bool Albero<I>::foglia(nodo n) const{
	return(nodi[n].figli.empty());
}

//RESTITUISCE IL PRIMO FIGLIO DEL NODO INDICATO
template <class I>
typename Albero<I>::nodo Albero<I>::primoFiglio (nodo n) const{
	if (!foglia(n)){
		return(nodi[n].figli.read(nodi[n].figli.begin()));
	}
    else 
        throw NullNode();
}

//VERO SE IL NODO NON HA PIù FRATELLI
template <class I>
bool Albero<I>::ultimoFratello (nodo n) const {
	position_list c;
	nodo p = padre(n);
	c = nodi[p].figli.begin();
	while (!nodi[p].figli.end(c))
		c = nodi[p].figli.next(c);

	return (n == nodi[p].figli.read(c));
}

//RESTITUISCE IL FRATELLO SUCCESSIOVO DEL NODO INDICATO
template <class I>
typename Albero<I>::nodo Albero<I>::succFratello (nodo n) const{
	if (!ultimoFratello(n)){
		position_list c;
		nodo p = padre(n);
		c = nodi[p].figli.begin();

		while (!nodi[p].figli.end(c)) {
			if (nodi[p].figli.read(c) == n)
				return (nodi[p].figli.read(nodi[p].figli.next(c)));
			c = nodi[p].figli.next(c);
		}
	}
    else
        throw NullNode();
}


//CANCELLA IL SOTTOALBERO CHE PARTE DAL NODO INDICATO (anche il NODO)
template <class I>
void Albero<I>::cancSottoAlbero (nodo n){
	position_list c;
	if (!foglia(n)) {
		while (!nodi[n].figli.empty())
			cancSottoAlbero(nodi[n].figli.read(nodi[n].figli.begin()));
	}

    if(n != _radice) {
        nodo p = padre(n);
	    c = nodi[p].figli.begin();	
	    while(nodi[p].figli.read(c) != n)
		    c = nodi[p].figli.next(c);

	    nodi[p].figli.erase(c);
    }
    nodi[n].used = false;
    numNodi--;
}

//SCRIVE L'ETICHETTA DEL NODO
template <class I>
void Albero<I>::scriviNodo (nodo n, item el){
	nodi[n].e = el;
}

//RITORNA ETICHETTA NODO
template <class I>
typename Albero<I>::item Albero<I>::leggiNodo (nodo n) const{
	return(nodi[n].e);
}

//INSERISCE UN ALBERO COME PRIMO FIGLIO DEL NODO
template <class I>
void Albero<I>::insPrimoFiglio(nodo n, item el){
	// cerca una posizione libera
	int k;
	for (k=0; k < MAXnodi && nodi[k].used == true; k++);
	if (k<MAXnodi){
		nodi[k].used = true;
		nodi[k].e = el;
		nodi[n].figli.insert(k, nodi[n].figli.begin());
	}
}

//INSERISCE UN NODO COME FRATELLO DI n
template <class I>
void Albero<I>::insFratello(nodo n, item el){
	// cerca una posizione libera
	int k;
	for (k=0; k < MAXnodi && nodi[k].used == true; k++);
	if (k<MAXnodi){
		nodi[k].used = true;
		nodi[k].e = el;
		nodo p = padre(n);		
		position_list child = nodi[p].figli.begin();
		bool found = false;
		while (!nodi[p].figli.end(child) && !found){
			if (nodi[p].figli.read(child) == n)
					found = true;
			child = nodi[p].figli.next(child);
		}
		nodi[p].figli.insert(k, child);
	}
}

//STAMPA
template <class I>
void Albero<I>::stampa() const{
	cout << "\n{";
	for (int i=0; i < MAXnodi;i++){
		if (nodi[i].used==true){
			cout << "\n  " << leggiNodo(i) << ":  ";
			if (!foglia(i)){
				position_list child = nodi[i].figli.begin();					
				while (!nodi[i].figli.end(child)){
					cout << leggiNodo(nodi[i].figli.read(child)) << " "; 
					child = nodi[i].figli.next(child);
				}
			}
		}

	}
	cout << "\n}\n";
}

#endif