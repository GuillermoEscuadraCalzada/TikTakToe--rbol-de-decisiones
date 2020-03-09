#pragma once
#include "ListaS.h"
class Vector2 {
public:
	int x;
	int y;
	Vector2(int x, int y) : x(x), y(y) {};

	~Vector2(){}

	
};
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
	int coste;
	/*Este nodo recibe un elemento a guardar y recibe una posición dentro de la matriz
	 *@param[T dat] el valor que se le quiere guardar dependiendo del template
	 *@param[int x] el valor en x dentro de la matriz
	 *@param[int y] el valor en y dentro de la matriz*/
	NodoG<T>(T dat, int x, int y) : nodoData(dat), x(x), y(y) { coste = 0; }
	NodoG<T>(const NodoG<T> &n) : nodoData(n.nodoData) 
	{
		std::cout << "Se está creando copia\n";
	}
};