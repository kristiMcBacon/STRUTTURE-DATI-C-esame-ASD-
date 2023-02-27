#ifndef _GRAFO_H
#define _GRAFO_H

#include <iostream>
#include <cstdlib>
#include "Lista\Linked_list.h"
#include "Arco.h"

//definizione della classe grafo (orientato, etichettato e pesato)
//realizzazione tramite vettore (di lunghezza maxnodi) con liste (monodirezionali dinamiche) di archi (adiacenza)
template<class tipoElem,class tipoPeso> 
class Grafo {
public:
    typedef unsigned int nodo;                  //identificatore del nodo: un intero (indice del vettore)
    typedef Arco<nodo,tipoPeso> arco; //adiacente = (rif.nodo archi | peso arco)

    typedef struct {
        tipoElem etichetta;             //etichetta del nodo
        bool esiste;                    //indica se il nodo fa parte del grafo
        Linked_list<arco> archi;        //lista di adiacenza archi
    } cellaGrafo;

    Grafo();    //costruttore
    ~Grafo();   //distruttore

    unsigned int n_nodi();

    //Altri OPERATORI--------------------------------------------------------------------------------------- 
    void creagrafo();                           //crea il grafo
    bool grafovuoto() const;                    //restituisce true se il grafo è vuoto, false altrimenti
    void insnodo(nodo&);                        //inserisce il nodo che sara identificato dall'indice n
    void insarco(nodo,nodo);                    //inserisce l'arco che esce dal nodo n ed entra in m
    void cancnodo(nodo);                        //elimina il nodo n
    void cancarco(nodo,nodo);                   //elimina l'arco che esce da n ed entra in m
    Linked_list<nodo> adiacenti(nodo) const;    //restituisce la lista di adiacenti di n
    bool esistenodo(nodo) const;                //restituisce true se il nodo appartiene al grafo, false altrimenti
    bool esistearco(nodo,nodo) const;           //restituisce true se il nodo n ha un arco uscente verso m, false altrimenti
    void scrivinodo(tipoElem,nodo);             //scrive l'etichetta del nodo n
    tipoElem legginodo(nodo) const;             //restituisce l'etichetta del nodo n
    void scriviarco(tipoPeso,nodo,nodo);        //scrive il peso dell'arco che va dal nodo n al nodo m
    tipoPeso leggiarco(nodo,nodo);              //restituisce il peso dell'arco che va da n a m

    int numnodi() { return nelementi;}
    //int numarchi() { return maxnodi;}

    //OPERATORI-----------------------------------------------------------------

private:
    cellaGrafo table[1000];     //vettore di Celle
    unsigned int maxnodi;       //dimensione del vettore
    unsigned int nelementi;     //numero nodi nel grafo
    nodo primolibero() const;   //Restituisce la prima posizione libera del vettore
};
//____________________________________________________________________________________________________________

//COSTRUTTORE
template<class tipoElem,class tipoPeso> Grafo<tipoElem,tipoPeso>::Grafo(){
    creagrafo();
}

//DISTRUTTORE
template<class tipoElem,class tipoPeso> Grafo<tipoElem,tipoPeso>::~Grafo() {

}

//crea il grafo
template<class tipoElem,class tipoPeso>
void Grafo<tipoElem,tipoPeso>::creagrafo() {
    maxnodi = 1000;
    nelementi=0; 
    for (int i=0; i<1000; i++) {//inizializzo il vettore mettendo
        table[i].esiste=false;
    }
}

//restituisce true se il grafo è vuoto, false altrimenti
template<class tipoElem,class tipoPeso>
bool Grafo<tipoElem,tipoPeso>::grafovuoto() const {
    return (nelementi==0);
}

//inserisce il nodo che sara identificato dall'indice n
template<class tipoElem,class tipoPeso>
void Grafo<tipoElem,tipoPeso>::insnodo(nodo &n) {   
    if (!esistenodo(n) && nelementi<1000)  {
        n=primolibero();        //la posizione in cui mettere il nodo del vettore sara la prima libera
        table[n].esiste=true;   //setto a true il suo campo esiste
        nelementi++;            //aumento il contatore di nodi del grafo
    }
}

//inserisce l'arco che esce dal nodo n ed entra in m
template<class tipoElem,class tipoPeso>
void Grafo<tipoElem,tipoPeso>::insarco(nodo n,nodo m) {
    if (esistenodo(n) && esistenodo(m) && !esistearco(n,m)) //precondizione nodi appartenenti e arco non esistente
    {
        auto indice=table[n].archi.begin();     //prima pos del vettore di archi
        arco temp;                              //creo l'elemento da inserire
        temp.scrivinodo(m);                     //setto l'adiacente
        table[n].archi.insert(temp,indice);     //inserisco l'arco nel vett di archi
    }
}

//elimina il nodo n
template<class tipoElem,class tipoPeso>
void Grafo<tipoElem,tipoPeso>::cancnodo(nodo n) {
    if (esistenodo(n)) {

            bool libero=true;                           
            int i=0;                                    
            while (i<maxnodi) {             //controllo tutti i nodi

                if (esistenodo(i)) {        //se il nodo esiste controllo se ha archi con il nodo che voglio cancellare
                    if(esistearco(i,n)) {
                        cancarco(i, n);
                    }
                }                                     
                i++;                       
            }   
            //Cancello il nodo
            table[n].esiste=false;      //adesso quel nodo non esiste piu
            //table[n].archi.; //svuoto l'etichetta
            nelementi--;                //e ho un nodo in meno nel grafo
    }
}

