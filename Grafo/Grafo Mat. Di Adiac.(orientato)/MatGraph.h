#ifndef MATGRAPH_H
#define MATGRAPH_H

#include <iostream>
#include "Lista\List_vector.h"                          //Contiene archi
#include "Coda_con_Priorita(Heap)\CodaPriorita.h"       //Per bfs()
#include "ServizioGraph.h"                              //Classi: arch, archInfo, nodeGraph, nodeInfo.
#include <assert.h>

#define MAXDIMENSION 100
using namespace std;

//Classe matgraph (ORIENTATO) di tipo MATRICE DI ADIACENZA ESTESA con Mtrice NxN (peso e vuoto), Etichetta, Vuoto
template <class E, class P>
class matgraph {
public:
    //Alias per i tipi template
    typedef E label;        //tipovalore o etichetta
    typedef P weight;       //tipo peso
    typedef nodeGraph node; //tipo nodo grafo

    //ridefiisco i tipi della classe astratta
    typedef class arch<weight, node> arch;                //tipo nodoarco
    typedef List_vector<node> listnode;                   //tipo listanodi
    typedef typename listnode::position position_listnode;//tipo posizione listanodi
    typedef List_vector<arch> listarch;                   //tipo listaarchi

    //COSTRUTTORE con paramentro
    matgraph(int);
    //COSTRUTTORE di default
    matgraph();
    //DISTRUTTORE
    ~matgraph();

    //OPERATORI------------------------------------------------------------------------------------
    void create();                      //Inizializza il grafo
    bool empty() const;                 //Vero se il grafo e' vuoto
    void insNode(node &);               //Inserisce un nodo nel grafo
    void insArch(node, node, weight);   //Inserisce un arco avendo in input il nodo uscente e il nodo entrante e il peso
    void eraseNode(node);               //Elimina un nodo dalla matrice di adiacenza  (non ci devono essere nodi entranti o nodi uscenti)
    void eraseArch(node, node);         //Elimina un arco entrante da un nodo della matrice di adiacenza      
    bool isNode(node) const;            //Vero se il nodo passato in input e' un nodo del grafo
    bool isArch(node, node) const;      //Vero se dati due nodi in input essi formano un arco nel grafo
    listnode adjacent(node) const;      //Restituisce una lista dei nodi adiacenti al nodo a cui si applica
    label readLabel(node) const;        //Restituisce l'etichetta di un nodo
    void writeLabel(node, label);       //Scrive e sovrascrive l'etichetta di un nodo con un altra etichetta

    listnode listNode() const;              //Restituisce una lista con tutti i nodi del grafo
    weight readWeight(node, node) const;    //Legge e restituisce il peso di due nodi se questi formano un arco
    void writeWeight(node, node, weight);   //Scrive e sovrascrive il peso di due nodi che formano un arco con un altro peso

    //OPERATORI di Stampa-------------------------------------------------------------------------
    //metodo che stampa i nodi adiacenti al nodo a cui si applica
    void printAdjacent(node) const;
    //stampa tutti i nodi con gli archi associati
    void print() const;
    //stampa tutti i nodi con gli archi associati partendo dal nodo indicato
    void print(node) const;
    //metodo che permette di visualizzare le relazioni tra i nodi e i loro archi nella matrice di adiacenza
    void adjacencyMatrix() const;
    //metodo che stampa un percorso tra due nodi del grafo se tale cammino esiste
    void dfsPath(node, node) const;
    //funzione di supporto che stampa l'intero cammino tra due nodi del grafo avente in input il vettore di marcatura
    void dfsPath(node, node, int *, bool &) const;
    //metodo che verifica l'esistenza tra due nodi del grafo ed in caso positivo stampa tutto il cammino richiamando dfsPath()
    void findPath(node, node) const;
    //funzione di supporto che restituisce vero se esiste un cammino tra due nodi del grafo avente in input il vettore di visite[]
    bool findPath(node, node, int *, bool) const;

    //ALGORITMI DI VISITA---------------------------------------------------------------------------
    void dfs(node) const;           //algoritmo dfs visita in profondita'
    void dfs(node, int *) const;
    void bfs(node) const;           //algoritmo bfs visita in ampiezza

