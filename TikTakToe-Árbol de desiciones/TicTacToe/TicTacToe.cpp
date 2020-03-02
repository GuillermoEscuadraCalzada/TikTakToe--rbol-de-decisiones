#include "TicTacToe.h"
TicTacToe* TicTacToe::ptr = nullptr;

/*Se imprimen los lugares vaci�s dentro del arreglo de dos dimensiones donde suceder� el juego*/
void TicTacToe::SetUp() {
	try {
		/*Determinar qu� se va a imprimir dentro de las casillas que tendr� el gameBoard*/
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
		for(int i = 0; i < lines; i++) {
			for(int j = 0; j < columns; j++) {
				cout << "| " << gameBoard[i][j] << " ";
			}
			cout << "|" << endl;
		}
	} catch(exception & e) {
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}

/*La clase ser� singleton, por lo que el constructor y destructor no se pueden conseguir de manera p�blica*/
TicTacToe* TicTacToe::GetPtr() {
	if(!ptr) //Si el apuntador es nulo, crea uno nuevo
		ptr = new TicTacToe();
	return ptr; //regresa el apuntador
}

/*Funci�n que mandar� a llamar las primer funciones del juego de TicTacToe*/
void TicTacToe::Init() {
	try {
		running = true;
		SetUp();
		printBoard();
	} catch(exception & e) {
		cout << "EXCEPTION CAUGHT: " << e.what() << endl;
	}
}

/*Actualizac�on constante del juego*/
void TicTacToe::Update() {
	while(running) {
		PlayerInput();
		printBoard();
	}
}

/*Detecta la posici�n en la que el jugador decide poner su s�mbolo*/
void TicTacToe::PlayerInput() {
	try {
		cout << "Elige la fila donde se ubicara tu simboolo: ";
		cin >> x;  //Elemento en el eje X o en las l�neas del gameBoard
		if(cin.fail() || x > columns - 1 || x < 0) 
			throw(x);
		
		cout << "\nElige la columna donde se ubicar� tu simbolo: ";
		cin >> y; //Elemento en el eje Y o en las columnas del gameBoard
		if(cin.fail() || y > lines - 1 || y < 0) //El input fue uno no permitido o se pas� del n�mero de l�neas
			throw(x);

		if(gameBoard[x][y] == "O"|| gameBoard[x][y] ==  "X")
			cout << "Esa posiciO	n ya fue elegida.\n";
		else {
			setNewBoard(x, y);
		}
		cout << endl;


	} catch(int x) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "You entered a wrong input" << endl;
		//if(cin.fail()) {
		//	cin.clear();
		//	cin.ignore(numeric_limits<streamsize>::max(), '\n');
		//	cout << "You have entered wrong input" << endl;
		//}
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




TicTacToe::TicTacToe() {
}

TicTacToe::~TicTacToe() {
}
