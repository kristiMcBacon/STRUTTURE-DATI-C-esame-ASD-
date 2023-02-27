#ifndef ALBERO_H
#define ALBERO_H

#include "Cella.h"
#include "Coda_Lista\Coda.h"   //per bfs
#include "Exception.h"
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Albero {
public:
    typedef T tipoelem;
    typedef Cella<T>* nodo;

    static constexpr Cella<T>* nil=nullptr;

    Albero();       //COSTRUTTORE
    ~Albero();      //DISTRUTTORE

    //OPERATORI------------------------------------------------------------------------------------------
    bool alberoVuoto() const;       //VERO SE NON CI SONO NODI NELL'ALBERO
    void insRadice(nodo);           //INSERISCO LA RADICE
    nodo radice() const;            //RIFERIMENTO ALLA RADICE
    nodo padre(nodo);               //RESTITUISCE RIFERIMENTO AL PADRE

    bool foglia(nodo);              //VERO SE IL NODO INDICATO NON HA FIGLI
    nodo primoFiglio(nodo);         //RESTITUISCE IL PRIMO FIGLIO DEL NODO INDICATO
    bool ultimoFratello(nodo);      //VERO SE IL NODO NON HA PIù FRATELLI
    nodo succFratello(nodo);        //RESTITUISCE IL FRATELLO SUCCESSIOVO DEL NODO INDICATO

    void insPrimoSottoAlbero(nodo, Albero<T> &);    //INSERISCE UN ALBERO COME PRIMO FIGLIO DEL NODO
    void insSottoAlbero(nodo, Albero<T> &);         //INSERISCE UN ALBERO COME FRATELLO SUCCESSIVO DEL NODO
    void cancSottoAlbero(nodo);                     //CANCELLA IL SOTTOALBERO CHE PARTE DAL NODO INDICATO (anche il NODO)

    void scriviNodo(nodo, tipoelem);    //SCRIVE L'ETICHETTA DEL NODO
    tipoelem leggiNodo(nodo);           //RITORNA ETICHETTA NODO

    void insPrimoFiglio(nodo, tipoelem);   //INSERISCE UN NODO COME PRIMO FIGLIO DI n
    void insFratello(nodo, tipoelem);      //INSERISCE UN NODO COME FRATELLO DI n

    //OPERATORI Stampa--------------------------------------------------------------------------------------
    void stampa();        //STAMPA
    void stampa(nodo);    

    //STAMPA DI TIPO PREORDER (stampa in profoniìdita del nodo padre, poi tutti i nodi partendo da sinstra) DEL SOTTOALBERO CON RADICE 'n'
	void preorder(nodo);
    //STAMPA DI TIPO POSTORDER (stampa in profoniìdita tutti i nodi partendo da sinstra, e da sotto e poi il padre) DEL SOTTOALBERO CON RADICE 'n'
	void postorder(nodo);
    //INSERISCE I NODI IN UNA CODA E LI STAMPA  (metodo che esegue una visita in ampiezza)
	void bfs(nodo);


    //Altri OPERATORI--------------------------------------------------------------------------------------- 
    //PROFONDITA' ALBERO       (O livello = lunghezza del cammino che collega il nodo alla radice)
    int profondita();
	void profondita(nodo, int, int &) ;     //USATA DA profondita()
    //PROFONDITA' NODO INDICATO
    int profondita(nodo curr);

    //ALTEZZA ALBERO  (l'altezza è la profondità massima)
	int altezza() ;
	void altezza(nodo, int, int &) ;
	
private:
    nodo root;
};
//____________________________________________________________________________________________________________

//COSTRUTTORE
template <class T> 
Albero<T>::Albero() {
    root=nullptr;
}

//DISTRUTTORE
template <class T> 
Albero<T>::~Albero() {
    if(!alberoVuoto())
        cancSottoAlbero(root);
    else
        delete root;
}

//OPERATORI------------------------------------------------------------------------------------------
//VERO SE NON CI SONO NODI NELL'ALBERO
template <class T> 
bool Albero<T>::alberoVuoto() const {
    return(this->root==nullptr);
}

//INSERISCO LA RADICE
template <class T> 
void Albero<T>::insRadice(nodo n) {
    if(alberoVuoto()) {
        root= new Cella<T>;
        root->setPadre(nullptr);
        root->setPrimoFiglio(nullptr);
        root->setFratelloSucc(nullptr);
    }
    else 
        throw RootExists();
}

//RIFERIMENTO ALLA RADICE
template <class T>
Cella<T>* Albero<T>::radice() const {
    return (root);
}