    //Altri OPERATORI-------------------------------------------------------------------------------
    //Restituisce il totale dei nodi presenti nel grafo
    int numNodes() const;
    //Restituisce il totale degli archi presenti nel grafo
    int numArches() const;
    //metodo che restituisce vero se la matrice di adiacenza e' nulla
    bool isEmptyMatrix() const;
    //funzione che restituisce il numero di archi entranti al nodo a cui si applica
    int inDegree(node) const;
    //funzione che restituisce il numero di archi uscenti al nodo a cui si applica
    int outDegree(node) const;
    //metodo che  restituisce la media del numero di archi uscenti per ogni nodo del grafo
    double meanOutDegree() const;

private:
    nodeInfo<E, P> *matrix; //matrice di info nodi
    int dimension;          //dimensione matrice
    int nodes;              //numero nodi presenti
    int arches;             //numero archi presenti
};
//____________________________________________________________________________________________________________

//COSTRUTTORE di default
template <class E, class P>
matgraph<E, P>::matgraph() 
{
    this->create();
    arches = 0;
    dimension = MAXDIMENSION;
    matrix = new nodeInfo<E, P>[dimension];
    for (int i = 0; i < dimension; i++) 
    {
        matrix[i].arches = new archInfo<P>[dimension];
    }
}

//COSTRUTTORE con paramentro
template <class E, class P>
matgraph<E, P>::matgraph(int dim)
{
    this->create();
    arches = 0;
    dimension = dim;
    matrix = new nodeInfo<E, P>[dimension];
    for (int i = 0; i < dimension; i++)
    {
        matrix[i].arches = new archInfo<P>[dimension];
    }
}

//DISTRUTTORE
template <class E, class P>
matgraph<E, P>::~matgraph()
{
    if (!isEmptyMatrix())
    {
        for (int i = 0; i < dimension; i++)
        {
            delete[] matrix[i].arches;
            matrix[i].arches = nullptr;
        }
    }
    delete[] matrix;
    matrix = nullptr;
}

//OPERATORI------------------------------------------------------------------------------------
//Inizializza il grafo
template <class E, class P>
void matgraph<E, P>::create()
{
    nodes = 0;
}

//Vero se il grafo e' vuoto
template <class E, class P>
bool matgraph<E, P>::empty() const
{
    return (nodes == 0);
}

//Inserisce un nodo nel grafo
template <class E, class P>
void matgraph<E, P>::insNode(node &nodegraph)
{
    int n = 0;
    assert(nodes < dimension);
    
    while (!matrix[n].empty)        //scorre fino a trovare una pos vuota
    {
        n++;
    }
    nodes++;
    matrix[n].empty = false;
    nodegraph.setId(n);
}

//Inserisce un arco avendo in input il nodo uscente e il nodo entrante e il peso
template <class E, class P>
void matgraph<E, P>::insArch(node n1, node n2, weight w)
{
    assert(isNode(n1) && isNode(n2));

    matrix[n1.getId()].arches[n2.getId()].weight = w;   
    matrix[n1.getId()].arches[n2.getId()].empty = false;
    arches++;
}

//Elimina un nodo dalla matrice di adiacenza (non ci devono essere nodi entranti o nodi uscenti)
template <class E, class P>
void matgraph<E, P>::eraseNode(node n)
{
    assert(isNode(n));

    bool canc = true;
    int i = 0;

    //Controlla se ci sono archi uscendi
    for (int i = 0; (i < dimension) && (canc); i++) {
        if (!matrix[n.getId()].arches[i].empty) {
            canc = false;
        }
    }
    //Controlla se ci sono archi entranti
    for (int i = 0; (i < dimension) && (canc); i++) {
        if (!matrix[i].empty && !(matrix[i].arches[n.getId()].empty)) {
            canc = false;
        }
    }
    if (canc) {
        delete[] matrix[n.getId()].arches;
        matrix[n.getId()].arches = nullptr;
        matrix[n.getId()].empty = true;
        arches--;
    }
    else    
        cout<<"  ->  Nodo non cancellato, ci sono archi entranti o uscendi !!!  <- "<<endl;
}

//Elimina un arco entrante da un nodo della matrice di adiacenza  
template <class E, class P>
void matgraph<E, P>::eraseArch(node n1, node n2)
{
    if(isArch(n1, n2)) {
        matrix[n1.getId()].arches[n2.getId()].empty = true; //arco vuoto
        matrix[n1.getId()].arches[n2.getId()].weight = 0;   //imposto il peso ad un valore nullo
        arches--;
    }
    else 
        cout<<"  ->  Arco non cancellato, non esiste !!!  <- "<<endl;
}

