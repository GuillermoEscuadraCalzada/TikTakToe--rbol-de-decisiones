#include "TicTacToe.h"
TicTacToe* TicTacToe::ptr = nullptr;

/*Se imprimen los lugares vaciós dentro del arreglo de dos dimensiones donde sucederá el juego*/
void TicTacToe::SetUp() {
	try {
		gameBoard = new string * [lines]; //Genera la primer dimensión para el arreglo de strings
		/*Determinar qué se va a imprimir dentro de las casillas que tendrá el gameBoard*/
		for(int i = 0; i < lines; i++) {
			gameBoard[i] = new string[columns]; //Crea la segunda dimensión del arreglo de strings
			for(int j = 0; j < columns; j++) {
				gameBoard[i][j] = "_"; //El elemento en esta matriz se iguala a "_" simulando un espacio vacío
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
		PlayerInput(); //Turno del jugador
		printBoard(); //Imprime la tabla
		//CheckWin();
		if(agentWin || playerWin)
			break;
		AgentTurn(); //Turno del agente
		/*copyBoard(); */
		//CheckWin();
		if(agentWin || playerWin)
			break;
		printBoard(); //Imprime la tabla
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
			setNewBoard(x, y); //Cambia el tablero actual
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
	try 
	{
		MinMax(GenerateCopy(gameBoard));
	} catch(...) {
		cout << "Algo esta mal!\n";
	}

}

/*Busca un valor vacío dentro del arreglo de strings del parámetro, si está ocupado por el símbolo del agente o del jugador, lo salta
 *@param[string** g] el tablero en el cual se va a buscar un string.
 *@return regresa un vector de 2 dimensiones*/
Vector2* TicTacToe::MinMax(string** g)
{
	for (int i = 0; i < lines; i++)
	{ //Itera en la primer dimensión del arreglo
		for (int j = 0; j < columns; j++)
		{ //Itera en la segunda dimensión del arreglo
			if (g[i][j] != "O" && g[i][j] != "X")
			{ //Pregunta si el string en esta posición no ha sido ocupado por el jugador o del agente 
				MinMaxR(i, j, 1, g); //Manda a llamar la función recursiva del juego 
			}
		}
	}
	return nullptr;
}

/*Pregunta si ya hay un estado terminal
 *@return regresa verdadero en caso de ser terminal y falso en caso de no serlo*/
bool TicTacToe::Terminal()
{
	return false;
}


/*Se realiza la búsqueda recursiva para saber si la posición actual es adecuada para que el agente realice su tirada ahí mismo.
 *@param[int i] la posición en la primer dimensión [i][j]
 *@param[int j] la posición en la segunda dimensión [i][j]
 *@param[int turn] el turno del que esté tirando, puede ser del jugador (2) o del agente (1)
 *@return regresa el número de la jugada (1 aceptable o -1 inaceptable) */
int TicTacToe::MinMaxR(int i, int j, int turn, string** cp)
{
	int value = 0;
	string** copy = GenerateCopy(cp); //Genera la copia del tablero de juego
	if (turn == 1)
	{ //El turno es del agente
		copy[i][j] = "X"; //En la copia imprime una X en estas posiciones
	}
	else
	{ //El turno es del jugador
		copy[i][j] = "O"; //En la copia imprime una O en estas posiciones
	}
	
	if (!Terminal(/*copy*/))
	{ //Si no ha sido un estado terminal
		for (int i = 0; i < lines; i++)
		{ //Itera por la primera dimensión del arreglo
			for (int j = 0; j < columns; j++) 
			{ //Itera por la segunda dimensión del arreglo
				if (copy[i][j] != "O" && copy[i][j] != "X")
				{ //Pregunta si es un espacio vacío 
					if (turn == 1)
					{ //Si es turno del agente
						value += MinMaxR(i, j, 2, copy); //Recursividad con el turno del jugador y suma el resultador
					}
					else
					{
						value += MinMaxR(i, j, 1, copy); //Recursividad con el turno del agente y suma el resultado
					}
				}
			}
		}
		return value;
	}
	else
	{ //Es un estado terminal
		if (turn == 1)
		{  //Es turno del agente
			return 1; //Regresa 1
		}
		else if (turn == 2)
		{ //Es turno del jugador
			return -1; //Regresa -1
		}
	}
}


string** TicTacToe::GenerateCopy(string** c)
{
	string** copy = new string * [lines];
	for (int i = 0; i < 3; i++)
	{
		copy[i] = new string[columns];
		for (int j = 0; j < 3; j++)
		{
			copy[i][j] = gameBoard[i][j];
		}
	}
	return copy;
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
