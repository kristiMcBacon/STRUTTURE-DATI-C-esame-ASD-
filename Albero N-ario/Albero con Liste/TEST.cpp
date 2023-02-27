#include "Albero.h"

int main(){

	Albero<char> Tree, Tree2;

	Albero<char>::nodo n;
	Tree.insRadice(n);
	Tree.scriviNodo(Tree.radice(),'r');

	Tree.insPrimoFiglio(Tree.radice(), 'a');
	Tree.insPrimoFiglio(Tree.radice(), 'b');

	n = Tree.radice();
	n = Tree.primoFiglio(n);

	Tree.insFratello(n, 'd');

	n = Tree.radice();
	n = Tree.primoFiglio(n);
	Tree.insPrimoFiglio(n, 'e');
	Tree.insPrimoFiglio(n, 'f');

	/*Tree.stampa();	

	n = Tree.radice();
	n = Tree.primoFiglio(n);
	Tree.cancSottoAlbero(n);*/

	Tree.stampa();
    cout<<"\n\n\n";

	Albero<char>::nodo n2;
	Tree2.insRadice(n2);
	Tree2.scriviNodo(Tree.radice(),'x');

	Tree2.insPrimoFiglio(Tree.radice(), 'y');
	Tree2.insPrimoFiglio(Tree.radice(), 'z');
	Tree2.stampa();


	return 0;
}