//Vero se il nodo passato in input e' un nodo del grafo
template <class E, class P>
bool matgraph<E, P>::isNode(node n) const
{
    return (!matrix[n.getId()].empty);
}

//Vero se dati due nodi in input essi formano un arco nel grafo
template <class E, class P>
bool matgraph<E, P>::isArch(node n1, node n2) const
{
    return (!matrix[n1.getId()].arches[n2.getId()].empty);
}

//Restituisce una lista dei nodi adiacenti al nodo a cui si applica
template <class E, class P>
typename matgraph<E, P>::listnode matgraph<E, P>::adjacent(node n) const
{
    assert(isNode(n));
    listnode list;
    for (int j = 0; j < dimension; j++)
    {
        if (!matrix[n.getId()].arches[j].empty)
        {
            node copy(j); //copio il nodo arco
            //inserisco il nodo arco adiacente ad n nella lista
            list.push_back(copy);
        }
    }
    return (list);
}

//Restituisce l'etichetta di un nodo
template <class E, class P>
typename matgraph<E, P>::label matgraph<E, P>::readLabel(node n) const
{
    assert(isNode(n));
    return (matrix[n.getId()].label);
}

//Scrive e sovrascrive l'etichetta di un nodo con un altra etichetta
template <class E, class P>
void matgraph<E, P>::writeLabel(node n, label l)
{
    assert(isNode(n));
    matrix[n.getId()].label = l;
}

//Restituisce una lista con tutti i nodi del grafo
template <class E, class P>
typename matgraph<E, P>::listnode matgraph<E, P>::listNode() const
{
    listnode list;
    for (int i = 0; i < dimension; i++)
    {
        if (!matrix[i].empty)
        {
            node nodecopy(i);
            list.push_back(nodecopy);
        }
    }
    return (list);
}

//Legge e restituisce il peso di due nodi se questi formano un arco
template <class E, class P>
typename matgraph<E, P>::weight matgraph<E, P>::readWeight(node n1, node n2) const
{
    assert(isArch(n1, n2));
    return (matrix[n1.getId()].arches[n2.getId()].weight);
}

//Scrive e sovrascrive il peso di due nodi che formano un arco con un altro peso
template <class E, class P>
void matgraph<E, P>::writeWeight(node n1, node n2, weight w)
{
    assert(isArch(n1, n2));
    matrix[n1.getId()].arches[n2.getId()].weight = w;
}

//OPERATORI di Stampa-------------------------------------------------------------------------
//metodo che stampa i nodi adiacenti al nodo a cui si applica
template <class E, class P>
void matgraph<E, P>::printAdjacent(node n) const
{
    assert(isNode(n));
    cout << "\nNodi Adiacenti: (" << readLabel(n) << "):\n";
    if (!empty())
    {
        listnode l = adjacent(n);   //Inserisce i nodi adiacenti
        position_listnode p = l.begin();
        while (!l.end(p))
        {
            cout << "\t\t    -->(" << readLabel(l.read(p)) << ")\n";
            p = l.next(p);
        }
    }
}

//stampa tutti i nodi con gli archi associati
template <class E, class P>
void matgraph<E, P>::print() const
{
    if (!empty()) {
        for (int i = 0; i < dimension; i++) {
            if (matrix[i].empty == false) {
                node node_n(i);
                cout << "\nnodo: " << readLabel(node_n) << "\n";
                for (int j = 0; j < dimension; j++) {
                    if (matrix[i].arches[j].empty == false) {
                        node node_a(j);
                        cout << "\tarco: " << readLabel(node_a);
                    }
                }
            }
        }
    }
}

//stampa tutti i nodi con gli archi associati
template <class E, class P>
void matgraph<E, P>::print(node u) const
{
    assert(isNode(u));
    if (isNode(u)) {
        for (int i = u.getId(); i < dimension; i++) {
            if (matrix[i].empty == false) {
                node node_n(i);
                cout << "\nnodo: " << readLabel(node_n) << "\n";
                for (int j = 0; j < dimension; j++) {
                    if (matrix[i].arches[j].empty == false) {
                        node node_a(j);
                        cout << "\tarco: " << readLabel(node_a);
                    }
                }
            }
        }
    }
}

