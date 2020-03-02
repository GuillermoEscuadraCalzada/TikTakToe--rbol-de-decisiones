#include <iostream>
#include "Tree/Tree.h"
#include "TicTacToe/TicTacToe.h"
int main()
{
    //Tree<int>* tree = new Tree<int>();
    //Nodo<int>* root = nullptr;
    //tree->insertValue(&root, 2);
    //tree->insertValue(&root, 3);
    //tree->insertValue(&root, 5);
    //tree->insertValue(&root, 1);
    //tree->insertValue(&root, 0);
    //tree->imprimirArbol(root, 0);
    TicTacToe* game = TicTacToe::GetPtr();
    game->SetUp();
    game->printBoard();
    //game->PlayerInput();
    game->Update();
	//Prueba

}