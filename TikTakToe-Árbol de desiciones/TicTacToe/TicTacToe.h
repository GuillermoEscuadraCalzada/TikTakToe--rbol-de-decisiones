#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <iostream>
#include <string>
using std::to_string;
using namespace std;
class TicTacToe {
protected:
	const static int columns = 3;
	const static int lines = 3;
public:
	int x, y;
	string gameBoard[lines][columns]; //El tablero representado como matriz de 2x2
	void SetUp();
	void printBoard();
	static TicTacToe* GetPtr();
	void Init();
	void Update();
	void PlayerInput();
	void setNewBoard(int x, int y);
	void CheckWin();
private:
	bool running;
	bool win;
	static TicTacToe* ptr;
	TicTacToe();
	~TicTacToe();
};


#endif // !TICTACTOE_H

