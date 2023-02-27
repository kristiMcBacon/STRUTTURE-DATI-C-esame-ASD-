#include "Grafo.h"

#include <string>
using namespace std;

int main(){
	Grafo<string,double> G;

	Grafo<string, double>::nodo n1=1,n2=2,n3=3,n4=4,n5=5,n6=6;

	G.insnodo(n1);
	G.scrivinodo("a", n1);
	G.insnodo(n2);
	G.scrivinodo("b", n2);
	G.insnodo(n3);
	G.scrivinodo("c", n3);
	G.insnodo(n4);
	G.scrivinodo("d", n4);
	G.insnodo(n5);
	G.scrivinodo("e", n5);
	G.insnodo(n6);
	G.scrivinodo("f", n6);



	G.insarco(n1,n2);
	G.insarco(n1,n3);
	G.insarco(n1,n5);
	G.insarco(n2,n4);
	G.insarco(n2,n6);
	G.insarco(n3,n4);
	G.insarco(n3,n6);
	G.insarco(n4,n1);
	G.insarco(n5,n2);
	G.insarco(n5,n6);
	G.insarco(n6,n4);

    G.scriviarco(1.0, n1,n2);
	G.scriviarco(0.9, n1,n3);
	G.scriviarco(0.3, n1,n6);
	G.scriviarco(0.1,n2,n4);
	G.scriviarco(0.2,n2,n6);
	G.scriviarco(1.0,n3,n4);
	G.scriviarco(0.7,n3,n6);
	G.scriviarco(0.5,n4,n1);
	G.scriviarco(0.4,n5,n2);
	G.scriviarco(0.2,n5,n6);
	G.scriviarco(0.1,n6,n4);

	cout << "\nNumNodi " << G.numnodi();
	//cout << "\nNumArchi " << G.numArchi();

	G.cancnodo(n6);

	cout <<"\nNumNodi " << G.numnodi() << endl<<"Arco->"<<G.leggiarco(n2,n1)<<endl;

    cout<<"\nNodi adiacenti a n1->"<<G.adiacenti(n3);


	cout<<"\n\n------------------------FINE--------------------------------";


}