//RESTITUISCE RIFERIMENTO AL PADRE
template <class T>
Cella<T>* Albero<T>::padre(nodo n) {
    if(n!=radice()) {
        return (n->getPadre());
    }
    else
        throw NullNode();
}

//VERO SE IL NODO INDICATO NON HA FIGLI
template <class T>
bool Albero<T>::foglia(nodo n){
    return (n->getPrimoFiglio()==nullptr);
}

//RESTITUISCE IL PRIMO FIGLIO DEL NODO INDICATO
template <class T>
Cella<T>* Albero<T>::primoFiglio(nodo n){
        return (n->getPrimoFiglio());

}

//VERO SE IL NODO NON HA PIù FRATELLI
template <class T>
bool Albero<T>::ultimoFratello(nodo n){
        return (n->getFratelloSucc()==nullptr);
}

//RESTITUISCE IL FRATELLO SUCCESSIOVO DEL NODO INDICATO
template <class T>
typename Albero<T>::nodo Albero<T>::succFratello(nodo n){
    if(!(ultimoFratello(n))){
        return (n->getFratelloSucc());
    }
    else 
        return(nullptr);
}

//INSERISCE UN ALBERO COME PRIMO FIGLIO DEL NODO
template <class T>
void Albero<T>::insPrimoSottoAlbero(nodo n, Albero<T> &albero){
    if (!(albero.alberoVuoto())) {
        albero.radice()->setFratelloSucc(n->getPrimoFiglio());
        albero.radice()->setPadre(n);
        n->setPrimoFiglio(albero.radice());
    }
    else 
        throw EmptyTree();
}

//INSERISCE UN ALBERO COME FRATELLO SUCCESSIVO DEL NODO
template <class T>
void Albero<T>::insSottoAlbero(nodo n, Albero<T> &albero) {
    if((!(albero.alberoVuoto())) && (radice()!=n)) {
        albero.radice()->setFratelloSucc(n->getFratelloSucc());
        albero.radice()->setPadre(n->getPadre());
        n->setFratelloSucc(albero.radice());
    }
    else 
        throw EmptyTree();
}

//CANCELLA IL SOTTOALBERO CHE PARTE DAL NODO INDICATO
template <class T>
void Albero<T>::cancSottoAlbero(nodo n) {
    if (n==radice()) {
        root = nullptr;
        delete root;
    }
    else {
        if(n==primoFiglio(padre(n))) {
            padre(n)->setPrimoFiglio(succFratello(n));
        }
        else {
            nodo indice=primoFiglio(padre(n));
            while(succFratello(indice)!=n) {
                indice=succFratello(indice);
            }
            indice->setFratelloSucc(succFratello(n));
        }
        
    }
delete n;   
}

//SCRIVE L'ETICHETTA DEL NODO
template <class T>
void Albero<T>::scriviNodo(nodo n, tipoelem a){
        n->setEtichetta(a);
}

//RITORNA ETICHETTA NODO
template <class T>
T Albero<T>::leggiNodo(nodo n){
        return n->getEtichetta();
}

//INSERISCE UN NODO COME PRIMO FIGLIO DI n
template <class T>
void Albero<T>::insPrimoFiglio(nodo n, tipoelem el) {
    nodo q = new Cella<T>;
    q->setFratelloSucc(n->getPrimoFiglio());
    n->setPrimoFiglio(q);
    q->setPrimoFiglio(nullptr); 
    q->setPadre(n);
    q->setEtichetta(el);
}

//INSERISCE UN NODO COME FRATELLO DI n
template <class T>
void Albero<T>::insFratello(nodo n, tipoelem el) {
    nodo q = new Cella<T>;
    q->setFratelloSucc(n->getFratelloSucc());
    n->setFratelloSucc(q);
    q->setPrimoFiglio(nullptr); 
    q->setPadre(n->getPadre());
    q->setEtichetta(el);
}

//OPERATORI Stampa--------------------------------------------------------------------------------------

//STAMPA
template <class T>
void Albero<T>::stampa() {
    if (!alberoVuoto()) {
		preorder(radice());
	}
	else {
		cout << "[]" << endl;
	}
	cout << endl;
}

//STAMPA DAL NODO n
template <class T>
void Albero<T>::stampa(nodo n) {
    nodo p;
	cout << leggiNodo(n) << ":";
	if(!foglia(n)) {
		p = primoFiglio(n);
		
    //stampa tutti i figli di 'n'
    while (!ultimoFratello(p))  {
			cout << " " << leggiNodo(p) << ","; 
			p = succFratello(p);
		}
		cout << " " << leggiNodo(p) << "\n";

    //STAMPA TUTTI I FIGLI DEI FIGLI DI 'n'
		p = primoFiglio(n);
		while (!ultimoFratello(p))  {
			bfs(p);
			p = succFratello(p);
		}
		stampa(p);
	}
	else
		cout << "\n";
}

