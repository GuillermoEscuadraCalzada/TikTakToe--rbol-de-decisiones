#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <iostream>
#include "../Tree/Grafo.h"
#include <string>


using std::to_string;
using namespace std;
class TicTacToe {
protected:
	const static int columns = 3;
	const static int lines = 3;
public:
	static TicTacToe* GetPtr();
	void Init();
	void Update();
	void CheckWin();
private:
	void PlayerInput();
	void setNewBoard(int x, int y);
	int x, y;
	string** gameBoard; //El tablero representado como matriz de 2x2
	string gameBoardCpy[lines][columns]; //El tablero representado como matriz de 2x2
	void SetUp();
	void printBoard();
	void AgentTurn();
	void checkAdjacent(int y, int x, NodoG<string>* posibilidad);
	void checarHijos(int x, int y);
	bool running, playerWin, agentWin;
	static TicTacToe* ptr;
	Grafo<string>* posibilidades;
	Vector2* MinMax(string** g);
	bool Terminal(string** g);
	string** GenerateCopy(string** c);
	int MinMaxR(int i, int j, int turn, string** copy); //1 IA, 2 es player
	TicTacToe();
	~TicTacToe();
};


#endif // !TICTACTOE_H

