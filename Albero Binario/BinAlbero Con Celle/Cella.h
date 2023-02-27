#ifndef CELLA_H
#define CELLA_H

template <class T>
class Cella{
public:
    typedef Cella<T>* Nodo;

    Cella();             //COSTRUTTORE
    ~Cella();            //DISTRUTTORE
    Cella(const Cella& ); //COSTRUTTORE DI COPIA

    //OPERATORI--------------------------------
    //METODI SET
    void setFiglioSx(Nodo);
    void setFiglioDx(Nodo);
    void setPadre(Nodo);
    void setEtichetta(T);

    //METODI GET
    Nodo getFiglioSx();
    Nodo getFiglioDx();
    Nodo getPadre();
    T getEtichetta();

    //SOVRACCARICO OPERATORI------------------------------
    bool operator == (Cella<T>&);         //SOVRACCARICO OPERATORE UGUAGLIANZA ==
    void operator = (const Cella&);      //SOVRACCARICO OPERATORE ASSEGNAZIONE =

private:
    Nodo FiglioDx;
    Nodo FiglioSx;
    Nodo Padre;
    T Etichetta;
};
//____________________________________________________________________________________________________________

//COSTRUTTORE
template <class T>
Cella<T>::Cella(){
    FiglioDx=nullptr;
    FiglioSx=nullptr;
    Padre=nullptr;
}

//DISTRUTTORE
template <class T>
Cella<T>::~Cella(){}

//COSTRUTTORE DI COPIA
template <class T>
Cella<T>::Cella(const Cella& c){
    Etichetta = c.Etichetta;
    FiglioDx = c.FiglioDx;
    FiglioSx = c.FiglioSx;
    Padre = c.Padre;
 }

//OPERATORI--------------------------------
//METODI SET
template <class T>
void Cella<T>::setFiglioSx(Nodo sx){
    FiglioSx=sx;
}

template <class T>
void Cella<T>::setFiglioDx(Nodo dx){
    FiglioDx=dx;
}

template <class T>
void Cella<T>::setPadre(Nodo p){
    Padre=p;
}

template <class T>
void Cella<T>::setEtichetta(T e){
    Etichetta=e;
}

//METODI GET
template <class T>
Cella<T>* Cella<T>::getFiglioSx(){
    return FiglioSx;
}

template <class T>
Cella<T>* Cella<T>::getFiglioDx(){
    return FiglioDx;
}

template <class T>
Cella<T>* Cella<T>::getPadre(){
    return Padre;
}

template <class T>
T Cella<T>::getEtichetta(){
    return Etichetta;
}

//SOVRACCARICO OPERATORI
//SOVRACCARICO OPERATORE UGUAGLIANZA ==
template <class T>
bool Cella<T>::operator==(Cella<T>&  b){
    if(Etichetta == b.Etichetta)
        return true;
    else
        return false;
}

//SOVRACCARICO OPERATORE ASSEGNAZIONE =
template <class T>
void Cella<T>::operator=(const Cella<T>& c ){
    Etichetta = c.Etichetta;
    Padre = c.Padre;
    FiglioDx = c.FiglioDx;
    FiglioSx = c.FiglioSx;
}

#endif