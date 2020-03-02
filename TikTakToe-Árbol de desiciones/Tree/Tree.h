#ifndef TREE_H
#define TREE_H

#include <iostream>
using namespace std;
template<class T>
class Nodo {
public:
	T value;
	Nodo<T>* left; Nodo<T>* right;
	Nodo();
	Nodo(T value);
	~Nodo();
};
template<class T>
Nodo<T>::Nodo() {
	left = right = nullptr;
}

template<class T>
Nodo<T>::Nodo(T value) {
	left = right = nullptr;
	this->value = value;
}

template<class T>
inline Nodo<T>::~Nodo() {
}

template<class T>
class Tree {
public:
	void insertValue(Nodo<T>** toInsert, T value);
	void imprimirArbol(Nodo<T>* padre, int space);
	Nodo<T>* padre;
	Tree();
	~Tree();
private:

};

/*Ingresa valores al árbol, si es menor se irá al hijo izquierdo, si es mayor al hijo derecho
 *@param[Nodo<T>** root] la raíz a la cual se le añadirán hijos
 *@param[T value] el valor que se le añadirá al hijo*/
template<class T>
inline void Tree<T>::insertValue(Nodo<T>** root, T value) {
	try {
		Nodo<T>* tempNode = new Nodo<T>(value); //Crea un nodo temporal
		if(!*root) { //La raíz es nula
		   *root = tempNode;  //Toma valores en esta posición
		}else if(value < (*root)->value){ //El valor es menor al valor de la raíz
			insertValue(&(*root)->left, value); //Recursividad en el hijo izquierdo
		} else if(value >  (*root)->value) { //El valor es mayor a la raíz
			insertValue(&(*root)->right, value); //Recursividad en el hijo derecho
		} else if(value == (*root)->value) { //El valor es igual al de la razí
			throw(value);
		}
		return; 
	} catch(T val) {
		cout << "Este valor ya se encuentra dentro del arbol\n";
	}
	catch(exception & e) {
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}

/*Imprime el árbol, si la raíz actual no existe, regresa. Si existe, entra a sus hijos de la derecha, al terminar con los hijos, regresar e imprimir el valor actual, después se imprimen los hijos de la 
 *izquierda y se repite el proceso
 *@param[Nodo<T>* root] la raíz que se investigará
 *@param[int space] espacio entre notods para que se puedan ver separado*/
template<class T>
inline void Tree<T>::imprimirArbol(Nodo<T>* root, int space) {
	try {
		// Base case  
		if(!root)
			return;

		// Increase distance between levels  
		space += 5;

		// Process right child first  
		imprimirArbol(root->right, space);

		// Print current node after space  
		// count  
		cout << endl;
		for(int i = 5; i < space; i++)
			cout << " ";
		cout << root->value << "\n";

		// Process left child  
		imprimirArbol(root->left, space);
	} catch(exception & e) {
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}

/*Constructor de la clase árbol*/
template<class T>
Tree<T>::Tree() {
	padre = nullptr;
}

template<class T>
Tree<T>::~Tree() {
	delete padre;
	padre = nullptr;
}

#endif // !TREE_H


