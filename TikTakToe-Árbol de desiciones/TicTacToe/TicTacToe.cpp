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
		posibilidades = new Grafo<int>();
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
		for(int i = 0; i < lines; i++) {
			if(i == x) {
				for(int j = 0; j < columns; j++) {
					if(j == y) {
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
				if (checking == "O")
				{  //Preguntar si es del jugador
					playerWin = true; //Win es igual a true
					running = false; //Termina el juego
				}
				else if (checking == "X")
				{
					agentWin = true;
					running = false;
				}
			}
		}
	}

	//Verticales
	for (int i = 0; i < lines; i++)
	{
		if (gameBoard[i][0] == "O" || gameBoard[i][0] == "X")
		{
			checking = gameBoard[i][0];
			if (gameBoard[i][1] == checking && gameBoard[i][2] == checking)
			{
				if (checking == "O")
				{
					running = false;
					playerWin = true;
				}
				else if (checking == "X")
				{
					agentWin = true;
					running = false;
				}
			}
		}
	}

	//Diagonal 1, posición [0][0]
	if (gameBoard[0][0] == "O" || gameBoard[0][0] == "X")
	{
		checking = gameBoard[0][0];
		if (gameBoard[1][1] == checking && gameBoard[2][2] == checking)
		{
			if (checking == "O")
			{
				playerWin = true;
				running = false;
			}
			else if (checking == "X")
			{
				agentWin = true;
				running = false;
			}
		}
	}

	//Diagonal 2, posición [2][2]
	if (gameBoard[0][2] == "O" || gameBoard[0][2] == "X")
	{
		checking = gameBoard[0][2];
		if (gameBoard[1][1] == checking && gameBoard[2][0] == checking)
		{
			if (checking == "O")
			{
				playerWin = true;
				running = false;
			}
			else if (checking == "X")
			{
				agentWin = true;
				running = false;
			}
		}
	}
}

/*Es el turno del agente, checa qué cambios hay en el tablero y a partir de ahí revisa qué cambios hubo.*/
void TicTacToe::AgentTurn() {
	try {
		int posicion = 0;
		for(int i = 0; i < lines; i++) {
			for(int j = 0; j < columns; j++) {
				cout << posicion << endl;
				//Insertar jugada del agente aquí y checar sus hijos
				if(gameBoard[i][j] != "O" && gameBoard[i][j] != "X") {
					//gameBoard[i][j] = "X";
					posibilidades->InsertaNodo(new NodoG<int>(posicion)); //Añadir el nodo al grafo
				}
				posicion++; //Aumentar la posición
			}
		}

		posibilidades->PrintPath(posibilidades->GetAllNodes());
	} catch(...) {
		cout << "Algo esta mal!\n";
	}

}

TicTacToe::TicTacToe() {
}

TicTacToe::~TicTacToe() {
}