//elimina l'arco che esce da n ed entra in m
template<class tipoElem,class tipoPeso>
void Grafo<tipoElem,tipoPeso>::cancarco(nodo n,nodo m)  {
    if (esistenodo(n) && esistenodo(m) && esistearco(n,m)) {
        bool cancellato=false;
        auto indice=table[n].archi.begin();

        while (!table[n].archi.end(indice) && !cancellato) //scandisco la lista finche non cancello l'elemento
        {
            if (table[n].archi.read(indice).legginodo()==m) {
                table[n].archi.erase(indice); 
                cancellato=true;
            }
            else 
                indice=table[n].archi.next(indice);
        }
    }
}

//restituisce la lista di adiacenti di n
template<class tipoElem,class tipoPeso>
Linked_list<typename Grafo<tipoElem,tipoPeso>::nodo> Grafo<tipoElem,tipoPeso>::adiacenti(nodo n) const  {
    Linked_list<nodo> lista; //lista da restituire
    arco temp;
    if (esistenodo(n)) {
        auto indice=table[n].archi.begin();
        auto indice2=lista.begin(); 
        
        while (!table[n].archi.end(indice)) //scansione della prima lista
        {
            temp=table[n].archi.read(indice); //lettura di adiacente
            lista.insert(temp.legginodo(),indice2); //inserisco (in coda) nella lista da restituire solo il riferimento al nodo adiacente (senza il peso dell'arco)
            indice=table[n].archi.next(indice);
            indice2=lista.next(indice2);
        }
    }
    return(lista);
}

//restituisce true se il nodo appartiene al grafo, false altrimenti
template<class tipoElem,class tipoPeso>
bool Grafo<tipoElem,tipoPeso>::esistenodo(nodo n) const {
    if (n<=maxnodi) 
        return (table[n].esiste);
    else 
        return false;
}

//restituisce true se il nodo n ha un arco uscente verso m, false altrimenti
template<class tipoElem,class tipoPeso>
bool Grafo<tipoElem,tipoPeso>::esistearco(nodo n,nodo m) const {
    bool esiste=false;
    if (esistenodo(n) && esistenodo(m)) {
        auto indice=table[n].archi.begin();
        while (!table[n].archi.end(indice) && !esiste) //scandisco la lista finche non trovo l'elemento o e finita
        {
            if (table[n].archi.read(indice).legginodo()==m) 
                esiste=true;
            indice=table[n].archi.next(indice);
        }
    }
    return (esiste);
}

//scrive l'etichetta del nodo n
template<class tipoElem,class tipoPeso>
void Grafo<tipoElem,tipoPeso>::scrivinodo(tipoElem val, nodo n) {
    if (esistenodo(n)) //precondizione nodo appartenente al grafo
        table[n].etichetta=val;
}

//restituisce l'etichetta del nodo n
template<class tipoElem,class tipoPeso>
 tipoElem Grafo<tipoElem,tipoPeso>::legginodo(nodo n) const {
    tipoElem e;
    if (esistenodo(n)) //precondizione nodo appartenente al grafo
        e=table[n].etichetta;
    return (e);
}

//scrive il peso dell'arco che va dal nodo n al nodo m
template<class tipoElem,class tipoPeso>
void Grafo<tipoElem,tipoPeso>::scriviarco(tipoPeso val,nodo n,nodo m) {
    if (esistenodo(n) && esistenodo(m)) {
        //se esiste e poi si farebbe la seconda scansione per aggiornare
        bool aggiornato=false;//quindi si fa un'unica scansione in cui si ricerca e si aggiorna)
        arco temp(m,val);
        auto indice=table[n].archi.begin();
        while (!table[n].archi.end(indice) && !aggiornato) //scandisco la lista finch� non trovo l'elemento o � finita
        {
            if (table[n].archi.read(indice).legginodo()==m) {
                table[n].archi.write(temp,indice);
                aggiornato=true;
            }
            indice=table[n].archi.next(indice);
        }
        
        if(!aggiornato)
            cout<<"\nL'arco che si vuole scrivere non esiste ->"<<n<<", "<<m<<", "<<val;
    }
}

//restituisce il peso dell'arco che va da n a m
template<class tipoElem,class tipoPeso>
tipoPeso Grafo<tipoElem,tipoPeso>::leggiarco(nodo n,nodo m) {
    tipoPeso a;
    if (esistenodo(n) && esistenodo(m)) {                                                            //quindi si fa un'unica scansione in cui si ricerca e si legge)
        bool letto=false;
        auto indice=table[n].archi.begin();
        while (!table[n].archi.end(indice) && !letto) //scandisco la lista finche non trovo l'elemento o e finita
        {
            if (table[n].archi.read(indice).legginodo()==m) {
                a=table[n].archi.read(indice).leggipeso();
                letto=true;
            }
            indice=table[n].archi.next(indice);
        }
        if(!letto)
            cout<<"\nL'arco che si vuole leggere non esiste -> ("<<n<<", "<<m<<")";
    }
    return(a);
}

//restituisce la prima posizione del vettore libera
template<class tipoElem,class tipoPeso>
unsigned int Grafo<tipoElem,tipoPeso>::primolibero() const {
    nodo i=-1;
    bool libero=false;
    while (!libero) //scorre il vettore finche non trova una posizione libera
    {   
        //Non controllo anche il superamento della dim del vettore perche viene chiamata solo se i<maxnodi
        i++;
        libero=!table[i].esiste;
    }
    return (i);
}

//OPERATORI-----------------------------------------------------------------


#endif
