#ifndef BINALBERO_H
#define BINALBERO_H

#include "Cella.h"
#include "Exception.h"

template <class T>
class BinAlbero {
public:
    typedef Cella<T>* Nodo;

    BinAlbero();                //COSTRUTTORE
    BinAlbero(BinAlbero<T> &);  //COSTRUTTORE DI COPIA          [UTILIZZA "getSottoAlbero()"]
    ~BinAlbero();               //DISTRUTTORE
    
    //OPERATORI------------------------------------------------------------------------------------------
    bool alberovuoto()const;     //VERO SE NON CI SONO NODI NELL'ALBERO
    Nodo radice()const;          //RIFERIMENTO ALLA RADICE
    Nodo padre(Nodo)const;       //RESTITUISCE RIFERIMENTO AL PADRE

    bool Sxvuoto(Nodo)const;      //VERO SE IL FIGLIO Sx E VUOTO
    bool Dxvuoto(Nodo)const;      //VERO SE IL FIGLIO Dx E VUOTO
    Nodo figlioSx(Nodo)const;     //RESTITUISCE RIFERIMENTO AL FIGLIO Sx DEL NODO INDICATO
    Nodo figlioDx(Nodo)const;     //RESTITUISCE RIFERIMENTO AL FIGLIO Dx DEL NODO INDICATO

    void costralbero(BinAlbero<T>&,BinAlbero<T>&);      //COSTRUISCE UN ALBERO UNENDO I DUE ALBERI (elimina l'etichetta della radice)
    void cancsottoalbero(Nodo);                         //CANCELLA IL SOTTOALBERO CHE PARTE DAL NODO INDICATO
    Nodo getSottoAlbero(Nodo);                          //RESTITUISCE LA RADICE DELlA COPIA DEL SOTTOALBERO A PARTIRE DAL NODO INDICATO
    
    T legginodo(Nodo)const;         //RESTITUISCE IL VALORE DEL NODO INDICATO
    void scrivinodo(Nodo, T);       //MODIFICA IL VALORE DEL NODO INDICATO
    void insradice();               //INSERISCO LA RADICE
    void insfiglioSx(Nodo);         //INSERISCO UN FIGLIO Sx AL NODO INDICATO
    void insfiglioDx(Nodo);         //INSERISCO UN FIGLIO Dx AL NODO INDICATO

    //OPERATORI Stampa--------------------------------------------------------------------------------------
    void stampa() const;                        //STAMPA ALBERO
    void stampaSimmetrica(const Nodo) const;    //USATA DA stampa() Visita Simmetrica
    void stampaPostOrdine(const Nodo) const;    //USATA DA stampa() Visita PostOrdine
    void stampaPreOrdine(const Nodo) const;     //USATA DA stampa() Visita PreOrdine

    //Altri OPERATORI---------------------------------------------------------------------------------------
    //VERO SE IL NODO INDICATO NON HA FIGLI
	bool foglia(Nodo) const;            
    int profonditaN(Nodo n);    
    //RESTITUISCE LA PROFONDITA' DELL'ALBERO (O SOTTOALBERO radicato in 'n')
	int profondita(Nodo) const;                      
	int profondita() const;  
    //NEL NODO INDICATO INNESTA UN SOTTOALBERO NEL FIGLIO Sx/Dx  -> [ELIMINA L'ALBERO DA INNESTARE]
	void insSub_sx(Nodo, BinAlbero<T> &);   
	void insSub_dx(Nodo, BinAlbero<T> &);
    //ALBERI <int>, CANCELLA LE FOGLIE DI VALORE PARI
	void cancFoglie_pari();                    
	void cancFoglie_pari(Nodo);

    /*_______________________________________________________________________
 	* Dati due alberi binari A e B, e due nodi u e v, con u appartenente ad A
 	* e v appartenente a B, implementare la funzione mutation che scambia i
 	* sottoalberi con radice u e v (u e v non devono essere le radici).
 	*/
	void mutation(Nodo, Nodo, BinAlbero<T> &);

    //SOVRACCARICO OPERATORE ASSEGNAMENTO '='       [UTILIZZA "getSottoAlbero()"]
	BinAlbero<T> &operator=(const BinAlbero<T> &);
    
    private:
        Nodo root;
};
//____________________________________________________________________________________________________________

//COSTRUTTORE
template <class T>
BinAlbero<T>::BinAlbero() {
    root=nullptr;
}

//COSTRUTTORE DI COPIA
template <class T>
BinAlbero<T>::BinAlbero(BinAlbero<T> &A) {
    root = nullptr;
	root = getSottoAlbero(A.root);
}

