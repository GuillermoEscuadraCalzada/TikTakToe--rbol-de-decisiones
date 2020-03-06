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
	string gameBoard[lines][columns]; //El tablero representado como matriz de 2x2
	void SetUp();
	void printBoard();
	void AgentTurn();
	void checarHijos(int x, int y);
	bool running, playerWin, agentWin;
	static TicTacToe* ptr;
	Grafo<int>* posibilidades;
	TicTacToe();
	~TicTacToe();
};


#endif // !TICTACTOE_H

