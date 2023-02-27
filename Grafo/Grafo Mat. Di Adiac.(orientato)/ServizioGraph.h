//definisco la classe archinfo che contiene le info di un nodoarco
template <class P>
class archInfo {
public:
    P weight;           //Peso
    bool empty;         //Vuoto

    //COSTRUTTORE
    archInfo() {
        empty = true;
        weight = P(NULL);
    }
};

//----------------------------------------------------------------------------------------------------------------------------

//definisco la classe nodeinfo che contiene le info del nodo
template <class E, class P>
class nodeInfo{
public:

    E label;
    bool empty;
    archInfo<P> *arches;
    nodeInfo()
    {
        label = "";
        empty = true;
    }
    ~nodeInfo()
    {
        if (!empty)
        {
            delete[] arches;
            arches = nullptr;
        }
    }
};

//----------------------------------------------------------------------------------------------------------------------------

//definisco la classe nodografo contenente l'id del grafo nella matrice di adiacenza
class nodeGraph
{
public:
    nodeGraph(int id) //costruttore con parametro id
    {
        idnode = id;
    }
    nodeGraph() //costruttore di default
    {
        idnode = 0;
    }
    int getId() //restituisce l'id del nodo
    {
        return (idnode);
    }
    void setId(int id) {
        idnode = id;
    }

    nodeGraph &operator=(const nodeGraph &n) {
        idnode = n.idnode;
        return *(this);
    }

    bool operator==(const nodeGraph &n) {
        return (idnode == n.idnode);
    }
    bool operator<(const nodeGraph &n) {
        return (idnode < n.idnode);
    }
    bool operator>(const nodeGraph &n) {
        return (idnode > n.idnode);
    }

private:
    int idnode;
};

//----------------------------------------------------------------------------------------------------------------------------

//CALSSE ARCO
template <class P, class N>
class arch  {
public:
    N node1;  //nodo uscente a->b
    N node2;  //nodo entrante b<-a
    P weight; //peso
};