//STAMPA DI TIPO PREORDER (stampa in profoniìdita del nodo padre, poi tutti i nodi partendo da sinstra) DEL SOTTOALBERO CON RADICE 'n'
template <class T>
void Albero<T>::preorder(nodo n) {
    if (n != nullptr) {
		nodo child;
		cout << "\nnodo: " << leggiNodo(n) << " livello: " << profondita(n); //(1) preorder
		if (!foglia(n)) {
			child = primoFiglio(n);  //INSERISCE IL PRIMO FIGLIO DEL NODO INDICATO
			
            //STAMPA RICORSIVAMENTE UTILIZZANDO preorder TUTTI I FIGLI DI 'n'
            while (!ultimoFratello(child)) {
				preorder(child);
				child = succFratello(child);
			}
			preorder(child);
		}
	}
    else 
        throw NullNode();
}

//STAMPA DI TIPO POSTORDER (stampa in profoniìdita tutti i nodi partendo da sinstra, e da sotto e poi il padre) DEL SOTTOALBERO CON RADICE 'n'
template <class T>
void Albero<T>::postorder(nodo n) {
    if (n != nullptr) {
		nodo child;
		if (!foglia(n)) {
			child = primoFiglio(n);  //INSERISCE IL PRIMO FIGLIO DEL NODO INDICATO
			
            //STAMPA RICORSIVAMENTE UTILIZZANDO preorder TUTTI I FIGLI DI 'n'
            while (!ultimoFratello(child)) {
				preorder(child);
				child = succFratello(child);
			}
			preorder(child);
		cout << "\nnodo: " << leggiNodo(n) << " livello: " << profondita(n); //(2) postorder
		}
	}
    else 
        throw NullNode();
}

//INSERISCE I NODI IN UNA CODA E LI STAMPA  (metodo che esegue una visita in ampiezza)
template <class T>
void Albero<T>::bfs(nodo n) {
    if (n != nullptr) {
		Coda<nodo> coda;
		coda.incoda(n);

		while (!coda.codavuota()) {
            cout<<"\n";
			nodo i = coda.leggicoda();
			coda.fuoricoda();
			//esame per livelli del nodo i
			cout << " (" << leggiNodo(i) << ") ";

            if(!foglia(i)) {
                i = primoFiglio(i);
                while (!ultimoFratello(i)) {
				    coda.incoda(i);
				    i = succFratello(i);
			    }
                coda.incoda(i);
            }
		}
	}
    else 
        throw NullNode();
}

//Altri OPERATORI---------------------------------------------------------------------------------------
    
//PROFONDITA' ALBERO
template <class T>
int Albero<T>::profondita() {
	int maxdepth;

	if (!alberoVuoto()) {
		maxdepth = 0;
		profondita(radice(), 0, maxdepth);
	}
	else {
		maxdepth = -1;
	}
	return maxdepth;
}

//USATA DA profondita()
template <class T>
void Albero<T>::profondita(nodo curr, int currdepth, int &maxdepth) {
	if(!foglia(curr)) {
		profondita(primoFiglio(curr), currdepth + 1, maxdepth);
	}
	else {
		if (maxdepth < currdepth) {
			maxdepth = currdepth;
		}
	}
	if (!ultimoFratello(curr)) {
		profondita(succFratello(curr), currdepth, maxdepth);
	}
}

//PROFONDITA' NODO INDICATO
template <class T>
int Albero<T>::profondita(nodo n) {
	if(n != radice())
        return (profondita(padre(n))+1);
	else
        return 0;
}

//ALTEZZA ALBERO  (l'altezza è la profondità massima)
template <class T>
int Albero<T>::altezza() {
	int maxwidth;
	if (!alberoVuoto())
	{
		maxwidth = 1;
		altezza(radice(), 0, maxwidth);
	}
	else
	{
		maxwidth = 0;
	}
	return maxwidth;
}

//usata da -> ALTEZZA ALBERO  (l'altezza è la profondità massima)
template <class T>
void Albero<T>::altezza(nodo n, int currwidth, int &maxwidth) {
	if (foglia(n))
	{
		return;
	}
	nodo child = primoFiglio(n);
	currwidth = 1;
	while (!ultimoFratello(child))
	{
		currwidth = currwidth + 1;
		child = succFratello(child);
	}
	if (maxwidth < currwidth)
	{
		maxwidth = currwidth;
	}
	altezza(primoFiglio(n), currwidth, maxwidth);
}

#endif