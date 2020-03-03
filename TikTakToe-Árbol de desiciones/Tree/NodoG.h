#pragma once
#include "ListaS.h"

template <class T>
class NodoG
{
public:
	bool visited = false;
	T nodoData; // Esto guarda el objeto deseado
	ListaS<NodoG<T>*> l; // esto guarda los apuntadores a los hijos
	NodoG<T>* previous; //Para saber de donde vengo
	int cost; //Cuanto me costó llegar aquí
	int Bidilvl; //De cual busqueda soy
	int Danger; //De cual busqueda soy
	int x;
	int y;
	NodoG<T>(T dat) : nodoData(dat) {}
	NodoG<T>(T dat, int d) : nodoData(dat), Danger(d) {}
	NodoG<T>(T dat, int x, int y) : nodoData(dat), x(x), y(y) {}
	NodoG<T>(const NodoG<T> &n) : nodoData(n.nodoData) 
	{
		std::cout << "Se está creando copia\n";
	}
};