//metodo che permette di visualizzare le relazioni tra i nodi e i loro archi nella matrice di adiacenza
template <class E, class P>
void matgraph<E, P>::adjacencyMatrix() const
{
    int adjacency_matrix[dimension][dimension]; //dichiaro la matrice di adiacenza
    //inizializzo la matrice
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            adjacency_matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < dimension; i++)
    {
        for (int j = i; j < dimension; j++)
        {
            if (matrix[i].arches[j].empty == false)
            {
                adjacency_matrix[i][j] = 1;
            }
            if (matrix[j].arches[i].empty == false)
            {
                adjacency_matrix[j][i] = 1;
            }
        }
    }
    cout << "\n:::::::: matrice di adiacenza :::::::: \n";
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            cout << "\t" << adjacency_matrix[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
}

//metodo che stampa un percorso tra due nodi del grafo se tale cammino esiste
template <class E, class P>
void matgraph<E, P>::dfsPath(node s, node d) const
{
    assert(isNode(s) && isNode(d));
    int v[dimension];
    for (int i = 0; i < dimension; i++)
    {
        if (!matrix[i].empty)
        {
            v[i] = 0; //nodo presente
        }
        else
        {
            v[i] = -1; //nodo assente
        }
    }
    if (findPath(s, d, v, false))
    {
        //creo il vettore di marcatura
        bool found = false;
        int visitato[dimension];
        for (int i = 0; i < dimension; i++)
        {
            if (!matrix[i].empty)
            {
                visitato[i] = 0; //nodo presente
            }
            else
            {
                visitato[i] = -1; //nodo assente
            }
        }
        dfsPath(s, d, visitato, found);
    }
}

//funzione di supporto che stampa l'intero cammino tra due nodi del grafo avente in input il vettore di marcatura
template <class E, class P>
void matgraph<E, P>::dfsPath(node s, node d, int *visitato, bool &found) const
{
    //esamino il nodo u
    cout << " (" << readLabel(s) << ") --> ";
    visitato[s.getId()] = 1; //nodo visitato
    listnode l = adjacent(s);
    if (!l.empty())
    {
        position_listnode p = l.begin();
        while (!l.end(p) && !found)
        {
            node n = l.read(p);
            if (n == d)
            {
                cout << "(" << readLabel(n) << ")";
                found = true;
            }
            else if (visitato[n.getId()] == 0)
            {
                dfsPath(n, d, visitato, found);
            }
            p = l.next(p);
        }
    }
}

//metodo che verifica l'esistenza tra due nodi del grafo ed in caso positivo stampa tutto il cammino richiamando dfsPath()
template <class E, class P>
void matgraph<E, P>::findPath(node s, node d) const
{
    assert(isNode(s) && isNode(d));
    bool flag;
    //eseguo una verifica col vettore di marcatura
    int visitato[dimension];
    for (int i = 0; i < dimension; i++) {
        if (matrix[i].empty == false) {
            visitato[i] = 0; //nodo occupato
        }
        else {
            visitato[i] = -1; //nodo vuoto
        }
    }
    //restituisce vero se esiste un cammino da s in d
    flag = findPath(s, d, visitato, false);

    //se tale cammino esiste lo stampo
    if (flag) {
        cout << "\ncammino che congiunge il nodo (" << readLabel(s) << ") al nodo (" << readLabel(d) << ") : ";
        dfsPath(s, d);
    }
    else {
        cout << "\ncammino non esistente tra il nodo(" << readLabel(s) << ") e il nodo(" << readLabel(d) << ")";
    }
}

//funzione di supporto che restituisce vero se esiste un cammino tra due nodi del grafo avente in input il vettore di visite[]
template <class E, class P>
bool matgraph<E, P>::findPath(node s, node d, int *visitato, bool found) const
{
    //esame con marcatura del nodo s
    visitato[s.getId()] = 1; //marco il nodo s come visitato
    listnode lista_adiacenti = this->adjacent(s);
    if (!lista_adiacenti.empty())
    {
        auto pos = lista_adiacenti.begin();
        while (!lista_adiacenti.end(pos) && !found)
        {
            node n = lista_adiacenti.read(pos);
            if (n == d)
            {
                found = true;
            }
            if (visitato[n.getId()] == 0)
            {
                found = findPath(n, d, visitato, found);
            }
            pos = lista_adiacenti.next(pos);
        }
    }
    return (found);
}


