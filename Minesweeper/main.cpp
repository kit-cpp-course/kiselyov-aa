// Minesweeper.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "field.h"
#include "advancedFunctions.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	system("mode con cols=100 lines=40");
	introduction();
	return 0;
}