#pragma once
#include "NodoG.h"
#include "NodoT.h"
#include "ListaS.h"
#include <exception>
#include <iostream>

using std::cout;

template <class T>
class Grafo
{
private:
	int size;
	NodoG<T> *first;
	ListaS<NodoG<T>* > AllNodes;
public:
	Grafo();
	~Grafo();
	void InsertaNodo(NodoG<T>* data);
	void CreaConexion(NodoG<T>* nodo1, NodoG<T>* nodo2);
	void eliminarTodoExcepto();
	ListaS<NodoG<T>*> GetAllNodes();
	NodoG<T>* GetFirst();
	void Reset();
	void PrintPath(ListaS<NodoG<T>*> l);
	void SetFirst(NodoG<T>* f);
};

template <class T>
Grafo<T>::Grafo()
{
	first = NULL;
}

template <class T>
Grafo<T>::~Grafo()
{

}

template <class T>
void Grafo<T>::SetFirst(NodoG<T>* f)
{
	first = f;
}

/**
* Inserta los nodos al grafo, pero ninguno está conectado
*
* @param NodoG<T>* Nodo1 (Dato que se va a insertar)
*/
template <class T>
void Grafo<T>::InsertaNodo(NodoG<T>* data)
{
	if (first == nullptr)
	{
		first = data;
	}
	AllNodes.Add(data);
}


/**
* Crea Conexiones entre los dos nodos Específicados
*
* @param NodoG<T>* Nodo1,
* @param NodoG<T>* Nodo2,
*/
template <class T>
void Grafo<T>::CreaConexion(NodoG<T>* nodo1, NodoG<T>* nodo2)
{
	nodo1->l.Add(nodo2);
	nodo2->l.Add(nodo1);
}

/*Eliminar todo excepto al nodo que se quiera salvar. Esto es para que se eliminen las demás opciones del gato y esta se quede como nuevo padre*/
template<class T>
inline void Grafo<T>::eliminarTodoExcepto() {
	try{
		NodoT<NodoG<int>*>* iterador = AllNodes.first;
		while (iterador != nullptr) {
			NodoT<NodoG<int>*>* temp = iterador->next;
			delete iterador;
			iterador = nullptr;
			iterador = temp;
		}
	} catch (...) {

	}
}

/*Regresa la Lista AllNodes*/
template<class T>
inline ListaS<NodoG<T>*> Grafo<T>::GetAllNodes() {
	return AllNodes;
}

/*Regresa el primer elemento de la lista del grafo*/
template<class T>
inline NodoG<T>* Grafo<T>::GetFirst() {
	return first;
}

/**
* Cambia el visisted de todos los nodos a Falso para poder realizar más operaciones con este
*
* @param NULL
*/
template <class T>
void Grafo<T>::Reset()
{
	for (int i = 0; i < AllNodes.size; i++)
	{
		(AllNodes.Get_at(i)->value)->visited = false;
	}
}



/**
* Imprime una lista
*
* @param ListaS<NodoG<T>*> l (La lista que se quiere imprimir)
*/
template <class T>
void Grafo<T>::PrintPath(ListaS<NodoG<T>*> l )
{
	//for (int i = l.size - 1; i >= 0; i--)
	//{
	//	std::cout << i << ")" << l.Get_at(i)->value->nodoData << "\n";
	//}

	for(int i = 0; i < l.size;  i++) {
		std::cout << i << ")" << l.Get_at(i)->value->nodoData << "\tPosicion[" << (l.Get_at(i)->value)->x << "][" << (l.Get_at(i)->value)->y << "]\n";
	}
}