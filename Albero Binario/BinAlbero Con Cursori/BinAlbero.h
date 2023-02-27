#ifndef BINALBERO_H
#define BINALBERO_H

#include <iostream>
#include <string>

#include "Exception.h"

using namespace std;

template <class T> 
class BinAlbero {
	static const int NIL = -1;

public:
	typedef T tipoelem;
	typedef int Nodo;

    //STRUCT cella
	struct _cella{
		int genitore;
		int sinistro;
		int destro;
		tipoelem valore;
	};
	typedef struct _cella Cella;

	BinAlbero();        //COSTRUTTORE
	BinAlbero(int);     //COSTRUTTORE DI COPIA
	~BinAlbero();       //DISTRUTTORE

	//OPERATORI-------------------------------------
	bool alberoVuoto()const;     //VERO SE NON CI SONO NODI NELL'ALBERO
    Nodo radice()const;          //RIFERIMENTO ALLA RADICE
    Nodo padre(Nodo)const;       //RESTITUISCE RIFERIMENTO AL PADRE

	bool SxVuoto(Nodo)const;      //VERO SE IL FIGLIO Sx E VUOTO
    bool DxVuoto(Nodo)const;      //VERO SE IL FIGLIO Dx E VUOTO
    Nodo figlioSx(Nodo)const;     //RESTITUISCE RIFERIMENTO AL FIGLIO Sx DEL NODO INDICATO
    Nodo figlioDx(Nodo)const;     //RESTITUISCE RIFERIMENTO AL FIGLIO Dx DEL NODO INDICATO

	//NON FATTA void costrAlbero(BinAlbero<T>&, BinAlbero<T>&);     //COSTRUISCE UN ALBERO UNENDO I DUE ALBERI (elimina l'etichetta della radice)
    void cancSottoAlbero(Nodo);                         //CANCELLA IL SOTTOALBERO CHE PARTE DAL NODO INDICATO

	T leggiNodo(Nodo)const;         //RESTITUISCE IL VALORE DEL NODO INDICATO
    void scriviNodo(Nodo, T);       //MODIFICA IL VALORE DEL NODO INDICATO

    void insRadice(Nodo);           //INSERISCO LA RADICE
    void insFiglioSx(Nodo);         //INSERISCO UN FIGLIO Sx AL NODO INDICATO
    void insFiglioDx(Nodo);         //INSERISCO UN FIGLIO Dx AL NODO INDICATO

    //Altri OPERATORI---------------------------------------------------------------------------------------
    void stampa() const;                   //STAMPA
    void stampaSottoAlbero(Nodo n) const;  //STAMPA SOTTOALBERO

private:
	int MAXLUNG;        //Lung max
	Cella *spazio;      //Arrey di Celle
	int nNodi;          //numero nodi
	Nodo inizio;        //Pos inizio albero
	Nodo libera;        //Pos inizio Celle libere
};
//____________________________________________________________________________________________________________

//COSTRUTTORE
template <class T>
BinAlbero<T>::BinAlbero(){
	MAXLUNG = 100;
	spazio = new Cella[MAXLUNG];
	inizio = NIL;
	for (int i = 0; i < MAXLUNG; i++) {
		spazio[i].sinistro = (i+1) % MAXLUNG;
	}
	libera = 0;
	nNodi = 0;
}

//COSTRUTTORE DI COPIA
template <class T>
BinAlbero<T>::BinAlbero(int nNodi): MAXLUNG(nNodi) {
	spazio = new Cella[nNodi];
	inizio = NIL;
	for (int i = 0; i < MAXLUNG; i++) {
		spazio[i].sinistro = (i+1) % MAXLUNG;
	}
	libera = 0;
	nNodi = 0;
}

//DISTRUTTORE
template <class T>
BinAlbero<T>::~BinAlbero() {
    if(!alberoVuoto())
	    cancSottoAlbero(inizio);
	delete[] spazio;
}

//OPERATORI-------------------------------------
//VERO SE NON CI SONO NODI NELL'ALBERO
template <class T>
bool BinAlbero<T>::alberoVuoto() const {
	return(nNodi == 0);
}

//RIFERIMENTO ALLA RADICE
template <class T> 
typename BinAlbero<T>::Nodo BinAlbero<T>::radice() const {
	return(inizio);
}

//RESTITUISCE RIFERIMENTO AL PADRE
template <class T> 
typename BinAlbero<T>::Nodo BinAlbero<T>::padre(Nodo n) const {
	if (n != inizio)
		return (spazio[n].genitore);
	else 
        return(n);
}

//VERO SE IL FIGLIO Sx E VUOTO
template <class T>
bool BinAlbero<T>::SxVuoto(BinAlbero<T>::Nodo n) const {
	return (spazio[n].sinistro == NIL);
}

//VERO SE IL FIGLIO Dx E VUOTO
template <class T>
bool BinAlbero<T>::DxVuoto(BinAlbero<T>::Nodo n) const {
	return (spazio[n].destro == NIL);
}