//DISTRUTTORE
template <class T>
BinAlbero<T>::~BinAlbero() {
    if(!alberovuoto())
        cancsottoalbero(root);
    delete root;
}

//OPERATORI---------------------------------------------------------------------------------------------------------------------
//VERO SE NON CI SONO NODI NELL'ALBERO
template <class T>
bool BinAlbero<T>::alberovuoto() const {
    if(root==nullptr)
        return true;
    else
        return false;
}

//RIFERIMENTO ALLA RADICE
template <class T>
typename BinAlbero<T>::Nodo BinAlbero<T>::radice()const{
    return root;
}

//RESTITUISCE RIFERIMENTO AL PADRE
template <class T>
typename BinAlbero<T>::Nodo BinAlbero<T>::padre(Nodo padre)const{
    return padre->getPadre();
}

//VERO SE IL FIGLIO Sx E VUOTO
template <class T>
bool BinAlbero<T>::Sxvuoto(Nodo sx)const{
    if(sx->getFiglioSx()==nullptr)
        return true;
    else
        return false;
}

//VERO SE IL FIGLIO Dx E VUOTO
template <class T>
bool BinAlbero<T>::Dxvuoto(Nodo dx)const{
    if(dx->getFiglioDx()==nullptr)
        return true;
    else
        return false;
}

//RESTITUISCE RIFERIMENTO AL FIGLIO Sx DEL NODO INDICATO
template <class T>
typename BinAlbero<T>::Nodo BinAlbero<T>::figlioSx(Nodo sx)const{
    return sx->getFiglioSx();
}

//RESTITUISCE RIFERIMENTO AL FIGLIO Dx DEL NODO INDICATO
template <class T>
typename BinAlbero<T>::Nodo BinAlbero<T>::figlioDx(Nodo dx)const{
    return dx->getFiglioDx();
}

//COSTRUISCE UN ALBERO UNENDO I DUE ALBERI  (elimina l'etichetta della radice)
template <class T>
void BinAlbero<T>::costralbero(BinAlbero<T> &A, BinAlbero<T> &B){
    BinAlbero<T> a(A), b(B);    //Copia alberi

    root=new Cella<T>;
    root->setPadre(nullptr);

    if(!A.alberovuoto()){
        root->setFiglioSx(a.radice());
        root->getFiglioSx()->setPadre(root);
        a.root=nullptr;
    }
    else
        root->setFiglioSx(nullptr);

    if(!b.alberovuoto()){
        root->setFiglioDx(b.radice());
        root->getFiglioDx()->setPadre(root);
    }
    else
        root->setFiglioDx(nullptr);
}

//CANCELLA IL SOTTOALBERO CHE PARTE DAL NODO INDICATO
template <class T>
void BinAlbero<T>::cancsottoalbero(Nodo r){
if(r != nullptr) {
    //Cancella il figlio sinistro
    if(!Sxvuoto(r))
        cancsottoalbero(r->getFiglioSx());
    //Cancella il figlio destro
    if(!Dxvuoto(r))
        cancsottoalbero(r->getFiglioDx());

    if(root!=r) {
        if( r->getPadre()->getFiglioSx() == r)
            r->getPadre()->setFiglioSx(nullptr);
        else
            r->getPadre()->setFiglioDx(nullptr);
    }
    else {
        root=nullptr;
    }
}
else 
    delete r;
}

//RESTITUISCE LA RADICE DEL SOTTOALBERO A PARTIRE DAL NODO INDICATO
template <class T>
typename BinAlbero<T>::Nodo BinAlbero<T>::getSottoAlbero(Nodo i) {
if(i != nullptr) {

    Nodo r = new Cella<T>;
    Nodo sx = new Cella<T>;
    Nodo dx = new Cella<T>;

    r->setEtichetta(i->getEtichetta());
    r->setPadre(i->getPadre());

    sx = getSottoAlbero( i->getFiglioSx() );
    dx = getSottoAlbero( i->getFiglioDx() );
    r->setFiglioSx(sx);
    r->setFiglioDx(dx);

    return (r);
}
else 
    return (nullptr);
}

//RESTITUISCE IL VALORE DEL NODO INDICATO
template <class T>
T BinAlbero<T>::legginodo(Nodo n)const{
    return n->getEtichetta();
}

//MODIFICA IL VALORE DEL NODO INDICATO
template <class T>
void BinAlbero<T>::scrivinodo(Nodo n, T e){
    n->setEtichetta(e);
}