//ALGORITMI DI VISITA---------------------------------------------------------------------------
//algoritmo dfs visita in profondita'
template <class E, class P>
void matgraph<E, P>::dfs(node u) const
{
    if (isNode(u))
    {
        int vettore[dimension];
        //inizializzo il vettore di marcatura
        for (int i = 0; i < dimension; i++)
        {
            vettore[i] = 0;
        }
        //marco le posizioni occupate dalla matrice
        for (int i = 0; i < dimension; i++)
        {
            if (matrix[i].empty == false)
            {
                vettore[i] = 1; //nodo occupato
            }
        }
        dfs(u, vettore);
    }
}

//funzione di servizio -> algoritmo dfs visita in profondita'
template <class E, class P>
void matgraph<E, P>::dfs(node u, int *visitato) const
{
    //esamino il nodo u
    cout << " (" << matrix[u.getId()].label << ") --> ";
    visitato[u.getId()] = 2; //nodo visitato
    listnode l = adjacent(u);
    if (!l.empty())
    {
        position_listnode p = l.begin();
        while (!l.end(p))
        {
            node n = l.read(p);
            if (visitato[n.getId()] == 1)
            {
                dfs(n, visitato);
            }
            p = l.next(p);
        }
    }
}

//algoritmo bfs visita in ampiezza  --> Utilizza coda con priorita
template <class E, class P>
void matgraph<E, P>::bfs(node n) const
{
    assert(isNode(n));

    //creo il vettore di marcatura
    bool visited[dimension];
    for (int i = 0; i < dimension; i++)
    {
        visited[i] = false;
    }
    //creo la coda per il bfs
    CodaP<node> queque;
    visited[n.getId()] = true;
    queque.inserisci(n.getId());
    while (!queque.insiemeVuoto())
    {
        node i = queque.min();
        cout << " (" << readLabel(i) << ") --> ";
        queque.cancellaMin();
        listnode l = adjacent(i);
        if (!l.empty())
        {
            for (auto p = l.begin(); !l.end(p); p = l.next(p))
            {
                if (visited[l.read(p).getId()] == false)
                {
                    visited[l.read(p).getId()] = true;
                    queque.inserisci(l.read(p));
                }
            }
        }
    }
}

//Altri OPERATORI-------------------------------------------------------------------------------
//Restituisce il totale dei nodi presenti nel grafo
template <class E, class P>
int matgraph<E, P>::numNodes() const
{
    return (nodes);
}

//Restituisce il totale degli archi presenti nel grafo
template <class E, class P>
int matgraph<E, P>::numArches() const
{
    return (arches);
}

//metodo che restituisce vero se la matrice di adiacenza e' nulla
template <class E, class P>
bool matgraph<E, P>::isEmptyMatrix() const
{
    return (matrix == nullptr);
}

//funzione che restituisce il numero di archi entranti al nodo a cui si applica
template <class E, class P>
int matgraph<E, P>::inDegree(node n) const
{
    assert(isNode(n));
    int numarchi = 0;
    //scorro la lista dei nodi
    for (int i = 0; i < dimension; i++)
    {
        //verifico se l'i-esimo nodo fa un arco con n, in caso positivo aumento il contatore
        if (!matrix[i].arches[n.getId()].empty)
        {
            numarchi++;
        }
    }
    return (numarchi);
}

//funzione che restituisce il numero di archi uscenti al nodo a cui si applica
template <class E, class P>
int matgraph<E, P>::outDegree(node n) const
{
    assert(isNode(n));
    int numarchi = 0;

    for (int j = 0; j < dimension; j++)
    {
        if (!matrix[n.getId()].arches[j].empty)
        {
            numarchi++;
        }
    }

    return (numarchi);
}

//metodo che  restituisce la media del numero di archi uscenti per ogni nodo del grafo
template <class E, class P>
double matgraph<E, P>::meanOutDegree() const
{
    double media = 0;
    if (!this->empty())
    {
        for (int i = 0; i < dimension; i++)
        {
            if (!matrix[i].empty)
            {
                node nodegraph(i);
                media = media + outDegree(nodegraph);
            }
        }
        media = media / this->numNodes();
    }
    return (media);
}

#endif