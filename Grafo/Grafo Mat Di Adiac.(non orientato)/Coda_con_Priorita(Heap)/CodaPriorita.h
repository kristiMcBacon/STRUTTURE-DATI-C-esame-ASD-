#ifndef CODAPRIORITA_H
#define CODAPRIORITA_H

#include <assert.h>

#include <string>
#include <iostream>
using namespace std;

template<class T> class CodaP {
public:
  typedef T tipoelem;

  CodaP ();     //COSTRUTTORE
  CodaP (int);  //COSTRUTTORE DI COPIA
  ~CodaP ();    //DISTRUTTORE

  //OPERATORI--------------------------------
  void creaPrioriCoda ();         //CREA PRIORI CODA
  void inserisci (tipoelem);      //INSERISCI UN ELEMENTO
  tipoelem min () ;                //STAMPA L'ELEMENTO MINIMO
  void cancellaMin ();            //CANCELLA L'ELEMENTO MINIMO

  //Altri OPERATORI--------------------------------------------------------------------------------------- 
  void stampaPrioriCoda();      //STAMPA
  bool insiemeVuoto() ;         //VERO SE VUOTO
  bool appartiene(tipoelem);    //VERO SE L'ELEMENTO APPARTIENE

private:
  int MAXLUNG;
  tipoelem *heap;
  int ultimo;

  void fixUp ();            //
  void fixDown (int, int);  //
};
//____________________________________________________________________________________________________________

//COSTRUTTORE
template < class T > 
CodaP<T>::CodaP ():MAXLUNG (100) {
  heap = new tipoelem[MAXLUNG];
  creaPrioriCoda ();
};

//COSTRUTTORE DI COPIA
template < class T > 
CodaP<T>::CodaP (int maxN): MAXLUNG (maxN) {
  heap = new tipoelem[MAXLUNG];
  creaPrioriCoda ();
};

//DISTRUTTORE
template <class T> 
CodaP<T>::~CodaP () {
  ultimo = 0;
  heap= nullptr;
  delete[]heap;
};

//OPERATORI--------------------------------
//CREA PRIORI CODA
template < class T > 
void CodaP<T>::creaPrioriCoda () {
  ultimo = 0;
};

//INSERISCI UN ELEMENTO
template < class T > 
void CodaP<T>::inserisci (tipoelem e) {
  assert (ultimo < MAXLUNG);
  heap[++ultimo - 1] = e;
  fixUp ();
};

//STAMPA L'ELEMENTO MINIMO
template < class T > 
typename CodaP<T>::tipoelem CodaP < T >::min (){
  assert (ultimo != 0);
  return (heap[0]);
};

//CANCELLA L'ELEMENTO MINIMO
template < class T > 
void CodaP<T>::cancellaMin () {
  assert (ultimo != 0);

  heap[0] = heap[ultimo - 1];
  ultimo--;
  fixDown (1,ultimo);
};


/* Per ripristinare i vincoli dello heap quando la priorità di un nodo è      *
 * cresciuta, ci spostiamo nello heap verso l'alto, scambiando, se necessario,*
 * il nodo in posizione k con il suo nodo padre (in posizione k/2),           *
 * continuando fintanto che heap[k]<heap[k/2] oppure fino a quando            *
 * raggiungiamo la cima dello heap.                                           */
template < class T > 
void CodaP<T>::fixUp () {
  int k = ultimo;

  while (k > 1 && heap[k - 1] < heap[k / 2 - 1]) {
      tipoelem tmp;
      tmp = heap[k - 1];
      heap[k - 1] = heap[k / 2 - 1];
      heap[k / 2 - 1] = tmp;
      k = k / 2;
    }
}

/* Per ripristinare i vincoli dello heap quando la priorità di un nodo si è   *
 * ridotta, ci spostiamo nello heap verso il basso, scambiando, se necessario,*
 * il nodo in posizione k con il minore dei suoi nodi figli e arrestandoci    *
 * quando il nodo al posto k non è più grande di almeno uno dei suoi figli    *
 * oppure quando raggiungiamo il fondo dello heap. Si noti che se N è pari e  *
 * k è N/2, allora il nodo in posizione k ha un solo figlio: questo caso      *
 * particolare deve essere trattato in modo appropriato.                      */
template < class T > 
void CodaP<T>::fixDown (int k, int N) {
    short int scambio = 1;

    while (k <= N / 2 && scambio) {
        int j = 2 * k;
        tipoelem tmp;
        if (j < N && heap[j - 1] > heap[j])
	    	j++;
        if (scambio = (heap[j - 1] < heap[k - 1])) {
			tmp = heap[k - 1];
			heap[k - 1] = heap[j - 1];
			heap[j - 1] = tmp;
			k = j;
	    }
    }
};

//Altri OPERATORI--------------------------------------------------------------------------------------- 
//STAMPA
template <class T>
void CodaP<T>::stampaPrioriCoda(){
	if(!insiemeVuoto()) {
		T el = min();
		cout<<"["<< min() <<"], ";
		cancellaMin();
		stampaPrioriCoda();

		inserisci(el);
	}
  else
    cout<<endl;
}

//VERO SE VUOTO
template<class T> 
bool CodaP<T>::insiemeVuoto() {
    return (ultimo==0);
}

//VERO SE L'ELEMENTO APPARTIENE
template<class T> 
bool CodaP<T>::appartiene(tipoelem a) {
    bool trovato=false;
    for(int i = 0; i < ultimo && trovato==false; i++){
        if(heap[i]==a) trovato = true;
    }
    return(trovato);
}

#endif