//INSERISCO LA RADICE
template <class T>
void BinAlbero<T>::insradice(){
    if(root == nullptr) {
        root = new Cella<T>;
        root->setFiglioDx(nullptr);
        root->setFiglioSx(nullptr);
        root->setPadre(nullptr);
    }
    else 
        throw RootExists();
}

//INSERISCO UN FIGLIO Sx AL NODO INDICATO
template <class T>
void BinAlbero<T>::insfiglioSx(Nodo n){
    if(alberovuoto())
        throw EmptyTree();
    if(n->getFiglioSx() == nullptr) {
        Nodo temp = new Cella<T>;
        n->setFiglioSx(temp);
        temp->setPadre(n);
        temp->setFiglioDx(nullptr);
        temp->setFiglioSx(nullptr);
    }
    else 
        throw NodeExists();
}

//INSERISCO UN FIGLIO Dx AL NODO INDICATO
template <class T>
void BinAlbero<T>::insfiglioDx(Nodo n){
    if(alberovuoto())
        throw EmptyTree();
    if(n->getFiglioSx() == nullptr) {
        Nodo temp = new Cella<T>;
        n->setFiglioDx(temp);
        temp->setPadre(n);
        temp->setFiglioDx(nullptr);
        temp->setFiglioSx(nullptr);
    }
    else 
        throw NodeExists();
}

//OPERATORI Stampa--------------------------------------------------------------------------------------
//STAMPA ALBERO
template <class T>
void BinAlbero<T>::stampa() const {
    if (!alberovuoto()) {
		stampaSimmetrica(radice());
	}
	else {
		cout << "[]" << endl;
	}
	cout << endl;
}    

//USATA DA stampa() PreOrdine
template <class T>
void BinAlbero<T>::stampaPreOrdine(const Nodo n) const {
    //STAMPA PADRE
    cout << " [" << legginodo(n) << ",";      
    //STAMPA FIGLIO DI SINISTRA
	if (!Sxvuoto(n)) {
		stampaPreOrdine(figlioSx(n));    
	}
	else {
		cout << "NIL";
	}
	cout << ",";
    //STAMPA FIGLIO DI DESTRA
	if (!Dxvuoto(n)) {
		stampaPreOrdine(figlioDx(n));    
	}
	else {
		cout << "NIL";
	}
	cout << "] ";
}

//USATA DA stampa() PostOrdine
template <class T>
void BinAlbero<T>::stampaPostOrdine(const Nodo n) const {
    cout << " ["; 
    //STAMPA FIGLIO DI SINISTRA
	if (!Sxvuoto(n)) {
		stampaPostOrdine(figlioSx(n));    
	}
	else { cout << "NIL"; }
	cout << ",";
    //STAMPA FIGLIO DI DESTRA
	if (!Dxvuoto(n)) {
		stampaPostOrdine(figlioDx(n));    
	}
	else { cout << "NIL"; }
    //STAMPA PADRE
    cout << ","<< legginodo(n) ;      
	
	cout << "] ";
}

//USATA DA stampa() Simmetrica
template <class T>
void BinAlbero<T>::stampaSimmetrica(const Nodo n) const {
    cout << " ["; 
    //STAMPA FIGLIO DI SINISTRA
	if (!Sxvuoto(n)) {
		stampaSimmetrica(figlioSx(n));    
	}
	else { cout << "NIL";}
    //STAMPA PADRE
    cout << "," << legginodo(n) << ",";      
    //STAMPA FIGLIO DI DESTRA
	if (!Dxvuoto(n)) {
		stampaSimmetrica(figlioDx(n));    
	}
	else { cout << "NIL"; }
	cout << "] ";
}

//Altri OPERATORI---------------------------------------------------------------------------------------
//VERO SE IL NODO INDICATO NON HA FIGLI
template <class T>
bool BinAlbero<T>::foglia(Nodo n) const {
    if(n != nullptr) 
        return ((n->getFiglioSx() == nullptr) && (n->getFiglioDx() == nullptr));
    else
        throw NullNode();

}  

//PROFONDITA' NODO INDICATO
template <class T>
int BinAlbero<T>::profonditaN(Nodo n) {
	if(n == radice())
        return 0;
    else {
        cout<<"Nodo prof->"<<legginodo(n)<<endl;
        return (profonditaN(padre(n))+1);
    }
        
}

//RESTITUISCE LA PROFONDITA' DELL'ALBERO (O SOTTOALBERO radicato in 'n')
template <class T>
int BinAlbero<T>::profondita(Nodo sub_root) const{
	if (sub_root == nullptr) {
		return (-1);
	}

	int left_profondita = profondita(sub_root->getFiglioSx());
	int right_profondita = profondita(sub_root->getFiglioDx());
	if (left_profondita > right_profondita) {
		return (left_profondita + 1);
	}
	else {
		return (right_profondita + 1);
	}
}

