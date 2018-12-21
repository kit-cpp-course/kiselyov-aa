#include "stdafx.h"
#include "field.h"

using namespace std;

field::field(unsigned int size, unsigned int mines) : size(size), minesCount(mines)
{
	ifBomb = new bool *[size];
	states = new unsigned int *[size];
	for (int i = 0; i < size; i++)
	{
		ifBomb[i] = new bool[size];
		states[i] = new unsigned int[size];
		for (int j = 0; j < size; j++)
		{
			ifBomb[i][j] = false;
			states[i][j] = 0;
		}
	}
}

field::field(unsigned int size, unsigned int bombsCount, string state, unsigned int * bombs) : size(size) , minesCount(bombsCount)
{
	ifBomb = new bool *[size];
	states = new unsigned int *[size];
	for (int i = 0; i < size; i++)
	{
		ifBomb[i] = new bool[size];
		states[i] = new unsigned int[size];
		for (int j = 0; j < size; j++)
		{
			ifBomb[i][j] = false;
			states[i][j] = (int)state[size * i + j] - 48;
		}
	}
	for (unsigned int k = 0; k < bombsCount; k++)
	{
		ifBomb[bombs[2 * k]][bombs[2 * k + 1]] = true;
	}
}

unsigned int field::returnSize()
{
	return size;
}

unsigned int field::returnBombsCount()
{
	return minesCount;
}

bool field::ifCellIsBomb(unsigned int i, unsigned int j)
{
	return ifBomb[i][j];
}

void field::changeState(unsigned int i, unsigned int j, int stateNumber)
{
	states[i][j] = stateNumber;
}

unsigned int field::returnState(unsigned int i, unsigned int j)
{
	return states[i][j];
}

bool field::ifVictory()
{
	unsigned int counter = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (states[i][j] == 1 && !ifBomb[i][j]) return false;
			if (states[i][j] == 2 || states[i][j] == 1)
			{
				counter++;
			}
		}
	}
	return (counter == size * size);
}

void field::plantBombs()
{
	srand(time(0));
	for (int i = 0; i < minesCount; i++)
	{
		unsigned int currBombNum = rand() % (size * size);
		while (ifBomb[currBombNum / size][currBombNum % size])
		{
			currBombNum = rand() % (size * size);
		}
		ifBomb[currBombNum / size][currBombNum % size] = true;
	}
}

unsigned int field::minesCountAroundCell(unsigned int i, unsigned int j)
{
	int bombsAround = 0;
	if (i > 0 && j > 0 && ifBomb[i - 1][j - 1])
	{
		bombsAround++;
	}
	if (i > 0 && ifBomb[i - 1][j])
	{
		bombsAround++;
	}
	if (i > 0 && j < size - 1 && ifBomb[i - 1][j + 1])
	{
		bombsAround++;
	}
	if (j < size - 1 && ifBomb[i][j + 1])
	{
		bombsAround++;
	}
	if (i < size - 1 && j < size - 1 && ifBomb[i + 1][j + 1])
	{
		bombsAround++;
	}
	if (i < size - 1 && ifBomb[i + 1][j])
	{
		bombsAround++;
	}
	if (i < size - 1 && j > 0 && ifBomb[i + 1][j - 1])
	{
		bombsAround++;
	}
	if (j > 0 && ifBomb[i][j - 1])
	{
		bombsAround++;
	}
	return bombsAround;
}

void field::draw()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (size > 10)
	{
		cout << "   ";
	}
	else
	{
		cout << "  ";
	}
	for (unsigned int i = 0; i < size; i++)
	{
		cout << char(65 + i) << " ";
	}
	cout << endl;
	for (unsigned int i = 0; i < size; i++)
	{
		if (size > 10 && i < 10)
		{
			cout << " ";
		}
		cout << i << " ";
		for (unsigned int j = 0; j < size; j++)
		{
			switch (states[i][j])
			{
				case 0:
				{
					cout << "* ";
					break;
				}
				case 1:
				{
					SetConsoleTextAttribute(hStdOut, (WORD)(0 | 6));
					cout << char(43) << " ";
					SetConsoleTextAttribute(hStdOut, (WORD)(0 | 15));
					break;
				}
				case 2:
				{
					SetConsoleTextAttribute(hStdOut, (WORD)(0 | 2));
					cout << minesCountAroundCell(i, j) << " ";
					SetConsoleTextAttribute(hStdOut, (WORD)(0 | 15));
					break;
				}
				case 3:
				{
					SetConsoleTextAttribute(hStdOut, (WORD)(0 | 4));
					cout << char(164) << " ";
					SetConsoleTextAttribute(hStdOut, (WORD)(0 | 15));
					break;
				}
			}
		}
		cout << endl;
	}
}

field::~field()
{
	for (int i = 0; i < size; i++)
	{
		delete ifBomb[i];
		delete states[i];
	}
	delete[] ifBomb;
	delete[] states;
}