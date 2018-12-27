// Minesweeper.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "game.h"
#include "component.h"
#include "cell.h"
#include "field.h"
#include "standartGame.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	system("mode con cols=100 lines=40");
	game & game = standartGame();
	game.introduction();
	return 0;
}