//RESTITUISCE RIFERIMENTO AL FIGLIO Sx DEL NODO INDICATO
template <class T> 
typename BinAlbero<T>::Nodo BinAlbero<T>::figlioSx(Nodo n) const {
	if (!SxVuoto(n))
		return (spazio[n].sinistro);
	else 
        return(n);
}

//RESTITUISCE RIFERIMENTO AL FIGLIO Dx DEL NODO INDICATO
template <class T> 
typename BinAlbero<T>::Nodo BinAlbero<T>::figlioDx(Nodo n) const {
	if (!DxVuoto(n))
		return (spazio[n].destro);
	else 
        return(n);
}

/*
COSTRUISCE UN ALBERO UNENDO I DUE ALBERI (elimina l'etichetta della radice)
template <class T> 
void BinAlbero<T>::costrAlbero(BinAlbero<T>&, BinAlbero<T>&) {

}   
*/

//CANCELLA IL SOTTOALBERO CHE PARTE DAL NODO INDICATO
template <class T>
void BinAlbero<T>::cancSottoAlbero(Nodo n) {
	if (n != NIL) {
		if (!SxVuoto(n))
			cancSottoAlbero(spazio[n].sinistro);
		if (!DxVuoto(n))
			cancSottoAlbero(spazio[n].destro);
		if (n != inizio) {
			Nodo p = padre(n);
			if (spazio[p].sinistro == n)
				spazio[p].sinistro = NIL; //se il nodo da cancellare è figlio sinistro
			else
				spazio[p].destro = NIL;//se il nodo da cancellare è figlio destro
		}
		else
			inizio = NIL; //se il nodo da cancellare è radice
		nNodi--;
		spazio[n].sinistro = libera;
		libera = n;
	}
}

//RESTITUISCE IL VALORE DEL NODO INDICATO
template <class T>
T BinAlbero<T>::leggiNodo(Nodo n) const {
	if (n != NIL)
		return (spazio[n].valore);
    else
		throw NullNode();
}

//MODIFICA IL VALORE DEL NODO INDICATO
template <class T>
void BinAlbero<T>::scriviNodo(Nodo n, tipoelem a) {
	if (n != NIL)
		spazio[n].valore = a;
    else
		throw NullNode();
}

//INSERISCO LA RADICE
template <class T>
void BinAlbero<T>::insRadice(BinAlbero<T>::Nodo n) {
	if (inizio == NIL) {
		inizio = libera;
		libera = spazio[libera].sinistro;
		spazio[inizio].genitore = NIL;          
		spazio[inizio].sinistro = NIL;
		spazio[inizio].destro = NIL;
		nNodi++;
	}
    else
		throw RootExists();
}

//INSERISCO UN FIGLIO Sx AL NODO INDICATO
template <class T>
void BinAlbero<T>::insFiglioSx(Nodo n) {
    if (inizio == NIL)
		throw EmptyTree();
	if (n == NIL)
		throw NullNode();
	if (spazio[n].sinistro != NIL)
		throw NodeExists();
	if (nNodi >= MAXLUNG)
		throw FullSize();
    else {
      Nodo q = libera;
      libera = spazio[libera].sinistro;
      spazio[n].sinistro = q;
      spazio[q].sinistro = NIL;
      spazio[q].genitore = n;
      spazio[q].destro = NIL;
      nNodi++;
    }
}

//INSERISCO UN FIGLIO Dx AL NODO INDICATO
template <class T>
void BinAlbero<T>::insFiglioDx(Nodo n) {
    if (inizio == NIL)
		throw EmptyTree();
	if (n == NIL)
		throw NullNode();
	if (spazio[n].destro != NIL)
		throw NodeExists();
	if (nNodi >= MAXLUNG)
		throw FullSize();
	else
    {
      Nodo q = libera;
      libera = spazio[libera].sinistro;
      spazio[n].destro = q;
      spazio[q].genitore = n;
      spazio[q].sinistro = NIL;
      spazio[q].destro = NIL;
      nNodi++;
    }
}        

//Altri OPERATORI---------------------------------------------------------------------------------------
//STAMPA
template <class T>
void BinAlbero<T>::stampa() const {
    if (!alberoVuoto())
		stampaSottoAlbero(radice());
	else 
		cout << "[]" << endl;
	cout << endl;
}

//STAMPA SOTTOALBERO
template <class T>
void BinAlbero<T>::stampaSottoAlbero(Nodo n) const {
    cout << "[" << leggiNodo(n) << ", ";
	if (!SxVuoto(n))
		stampaSottoAlbero(figlioSx(n));
	else std::cout << "NIL";
	cout << ", ";
	if (!SxVuoto(n))
		stampaSottoAlbero(figlioDx(n));
	else cout << "NIL";
	cout << " ]";
}

//SOVRACCARICO
template<class T>
std::ostream& operator<<(std::ostream& out, const BinAlbero<T>& t) {
    t.stampa();
    return out;
}

#endif