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
	ListaS<NodoG<T>* > ResultPath;
	ListaS<NodoG<T>* > AgendaBBD;
	NodoG<T>* firstBBD;
	NodoG<T>* lastBBD;
public:
	Grafo();
	~Grafo();
	void InsertaNodo(NodoG<T>* data);
	void CreaConexion(NodoG<T>* nodo1, NodoG<T>* nodo2);
	void BFS(NodoG<T>* search);
	void DFS(NodoG<T>* search);
	void DFSL(NodoG<T>* search, int MaxLevel);
	void BPI(NodoG<T>* search, int StartLevel);
	void BBD(NodoG<T>* search);
	void Reset();
	void PrintResult();
	void PrintPath(ListaS<NodoG<T>*> l);
	void SetFirst(NodoG<T>* f);
	void Dijkstra(NodoG<T>* search);
	void SafePath(NodoG<T>* search);
	void Astar(NodoG<T>* search);
	void Memory(NodoG<T>* search);
	void HillClimbing(NodoG<T>* search);
private:
	void DFSR(NodoG<T>* n, NodoG<T>* previous, NodoG<T>* search);
	void DFSLR(NodoG<T>* n, NodoG<T>* previous, NodoG<T>* search, int level, int MaxLevel);
	void BPIR(NodoG<T>* n, NodoG<T>* previous, NodoG<T>* search, int level, int MaxLevel);
	bool BBDBFS(NodoG<T>* node, int level);
	int AstarHeuristic(NodoG<T>* node1, NodoG<T>* node2);
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
* Imprime Los resultados
*
* @param NULL
*/
template <class T>
void Grafo<T>::PrintResult()
{
	for (int i = ResultPath.size - 1; i >= 0; i--)
	{
		cout << i << ") "<< (ResultPath.Get_at(i)->value)->nodoData << "\n";
	}
	if (ResultPath.size == 0)
	{
		std::cout << "No Path Found";
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
	for (int i = l.size - 1; i >= 0; i--)
	{
		std::cout << i << ")" << l.Get_at(i)->value->nodoData << "\n";
	}
}

/**
* Hace una Búsqueda por aplitud dentro del Grafo
*
* @param NodoG<T>* search (El nodo que se está Buscando)
*/
template <class T>
void Grafo<T>::BFS(NodoG<T>* search)
{
	ListaS<NodoG<T>*> Agenda;
	ListaS<NodoG<T>*> Visited;
	int level = 1;

	if (first != search)
	{
		//Visited.Add(*first);
		first->visited = true;
		//Add Sons
		for (int i = 0; i < first->l.size; i++)
		{
			(first->l.Get_at(i)->value)->previous = first;
			(first->l.Get_at(i))->value->cost = level;
			Agenda.Add((first->l.Get_at(i)->value));
		}
	}

	NodoG<T>* current = first;
	NodoG<T>* foundN = first;
	bool found = false;
	while (current != search)
	{
		for (int i = 0; i < Agenda.size; i++)
		{		
			if (Agenda.Get_at(i)->value->cost == level && Agenda.Get_at(i)->value->visited == false && found == false)
			{
				current = nullptr;
				current = (Agenda.Get_at(i)->value);
				if (current != search) //si es diferente agregas los hijos
				{
					//cout << "Adding sons of current: " << (current->nodoData) << ":" << current << std::endl;
					//cout << "{" << std::endl;
					for (int j = 0; j < current->l.size; j++)
					{
						current->visited = true;
						if ((current->l.Get_at(j)->value)->visited == false)
						{
							NodoG<T>* son = nullptr;
							son = (current->l.Get_at(j)->value);
							son->previous = current;
							son->cost = level + 1;
							//cout << "\t" << son->nodoData << ":" << son << std::endl;

							Agenda.Add(son); //Add sons of current
						}
					}
					//cout << "}" << std::endl;
				}
				else
				{
					found = true;
					foundN = current;
					break;
				}
				
			}
			else
			{
				//YA lo encontró
			}
		}
		level++;

	}
	while (foundN != nullptr)
	{
		ResultPath.Add(foundN);
		foundN = foundN->previous;
	}
	PrintResult();
	
}

/**
* Hace una Búsqueda por profundidad dentro del Grafo
*
* @param NodoG<T>* search (El nodo que se está Buscando)
*/
template <class T>
void Grafo<T>::DFS(NodoG<T>* search)
{	
	Reset();
	DFSR(first, nullptr, search);
	PrintResult();
}

/**
* Hace una Búsqueda recursivamente por profundidad dentro del Grafo
* Solo se debe usar dentro de la clase
* @param NodoG<T>* search (El nodo que se está Buscando)
*/
template <class T>
void Grafo<T>::DFSR(NodoG<T>* n, NodoG<T>* previous, NodoG<T>* search)
{
	if (n->visited == false)
	{
		n->previous = previous;
		n->visited = true;
		if (n == search)
		{
			std::cout << "Se encontro\n";
			NodoG<T>* Result = n;
			while (Result != nullptr)
			{
				ResultPath.Add(Result);
				Result = Result->previous;
			}
			//ResultPath.Reverse();
		}

		else if (n->l.size != 0)
		{
			for(int i = 0; i < n->l.size; i++)
			{
				NodoG<T>* son = n->l.Get_at(i)->value;
				if (son->visited == false)
				{
					DFSR(son, n, search);
				}
			}
		}

		else
		{
			return;
		}
	}
	else
	{
		return;
	}
}

/**
* Hace una Búsqueda por profundidad limitada dentro del Grafo
* 
* @param NodoG<T>* search (El nodo que se está Buscando)
* @param int MaxLevel El nivel máximo de profundidad que va a buscar
*/
template <class T>
void Grafo<T>::DFSL(NodoG<T>* search, int MaxLevel)
{
	Reset();
	DFSLR(first, nullptr, search, 0, MaxLevel);
	PrintResult();
}

/**
* Hace una Búsqueda recursivamente por profundidad limitada dentro del Grafo
* Solo se debe usar dentro de la clase
* @param NodoG<T>* search (El nodo que se está Buscando)
* @param NodoG<T>* n (El nodo actual)
* @param NodoG<T>* previous (El nodo anterior)
* @param int level (El nivel de profundidad actual)
* @param int MacLevel (El nivel de profundidad Máximo)
*/
template <class T>
void Grafo<T>::DFSLR(NodoG<T>* n, NodoG<T>* previous, NodoG<T>* search, int level, int MaxLevel)
{
	if (n->visited == false && level <= MaxLevel)
	{
		n->previous = previous;
		n->visited = true;
		if (n == search)
		{
			//Debug.Log("Se encontró");
			NodoG<T>* Result = n;
			while (Result != nullptr)
			{
				ResultPath.Add(Result);
				Result = Result->previous;
			}
			//ResultPath.Reverse();
		}

		else if (n->l.size != 0)
		{
			for(int i = 0; i < n->l.size; i++)
			{
				NodoG<T>* son = n->l.Get_at(i)->value;
				if (son->visited == false)
				{
					DFSLR(son, n, search, level + 1, MaxLevel);
				}
			}
		}

		else
		{
			return;
		}
	}
	else
	{
		return;
	}
}

/**
* Hace una Búsqueda por profundidad iterativa dentro del Grafo
*
* @param NodoG<T>* search (El nodo que se está Buscando)
* @param int StartLevel El nivel de profundidad inicial con el que se va a buscar
*/
template <class T>
void Grafo<T>::BPI(NodoG<T>* search, int StartLevel)
{
	int level = StartLevel;
	bool end = false;
	Reset();
	BPIR(first, nullptr, search, 0, StartLevel);

	while (end != true)
	{
		end = true;
		for(int i = 0; i < AllNodes.size; i++)
		{
			if (AllNodes.Get_at(i)->value->visited == false)
			{
				end = false;
			}
		}
		if (ResultPath.size == 0 && end == false)
		{
			Reset();
			level++;
			BPIR(first, nullptr, search, 0, level);
		}
		else
		{
			PrintResult();
		}
		if (ResultPath.size != 0)
		{
			end = true;
			PrintResult();
		}
	}

}

/**
* Hace una Búsqueda recursivamente por profundidad limitada dentro del Grafo
* Solo se debe usar dentro de la clase
* @param NodoG<T>* search (El nodo que se está Buscando)
* @param NodoG<T>* n (El nodo actual)
* @param NodoG<T>* previous (El nodo anterior)
* @param int level (El nivel de profundidad actual)
* @param int MacLevel (El nivel de profundidad Máximo)
*/
template <class T>
void Grafo<T>::BPIR(NodoG<T>* n, NodoG<T>* previous, NodoG<T>* search, int level, int MaxLevel)
{
	if (n->visited == false && level <= MaxLevel)
	{
		n->previous = previous;
		n->visited = true;
		if (n == search)
		{
			NodoG<T>* Result = n;
			while (Result != nullptr)
			{
				ResultPath.Add(Result);
				Result = Result->previous;
			}
			//esultPath.Reverse();
		}

		else if (n->l.size != 0)
		{
			for(int i = 0 ; i < n->l.size; i++)
			{
				NodoG<T>* son = n->l.Get_at(i)->value;
				if (son->visited == false)
				{
					BPIR(son, n, search, level + 1, MaxLevel);
				}
			}
		}

		else
		{
			return;
		}
	}
	else
	{
		return;
	}
}

/**
* Hace una Búsqueda Bidireccional en el Grafo
* 
* @param NodoG<T>* search (El nodo que se está Buscando)
*/
template <class T>
void Grafo<T>::BBD(NodoG<T>* search)
{
	Reset();
	ListaS<NodoG<T>*> Path1;
	ListaS<NodoG<T>*> Path2;
	int level = 0;
	bool found = false;

	first->Bidilvl = 1;
	search->Bidilvl = 2;
	BBDBFS(first, level);
	BBDBFS(search, level);

	while (!found)
	{
		for (int i = 0; i < AgendaBBD.size; i++)
		{
			if (AgendaBBD.Get_at(i)->value->cost == level && AgendaBBD.Get_at(i)->value->visited == false)
			{
				AgendaBBD.Get_at(i)->value->visited = true;
				if (BBDBFS(AgendaBBD.Get_at(i)->value, level++))
				{
					found = true;
				}
			}

		}
		level++;
	}


	while (firstBBD != nullptr)
	{
		Path1.Add(firstBBD);
		firstBBD = firstBBD->previous;
	}

	while (lastBBD != nullptr)
	{
		Path2.Add(lastBBD);
		lastBBD = lastBBD->previous;
	}

	//Path2.Reverse();
	for(int i = Path1.size - 1; i >= 0; i--)
	{
		Path2.Add(Path1.Get_at(i)->value);
	}
	//Path2.Reverse();
	PrintPath(Path2);
	//PrintPath(AgendaBBD);
}

/**
* Hace una Búsqueda Bidireccional en el Grafo
* Esta función solo se dedbe usar dentro de la clase
* @param NodoG<T>* search (El nodo que se está Buscando)
* @param int level (El nivel en el que estoy)
*/
template <class T>
bool Grafo<T>::BBDBFS(NodoG<T>* node, int level)
{
	for (int i = 0; i < node->l.size; i++)
	{
		if (node->visited == false)
		{
			node->l.Get_at(i)->value->previous = node;
			node->l.Get_at(i)->value->cost = level;
			node->l.Get_at(i)->value->Bidilvl = node->Bidilvl; //Para saber cual busqueda es
			AgendaBBD.Add(node->l.Get_at(i)->value);
		}
		else if (node->Bidilvl != 0 && node->Bidilvl != node->l.Get_at(i)->value->Bidilvl)
		{
			firstBBD = node;
			lastBBD = node->l.Get_at(i)->value;
			return true;
		}
	}
	return false;
}

/**
* Hace una Búsqueda DIJSTRA en el Grafo
* Esta función solo se dedbe usar dentro de la clase
* @param NodoG<T>* search (El nodo que se está Buscando)
*/
template <class T>
void Grafo<T>::Dijkstra(NodoG<T>* search)
{
	ListaS<NodoG<T>*> Agenda;
	ListaS<NodoG<T>*> Visited;
	int level = 1;

	if (first != search)
	{
		//Visited.Add(*first);
		first->visited = true;
		//Add Sons
		for (int i = 0; i < first->l.size; i++)
		{
			(first->l.Get_at(i)->value)->previous = first;
			(first->l.Get_at(i))->value->cost = level;
			Agenda.Add((first->l.Get_at(i)->value));
		}
	}

	NodoG<T>* current = first;
	NodoG<T>* foundN = first;
	bool found = false;
	while (current != search)
	{
		for (int i = 0; i < Agenda.size; i++)
		{
			if (Agenda.Get_at(i)->value->cost == level && Agenda.Get_at(i)->value->visited == false && found == false)
			{
				current = nullptr;
				current = (Agenda.Get_at(i)->value);
				if (current != search) //si es diferente agregas los hijos
				{
					//cout << "Adding sons of current: " << (current->nodoData) << ":" << current << std::endl;
					//cout << "{" << std::endl;
					for (int j = 0; j < current->l.size; j++)
					{
						current->visited = true;
						if ((current->l.Get_at(j)->value)->visited == false)
						{
							NodoG<T>* son = nullptr;
							son = (current->l.Get_at(j)->value);
							son->previous = current;
							son->cost = current->cost + 1;
							//cout << "\t" << son->nodoData << ":" << son << std::endl;

							Agenda.Add(son); //Add sons of current
						}
					}
					//cout << "}" << std::endl;
				}
				else
				{
					found = true;
					foundN = current;
					break;
				}

			}
			else
			{
				//YA lo encontró
			}
		}
		level++;

	}
	int finalcost = foundN->cost;
	while (foundN != nullptr)
	{
		ResultPath.Add(foundN);
		foundN = foundN->previous;
	}
	PrintResult();
	std::cout << "Final Cost: " << finalcost << "\n2";
}

/**
* Hace una Búsqueda Por el camino Menos Ñero
* 
* @param NodoG<T>* search (El nodo que se está Buscando)
*/
template <class T>
void Grafo<T>::SafePath(NodoG<T>* search)
{
	ListaS<NodoG<T>*> Agenda;
	ListaS<NodoG<T>*> Visited;
	int level = 1;

	if (first != search)
	{
		//Visited.Add(*first);
		first->visited = true;
		//Add Sons
		for (int i = 0; i < first->l.size; i++)
		{
			(first->l.Get_at(i)->value)->previous = first;
			(first->l.Get_at(i))->value->cost = level;
			Agenda.Add((first->l.Get_at(i)->value));
		}
	}

	NodoG<T>* current = first;
	NodoG<T>* foundN = first;
	bool found = false;
	while (current != search)
	{
		for (int i = 0; i < Agenda.size; i++)
		{
			if (Agenda.Get_at(i)->value->cost == level && Agenda.Get_at(i)->value->visited == false && found == false)
			{
				current = nullptr;
				current = (Agenda.Get_at(i)->value);
				if (current != search) //si es diferente agregas los hijos
				{
					//cout << "Adding sons of current: " << (current->nodoData) << ":" << current << std::endl;
					//cout << "{" << std::endl;
					for (int j = 0; j < current->l.size; j++)
					{
						current->visited = true;
						if ((current->l.Get_at(j)->value)->visited == false)
						{
							NodoG<T>* son = nullptr;
							son = (current->l.Get_at(j)->value);
							son->previous = current;
							son->cost = (current->cost + 1 + current->Danger);
							//cout << "\t" << son->nodoData << ":" << son << std::endl;

							Agenda.Add(son); //Add sons of current
						}
					}
					//cout << "}" << std::endl;
				}
				else
				{
					found = true;
					foundN = current;
					break;
				}

			}
			else
			{
				//YA lo encontró
			}
		}
		level++;

	}
	int finalcost = foundN->cost;
	while (foundN != nullptr)
	{
		ResultPath.Add(foundN);
		foundN = foundN->previous;
	}
	PrintResult();
	std::cout << "Final Cost: " << finalcost << "\n2";
}

/**
* Hace el cálculo del A*
*
* @param NodoG<T>* node1 (Para sacar distancias)
* @param NodoG<T>* node2 (Para sacar distancias)
* @return INT result
*/
template <class T>
int Grafo<T>::AstarHeuristic(NodoG<T>* node1, NodoG<T>* node2)
{
	return sqrtf((node1->x* node1->x) + (node2->y* node2->y));
}

/**
* Hace una Búsqueda con A*
*
* @param NodoG<T>* search (El nodo que se está Buscando)
*/
template <class T>
void Grafo<T>::Astar(NodoG<T>* search)
{
	ListaS<NodoG<T>*> Agenda;
	ListaS<NodoG<T>*> Visited;
	int level = 1;

	if (first != search)
	{
		//Visited.Add(*first);
		first->visited = true;
		//Add Sons
		for (int i = 0; i < first->l.size; i++)
		{
			(first->l.Get_at(i)->value)->previous = first;
			(first->l.Get_at(i))->value->cost = level;
			Agenda.Add((first->l.Get_at(i)->value));
		}
	}

	NodoG<T>* current = first;
	NodoG<T>* foundN = first;
	bool found = false;
	while (current != search)
	{
		for (int i = 0; i < Agenda.size; i++)
		{
			if (Agenda.Get_at(i)->value->cost == level && Agenda.Get_at(i)->value->visited == false && found == false)
			{
				current = nullptr;
				current = (Agenda.Get_at(i)->value);
				if (current != search) //si es diferente agregas los hijos
				{
					//cout << "Adding sons of current: " << (current->nodoData) << ":" << current << std::endl;
					//cout << "{" << std::endl;
					for (int j = 0; j < current->l.size; j++)
					{
						current->visited = true;
						if ((current->l.Get_at(j)->value)->visited == false)
						{
							NodoG<T>* son = nullptr;
							son = (current->l.Get_at(j)->value);
							son->previous = current;
							son->cost = current->cost + AstarHeuristic(son, search); //A*Heuristic
							Agenda.Add(son); //Add sons of current
						}
					}
					//cout << "}" << std::endl;
				}
				else
				{
					found = true;
					foundN = current;
					break;
				}

			}
			else
			{
				//YA lo encontró
			}
		}
		level++;

	}
	int finalcost = foundN->cost;
	while (foundN != nullptr)
	{
		ResultPath.Add(foundN);
		foundN = foundN->previous;
	}
	PrintResult();
	std::cout << "Final Cost: " << finalcost << "\n2";
}

/**
* Hace una Búsqueda con Memory Heuristic
*
* @param NodoG<T>* search (El nodo que se está Buscando)
*/
template <class T>
void Grafo<T>::Memory(NodoG<T>* search)
{
	ListaS<NodoG<T>*> Agenda;
	ListaS<NodoG<T>*> Visited;
	NodoG<T>* Temp = first; // esta es la diferencia
	int level = 1;

	if (first != search)
	{
		//Visited.Add(*first);
		first->visited = true;
		//Add Sons
		for (int i = 0; i < first->l.size; i++)
		{
			(first->l.Get_at(i)->value)->previous = first;
			(first->l.Get_at(i))->value->cost = level;
			Agenda.Add((first->l.Get_at(i)->value));
		}
	}

	NodoG<T>* current = first;
	NodoG<T>* foundN = first;
	bool found = false;
	while (current != search)
	{
		for (int i = 0; i < Agenda.size; i++)
		{
			if (Agenda.Get_at(i)->value->cost == level && Agenda.Get_at(i)->value->visited == false && found == false)
			{
				current = nullptr;
				current = (Agenda.Get_at(i)->value);
				if (current != search) //si es diferente agregas los hijos
				{
					//cout << "Adding sons of current: " << (current->nodoData) << ":" << current << std::endl;
					//cout << "{" << std::endl;
					for (int j = 0; j < current->l.size; j++)
					{
						current->visited = true;
						if ((current->l.Get_at(j)->value)->visited == false)
						{
							NodoG<T>* son = nullptr;
							son = (current->l.Get_at(j)->value);
							son->previous = current;
							son->cost = current->cost + AstarHeuristic(son, search); //A*Heuristic
							if (Temp->cost > son->cost)
							{
								current = Temp;
							}
							Agenda.Add(son); //Add sons of current
						}
					}
				}
				else
				{
					found = true;
					foundN = current;
					break;
				}

			}
			else
			{
				//YA lo encontró
			}
		}
		level++;
		Temp = current;
	}
	int finalcost = foundN->cost;
	while (foundN != nullptr)
	{
		ResultPath.Add(foundN);
		foundN = foundN->previous;
	}
	PrintResult();
	std::cout << "Final Cost: " << finalcost << "\n2";
}

/**
* Hace una Búsqueda con HillClimbing
*
* @param NodoG<T>* search (El nodo que se está Buscando)
*/
template <class T>
void Grafo<T>::HillClimbing(NodoG<T>* search)
{
	int Optimal = 10000000;
	ListaS<NodoG<T>*> Agenda;
	ListaS<NodoG<T>*> Visited;
	int level = 1;

	if (first != search)
	{
		//Visited.Add(*first);
		first->visited = true;
		//Add Sons
		for (int i = 0; i < first->l.size; i++)
		{
			(first->l.Get_at(i)->value)->previous = first;
			(first->l.Get_at(i))->value->cost = level;
			Agenda.Add((first->l.Get_at(i)->value));
		}
	}

	NodoG<T>* current = first;
	NodoG<T>* foundN = first;
	bool found = false;
	while (current != search)
	{
		for (int i = 0; i < Agenda.size; i++)
		{
			if (Agenda.Get_at(i)->value->cost == level && Agenda.Get_at(i)->value->visited == false && found == false)
			{
				current = nullptr;
				current = (Agenda.Get_at(i)->value);
				if (current != search) //si es diferente agregas los hijos
				{
					//cout << "Adding sons of current: " << (current->nodoData) << ":" << current << std::endl;
					//cout << "{" << std::endl;
					for (int j = 0; j < current->l.size; j++)
					{
						current->visited = true;
						if ((current->l.Get_at(j)->value)->visited == false)
						{
							NodoG<T>* son = nullptr;
							son = (current->l.Get_at(j)->value);
							son->previous = current;
							son->cost = current->cost + AstarHeuristic(son, search); //A*Heuristic
							if (Optimal < son->cost)
							{
								level = Optimal;
								Optimal = son->cost;
							}
							Agenda.Add(son); //Add sons of current
						}
					}
					//cout << "}" << std::endl;
				}
				else
				{
					found = true;
					foundN = current;
					break;
				}

			}
			else
			{
				//YA lo encontró
			}
		}
		level++;

	}
	int finalcost = foundN->cost;
	while (foundN != nullptr)
	{
		ResultPath.Add(foundN);
		foundN = foundN->previous;
	}
	PrintResult();
	std::cout << "Final Cost: " << finalcost << "\n2";
}