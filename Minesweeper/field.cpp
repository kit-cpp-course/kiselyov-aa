#include "stdafx.h"
#include "component.h"
#include "cell.h"
#include "field.h"

using namespace std;

field::field(unsigned int size, unsigned int mines) : size(size), minesCount(mines)
{
	cells = new cell *[size];
	for (int i = 0; i < size; i++)
	{
		cells[i] = new cell[size];
	}
}

field::field(unsigned int size, unsigned int bombsCount, string state, unsigned int * bombs) : size(size) , minesCount(bombsCount)
{
	cells = new cell *[size];
	for (int i = 0; i < size; i++)
	{
		cells[i] = new cell[size];
		for (int j = 0; j < size; j++)
		{
			cells[i][j].setState((int)state[size * i + j] - 48);
		}
	}
	for (unsigned int k = 0; k < bombsCount; k++)
	{
		cells[bombs[2 * k]][bombs[2 * k + 1]].setIfBomb(true);
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
	return cells[i][j].returnIfBomb();
}

void field::changeState(unsigned int i, unsigned int j, int stateNumber)
{
	cells[i][j].setState(stateNumber);
}

unsigned int field::returnState(unsigned int i, unsigned int j)
{
	return cells[i][j].returnState();
}

bool field::ifVictory()
{
	unsigned int counter = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (cells[i][j].returnState() == 1 && !cells[i][j].returnIfBomb()) return false;
			if (cells[i][j].returnState() == 2 || cells[i][j].returnState() == 1)
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
		while (cells[currBombNum / size][currBombNum % size].returnIfBomb())
		{
			currBombNum = rand() % (size * size);
		}
		cells[currBombNum / size][currBombNum % size].setIfBomb(true);
	}
}

unsigned int field::minesCountAroundCell(unsigned int i, unsigned int j)
{
	int bombsAround = 0;
	if (i > 0 && j > 0 && cells[i - 1][j - 1].returnIfBomb())
	{
		bombsAround++;
	}
	if (i > 0 && cells[i - 1][j].returnIfBomb())
	{
		bombsAround++;
	}
	if (i > 0 && j < size - 1 && cells[i - 1][j + 1].returnIfBomb())
	{
		bombsAround++;
	}
	if (j < size - 1 && cells[i][j + 1].returnIfBomb())
	{
		bombsAround++;
	}
	if (i < size - 1 && j < size - 1 && cells[i + 1][j + 1].returnIfBomb())
	{
		bombsAround++;
	}
	if (i < size - 1 && cells[i + 1][j].returnIfBomb())
	{
		bombsAround++;
	}
	if (i < size - 1 && j > 0 && cells[i + 1][j - 1].returnIfBomb())
	{
		bombsAround++;
	}
	if (j > 0 && cells[i][j - 1].returnIfBomb())
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
			switch (cells[i][j].returnState())
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
	for (int i = 0; i < size; i++) delete cells[i];
}