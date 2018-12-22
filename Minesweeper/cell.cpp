#include "stdafx.h"
#include "component.h"
#include "cell.h"
#include "field.h"

using namespace std;

void cell::setIfBomb(bool ifCellIsBomb)
{
	ifBomb = ifCellIsBomb;
}

void cell::setState(unsigned int cellState)
{
	state = cellState;
}