//RESTITUISCE LA PROFONDITA' DELL'ALBERO (O SOTTOALBERO radicato in 'n')
template <class T>
int BinAlbero<T>::profondita() const {
	return profondita(radice());
}

//DEL NODO INDICATO INNESTA UN SOTTOALBERO NEL FIGLIO Sx     [ELIMINA L'ALBERO DA INNESTARE]
template <class T>
void BinAlbero<T>::insSub_sx(Nodo n, BinAlbero<T> &tree) {
    if (!alberovuoto() && (n != nullptr))  {
		if (Sxvuoto(n)) {
        n->setFiglioSx(tree.radice());        //IMPOSTO IL FIGLIO SINISTRO (del nodo dove collegare) CON LA ROOT DELL'ALBERO DA COLLEGARE
			tree.root->setPadre(n);           //IMPOSTO IL PADRE DELLA ROOT DELL'ALBERO DA COLLEGARE
			tree.root = nullptr;
		}
        else cout<<"\nFiglio sinistro NON vuoto !!!\n";
	}   
    else cout<<"\nAlbero o nodo vuoto !!!\n";
}    

//INNESTA UN SOTTOALBERO NEL FIGLIO Dx DEL NODO INDICATO    [ELIMINA L'ALBERO DA INNESTARE]
template <class T>
void BinAlbero<T>::insSub_dx(Nodo n, BinAlbero<T> & tree) {
    if (!alberovuoto() && (n != nullptr))  {
		if (Dxvuoto(n)) {
        n->setFiglioDx(tree.radice());      //IMPOSTO IL FIGLIO DESTRO (del nodo dove collegare) CON LA ROOT DELL'ALBERO DA COLLEGARE
			tree.root->setPadre(n);         //IMPOSTO IL PADRE DELLA ROOT DELL'ALBERO DA COLLEGARE
			tree.root = nullptr;
		}
        else cout<<"\nFiglio sinistro NON vuoto !!!\n";
	}
    else cout<<"\nAlbero o nodo vuoto !!!\n";
}      

//ALBERI <int>, CANCELLA LE FOGLIE DI VALORE PARI
template <class T>
void BinAlbero<T>::cancFoglie_pari() {
    this->cancFoglie_pari(this->radice());
} 

//ALBERI <int>, CANCELLA LE FOGLIE DI VALORE PARI
template <>
void BinAlbero<int>::cancFoglie_pari(Nodo n) {
    if (n == nullptr) {
		return;
	}
	if (!foglia(n)) {
		cancFoglie_pari(n->getFiglioSx());
		cancFoglie_pari(n->getFiglioDx());
	}
	if (foglia(n) && (n->getEtichetta() % 2 == 0)) {
		cancsottoalbero(n);
	}
}

/*_______________________________________________________________________
* Dati due alberi binari A e B, e due nodi u e v, con u appartenente ad A
* e v appartenente a B, implementare la funzione mutation che scambia i
* sottoalberi con radice u e v (u e v non devono essere le radici).
*/
template <class T>
void BinAlbero<T>::mutation(Nodo u, Nodo v, BinAlbero<T> & B) {
    if ((u != radice()) && (v != B.radice())) {

		if (u == u->getPadre()->getFiglioSx() )
			u->getPadre()->setFiglioSx(v);
		else
			u->getPadre()->setFiglioDx(v);

		if (v == v->getPadre()->getFiglioSx())
			v->getPadre()->setFiglioSx(u);
		else 
			v->getPadre()->setFiglioDx(u);

		Nodo parent = u->getPadre();
		u->setPadre(v->getPadre());
		v->setPadre(u->getPadre());
	} else
        cout<<"I Nodi sono la radice";
}

//--------------------------------------------------------------------------------------------------------------------------
//SOVRACCARICO OPERATORE ASSEGNAMENTO '='       [UTILIZZA "getSottoAlbero()"]
template <class T>
BinAlbero<T>& BinAlbero<T>::operator=(const BinAlbero<T> & A) {
    //cancello il vecchio stato
	if (!alberovuoto()) {
		cancsottoalbero(root);
	}
    delete root;
	root = getSottoAlbero(A.root);    //copio il nuovo stato
	return *(this);
}

//SOVRACCARICO OPERATORE (ostream)
template <class T>
std::ostream &operator<<(std::ostream &os, const BinAlbero<T> &t)
{
	t.stampa();
	return (os);
}

#endif