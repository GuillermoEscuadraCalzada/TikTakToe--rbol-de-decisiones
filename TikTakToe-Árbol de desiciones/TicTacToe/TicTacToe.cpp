#include "TicTacToe.h"
TicTacToe* TicTacToe::ptr = nullptr;

/*Se imprimen los lugares vaciós dentro del arreglo de dos dimensiones donde sucederá el juego*/
void TicTacToe::SetUp() {
	try {
		/*Determinar qué se va a imprimir dentro de las casillas que tendrá el gameBoard*/
		for(int i = 0; i < lines; i++) {
			for(int j = 0; j < columns; j++) {
				gameBoard[i][j] = "_";
			}
		}
	} catch(exception & e) {
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}

/*Se imprimen los valores del tablero*/
void TicTacToe::printBoard() {
	try {

		cout << "\nTablero del juego\n";
		/*Recorre toda la matriz e imprime los valores*/
		for(int i = 0; i < lines; i++) {
			for(int j = 0; j < columns; j++) {
				cout << "| " << gameBoard[i][j] << " ";
			}
			cout << "|" << endl;
		}
		cout << endl;
	} catch(exception & e) {
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}

/*La clase será singleton, por lo que el constructor y destructor no se pueden conseguir de manera pública*/
TicTacToe* TicTacToe::GetPtr() {
	if(!ptr) //Si el apuntador es nulo, crea uno nuevo
		ptr = new TicTacToe();
	return ptr; //regresa el apuntador
}

/*Función que mandará a llamar las primer funciones del juego de TicTacToe*/
void TicTacToe::Init() {	
	try {
		running = true;
		posibilidades = new Grafo<string>();
		SetUp();
		printBoard();
	} catch(exception & e) {
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}

/*Actualizacíon constante del juego*/
void TicTacToe::Update() {
	while(running) {
		PlayerInput();
		//CheckWin();
		if(agentWin || playerWin)
			break;
		AgentTurn();
		/*copyBoard(); */
		//CheckWin();
		if(agentWin || playerWin)
			break;
		printBoard();
	}
	if (playerWin)
	{
		cout << "YOU WINNNNNNNNNNNNNNNNNNNNNN";
	}
	else
	{
		cout << "YOU LOOOOOOOOOOOOOOOOOOSE";
	}
}

/*Detecta la posición en la que el jugador decide poner su símbolo*/
void TicTacToe::PlayerInput() {
	try {

		cout << "Elige la fila donde se ubicara tu simbolo: ";
		cin >> x;  //Elemento en el eje X o en las líneas del gameBoard
		if(cin.fail() || x > columns - 1 || x < 0) 
			throw(x);
		
		cout << "\nElige la columna donde se ubicará tu simbolo: ";
		cin >> y; //Elemento en el eje Y o en las columnas del gameBoard
		if(cin.fail() || y > lines - 1 || y < 0) //El input fue uno no permitido o se pasó del número de líneas
			throw(x);

		if(gameBoard[x][y] == "O"|| gameBoard[x][y] ==  "X")
			cout << "Esa posicion ya fue elegida.\n";
		else {
			setNewBoard(x, y);
		}
		cout << endl;


	} catch(int x) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "You entered a wrong input" << endl;
	} catch(exception & e) {
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}


/*Se actualiza el nuevo gameboard en caso de que ingresen buenos inputs por parte del jugador*/
void TicTacToe::setNewBoard(int x, int y) {
	try {
		/*Se actualiza el input del jugador dentro de la matriz del juego*/
		for(int i = 0; i < lines; i++) {
			if(i == x) { //Si la i es igual a la x, avanza el la j
				for(int j = 0; j < columns; j++) {
					if(j == y) { //Si es igual, cambia el string a una O
						gameBoard[i][j] = "O";
					}
				}
			}
		}
	} catch(exception & e) {
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}

/*Checamos si se cumplen las condiciones de victoria*/
void TicTacToe::CheckWin()
{ 
	string checking;

	//Horzontales
	for (int j = 0; j < lines; j++)
	{
		if (gameBoard[0][j] == "O" || gameBoard[0][j] == "X")
		{ //Preguntar si el caracter es del jugador o del agente
			checking = gameBoard[0][j]; //Guardar el string de este elemento
			if (gameBoard[1][j] == checking && gameBoard[2][j] == checking)
			{ //Preguntar si en el espacio al lado de este elemento tiene string
				if (checking == "O") { //Preguntar si es del jugador
					playerWin = true; //Win es igual a true
					running = false; //Termina el juego
				} else if (checking == "X") { //El ganador es el agente
					agentWin = true; //Cambia el bool a verdadero
					running = false; //Rompe el while
				}
			}
		}
	}

	//Verticales
	for (int i = 0; i < lines; i++)
	{ 
		if (gameBoard[i][0] == "O" || gameBoard[i][0] == "X")
		{ //Pregunta si es el jugador o es el agente
			checking = gameBoard[i][0];
			if (gameBoard[i][1] == checking && gameBoard[i][2] == checking)
			{ //Checa si las verticales son del mismo string
				if (checking == "O")
				{ //Checa si es string del jugador
					running = false; //Termina el while
					playerWin = true; //Gana el jugador
				}
				else if (checking == "X")
				{ //Es string del agente
					agentWin = true; //Gana el agente
					running = false; //Termina el while
				}
			}
		}
	}

	//Diagonal 1, posición [0][0]
	if (gameBoard[0][0] == "O" || gameBoard[0][0] == "X")
	{ //Checa las diagonales de izquierda a derecha
		checking = gameBoard[0][0];
		if (gameBoard[1][1] == checking && gameBoard[2][2] == checking) { //checa las diagonales de [1][1] y [2][2]
			if (checking == "O")
			{ //Checa si son símbolos del jugador
				playerWin = true; //Gana el jugador
				running = false; //Rompe el while
			}
			else if (checking == "X")
			{ //Checa si es tirada del agente
				agentWin = true; //Gana el agente, rompe el while
				running = false; //
			}
		}
	}

	//Diagonal 2, posición [2][2]
	if (gameBoard[0][2] == "O" || gameBoard[0][2] == "X")
	{ //checa de derecha a izquierda en la diagonal principal
		checking = gameBoard[0][2];
		if (gameBoard[1][1] == checking && gameBoard[2][0] == checking)
		{ //Si la diagonal de la derecha a la izquierda tiene el mismo string
			if (checking == "O")
			{ //Pregunta si es símbolo del jugador
				playerWin = true; //Gana el jugador
				running = false; //Termina el while
			}
			else if (checking == "X")
			{ //Pregunta si es símbolo del jugador
				agentWin = true;
				running = false;
			}
		}
	}
}

/*Es el turno del agente, checa qué cambios hay en el tablero y a partir de ahí revisa qué cambios hubo.*/
void TicTacToe::AgentTurn() {
	try {
		for(int i = 0; i < lines; i++) { //Guardar los elementos desocupados del tablero dentro del grafo
			for(int j = 0; j < columns; j++) { //Insertar jugada del agente aquí y checar sus hijos
				if(gameBoard[i][j] != "O" && gameBoard[i][j] != "X") {
					posibilidades->InsertaNodo(new NodoG<string>(gameBoard[i][j], j, i)); //Añadir el nodo al grafo
				}
			} cout << endl;
		} 
		posibilidades->PrintPath(posibilidades->GetAllNodes()); //Imprimir los nodos disponibles
		NodoT<NodoG<string>*>* iterador = posibilidades->GetAllNodes().first;
		for (int i = 0; i < lines; i++) {
			for (int j = 0; j < columns; j++) {
				if (i == iterador->value->y && j == iterador->value->x) {
					checkAdjacent(i, j, iterador->value);
				}
			}
		}

		//for(int i = 0; i < lines; i++) {
		//	for(int j = 0; j < columns; j++) {
		//		if(posicion == nodo->value->nodoData) {
		//			cout << "Visitando la posicion: " << i << ", " << j << endl;
		//			if(j - 1 != -1) {
		//				cout << "Tengo alguien detras!\n";
		//			}
		//			if(j + 1 != columns) {
		//				cout << "Tengo alguien en frente!\n";
		//				//checarHijos(i, j + 1);
		//			}
		//			if(i - 1 != -1) {
		//				cout << "Tengo alguien arriba!\n";
		//			}
		//			if(i + 1 != lines) {
		//				cout << "Tengo alguien debajo!\n";
		//				//checarHijos(i, j + 1);
		//			}
		//			nodo = nodo->next;
		//		}
		//		cout << endl;
		//		posicion++;
		//	}
		//}
		
	} catch(...) {
		cout << "Algo esta mal!\n";
	}

}

/*Checa las casillas adyacentes a la casilla actual y a sus vecinos posibles
 *@param[int y] posición dentro de una matriz en las líneas
 *@param[int x] posición dentro de una matriz en las columnas
 *@param[NodoG<string>* posibilidad] el nodo que tiene una posibilidad para establecer la jugada del agente */
void TicTacToe::checkAdjacent(int y, int x, NodoG<string>* posibilidad)
{
	try {
		if (x + 1 <  columns) { //Analizar la posición de en frente de la casilla actual
			if (gameBoard[y][x + 1] == "X"|| gameBoard[y][x + 1] == "_") { //Pregunta si la casilla frontal tiene jugada del agente o está vacía
				posibilidad->cost += 10; //Aumenta el coste del nodo en 10
			} else if (gameBoard[y][x + 1] == "O") { //Si la casilla de enfrente tiene símbolo del jugador, reduce el costo del nodo
				posibilidad->cost -= 10;
			}
		}
		if (x - 1 >= 0) {
			if (gameBoard[y][x - 1] == "X" || gameBoard[y][x - 1] == "_") { //Pregunta si la casilla trasera tiene jugada del agente o está vacía
				posibilidad->cost += 10;
			} else if (gameBoard[y][x - 1] == "O") {
				posibilidad->cost -= 10;
			}

		}if (y + 1 < lines) {
			if (gameBoard[y + 1][x] == "X" || gameBoard[y + 1][x] == "_") { //Pregunta si la casilla de arriba tiene jugada del agente o está vacía
				posibilidad->cost += 10;
			} else if (gameBoard[y + 1][x] == "O") {
				posibilidad->cost -= 10;
			}
		}
		if (y - 1 >= 0) {
			if (gameBoard[y - 1][x] == "X" || gameBoard[y - 1][x] == "_") { //Pregunta si la casilla de abajo tiene jugada del agente o está vacía
				posibilidad->cost += 10;
			} else if (gameBoard[y - 1][x] == "O") {
				posibilidad->cost -= 10;
			}
		}
	} catch (...) {
		cout << "Algo salio mal!\n";
	}
}

void TicTacToe::checarHijos(int x, int y) 	{
	try {
		if(gameBoard[x][y] != "X" || gameBoard[x][y] == "_") {
			if(y + 1 != NULL)
				checarHijos(x, y + 1);
		}
	} catch(...) {	
		cout << "Algo esta mal!\n";
	}
}

TicTacToe::TicTacToe() {
}

TicTacToe::~TicTacToe() {
}
