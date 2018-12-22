#include "stdafx.h"
#include "component.h"
#include "cell.h"
#include "field.h"
#include "advancedFunctions.h"

using namespace std;

void gameLogic::introduction()
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)(0 | 2));
	cout << endl << "Приветствуем тебя в игре 'Сапер'!" << endl << endl;
	SetConsoleTextAttribute(hStdOut, (WORD)(0 | 15));
	string com;
	cout << "Нажми на 'h' для вызова справки по игре, 's' для начала игры" << endl;
	cout << "или 'l' для загрузки сохраненной игры: ";
	cin >> com;
	while (com != "h" && com != "s" && com != "l")
	{
		cout << "Неверный ввод. Введите снова: ";
		cin >> com;
	}
	cout << endl;
	if (com == "h")
	{
		SetConsoleTextAttribute(hStdOut, (WORD)(0 | 2));
		cout << "Поле возможно задавать размером size от 2 до 26 включительно." << endl;
		cout << "Количество мин также может быть от 1 до размера (size * size - 1) включительно." << endl;
		cout << "Ячейки поля могут быть 4 видов:" << endl;
		cout << " * - ячейка закрыта;" << endl;
		cout << " 0..8 - количество бомб вокруг данной ячейки;" << endl;
		cout << " + - ячейка помечена;" << endl;
		cout << " " << char(164) << " - в данной ячейке расположена бомба." << endl;
		SetConsoleTextAttribute(hStdOut, (WORD)(0 | 15));
		cout << endl;
		cout << "Удачной игры!" << endl;
		system("pause");
		system("cls");
		startGame();
	}
	else if (com == "s")
	{
		system("cls");
		startGame();
	}
	else if (com == "l")
	{
		system("cls");
		cout << "Доступные сохранения:" << endl;
		ifstream fin("saves.txt");
		string buf;
		unsigned int saveNum = 1;
		while (fin.peek() != EOF)
		{
			getline(fin, buf);
			unsigned int size = buf.length();
			for (unsigned int i = 0; i < size; i++)
			{
				if (buf[i] == '|')
				{
					buf.erase(i, size - 1 - i);
					break;
				}
			}
			cout << saveNum << ". " << buf << endl;
			saveNum++;
		}
		fin.close();
		if (saveNum == 1)
		{
			cout << endl << "Нет доступных сохранений." << endl;
			system("pause");
			system("cls");
			startGame();
		}
		else
		{
			string save;
			cout << endl << "Введите номер сохранения: ";
			cin >> save;
			while (save < "1" || save >= to_string(saveNum))
			{
				cout << "Неверный номер сохранения. Введите заново: ";
				cin >> save;
			}
			fstream fstr("saves.txt");
			string curSave;
			unsigned int curLine = 1;
			while (getline(fstr, curSave)) // ищем подходящую строку в файле по номеру
			{
				if (curLine == atoi(save.c_str()))
				{
					break;
				}
				curLine++;
			}
			fstr.close();
			unsigned int size = 0;
			unsigned int bombsCount = 0;
			string states = "";
			unsigned int * bombs;
			unsigned int lineSize = curSave.length();
			for (int i = 0; i < lineSize; i++) // удаляем информацию о дате сохранения
			{
				if (curSave[i] == '|')
				{
					curSave.erase(0, i + 2);
					break;
				}
			}
			lineSize = curSave.length();
			unsigned int i = 0;
			while (curSave[i] != '|')
			{
				if (curSave[i] != ' ')
				{
					size++;
					states += curSave[i];
				}
				i++;
			}
			size = (unsigned int)sqrt(size);
			curSave.erase(0, i + 1);
			bombs = new unsigned int[2 * (size * size - 1)];
			curSave = decryption(curSave);
			lineSize = curSave.length();
			for (int i = 0; i < lineSize; i++) // ищем кол-во бомб и их расположение
			{
				if (curSave[i] != ' ' && curSave[i - 1] == ' ' && curSave[i + 1] == ' ')
				{
					bombs[bombsCount] = curSave[i] - 48;
					bombsCount++;
				}
				else if (curSave[i] != ' ' && curSave[i + 1] != ' ')
				{
					bombs[bombsCount] = 10 * (curSave[i] - 48) + curSave[i + 1] - 48;
					bombsCount++;
				}
			}
			bombsCount /= 2;
			field * fiel = new field(size, bombsCount, states, bombs);
			if (fiel) gameLogic::currentTurn(fiel);
		}
	}
}

void gameLogic::startGame()
{
	string size;
	string minesCount;
	cout << endl << "Введите размер поля: ";
	cin >> size;
	while (!(ifStringIsInt(size) && atoi(size.c_str()) > 1 && atoi(size.c_str()) < 27))
	{
		cout << "Неверный размер поля. Введите снова: ";
		cin >> size;
	}
	int intSize = atoi(size.c_str());
	cout << "Введите число мин: ";
	cin >> minesCount;
	while (!(ifStringIsInt(minesCount) && atoi(minesCount.c_str()) > 0 && atoi(minesCount.c_str()) <= (intSize * intSize - 1)))
	{
		cout << "Неверное число мин. Введите снова: ";
		cin >> minesCount;
	}
	field * f = new field(atoi(size.c_str()), atoi(minesCount.c_str()));
	f->plantBombs();
	gameLogic::currentTurn(f);
}

void gameLogic::currentTurn(field * f)
{
	system("cls");
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)(0 | 2));
	cout << endl << "Всего бомб на поле: " << f->returnBombsCount() << endl;
	cout << "Число оставшихся бомб: " << f->returnBombsCount() - gameLogic::markedCellsCount(f) << endl << endl;
	SetConsoleTextAttribute(hStdOut, (WORD)(0 | 15));
	component * comp = f;
	comp->draw();
	string com;
	cout << endl;
	cout << "Доступные действия:" << endl;
	cout << "0 - пометить ячейку поля;" << endl;
	cout << "1 - открыть ячейку поля;" << endl;
	cout << "2 - сохранить игру;" << endl;
	cout << "3 - загрузить сохраненную игру;" << endl;
	cout << "4 - завершить игру." << endl << endl;
	cout << "Введите номер действия: ";
	cin >> com;
	while (!(ifStringIsInt(com) && (atoi(com.c_str()) >= 0 && atoi(com.c_str()) <= 4)))
	{
		cout << "Неверный номер действия. Введите снова: ";
		cin >> com;
	}
	int curCom = atoi(com.c_str());
	switch (curCom)
	{
	case 0:
	{
		string cell = gameLogic::suitableCell(f);
		unsigned int j = cell[0] - 65;
		unsigned int i = atoi(cell.erase(0, 1).c_str());
		gameLogic::markCell(f, i, j);
		break;
	}
	case 1:
	{
		string cell = gameLogic::suitableCell(f);
		unsigned int j = cell[0] - 65;
		unsigned int i = atoi(cell.erase(0, 1).c_str());
		gameLogic::openCell(f, i, j);
		break;
	}
	case 2:
	{
		gameLogic::saveGame(f);
		gameLogic::ifContinue(f);
		break;
	}
	case 3:
	{
		gameLogic::loadOrDeleteSavedGame(f);
		break;
	}
	case 4:
	{
		f->~field();
		cout << "Завершение игры..." << endl;
		system("pause");
		break;
	}
	}
}

string gameLogic::suitableCell(field *f)
{
	string cell;
	cout << "Введите номер ячейки поля в формате [номерCтолбца номерCтроки], например A0: ";
	cin >> cell;
	string bufCell = cell;
	unsigned int bufJ = bufCell[0] - 65;
	unsigned int bufI = atoi(bufCell.erase(0, 1).c_str());
	while (!(gameLogic::checkCellNumber(f, cell) && f->returnState(bufI, bufJ) != 2))
	{
		cout << "Номер ячейки не верен. Введите снова: ";
		cin >> cell;
		bufCell = cell;
		bufJ = bufCell[0] - 65;
		bufI = atoi(bufCell.erase(0, 1).c_str());
	}
	return cell;
}

void gameLogic::markCell(field *f, unsigned int i, unsigned int j)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	f->changeState(i, j, 1);
	if (f->ifVictory())
	{
		system("cls");
		cout << endl;
		component * comp = f;
		comp->draw();
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, (WORD)(0 | 2));
		cout << endl << "Вы выиграли!" << endl << endl;
		SetConsoleTextAttribute(hStdOut, (WORD)(0 | 15));
		startNewGame(f);
	}
	else
	{
		gameLogic::currentTurn(f);
	}
}

void gameLogic::openCell(field *f, unsigned int i, unsigned int j)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (f->ifCellIsBomb(i, j))
	{
		unsigned int size = f->returnSize();
		for (unsigned int i = 0; i < size; i++)
		{
			for (unsigned int j = 0; j < size; j++)
			{
				if (f->ifCellIsBomb(i, j))
				{
					f->changeState(i, j, 3);
				}
				else
				{
					f->changeState(i, j, 2);
				}
			}
		}
		system("cls");
		cout << endl;
		component * comp = f;
		comp->draw();
		SetConsoleTextAttribute(hStdOut, (WORD)(0 | 4));
		cout << endl << "Вы наткнулись на бомбу. Вы проиграли!" << endl << endl;
		SetConsoleTextAttribute(hStdOut, (WORD)(0 | 15));
		startNewGame(f);
	}
	else
	{
		f->changeState(i, j, 2);
		if (f->minesCountAroundCell(i, j) == 0) gameLogic::openCellsAroundZeroCell(i, j, f);
		if (f->ifVictory())
		{
			system("cls");
			cout << endl;
			component * comp = f;
			comp->draw();
			SetConsoleTextAttribute(hStdOut, (WORD)(0 | 2));
			cout << endl << "Вы выиграли!" << endl << endl;
			SetConsoleTextAttribute(hStdOut, (WORD)(0 | 15));
			startNewGame(f);
		}
		else
		{
			currentTurn(f);
		}
	}
}

void gameLogic::saveGame(field *f)
{
	ofstream fout;
	fout.open("saves.txt", ios_base::app);
	char buffer[30];
	time_t seconds = time(0);
	tm timeinfo;
	localtime_s(&timeinfo, &seconds);
	char* format = "%d %B %Y %H:%M:%S";
	strftime(buffer, 80, format, &timeinfo);
	fout << buffer << " | "; // сохраняем в файл дату сохранения
	unsigned int size = f->returnSize();
	for (unsigned int i = 0; i < size; i++)
	{
		for (unsigned int j = 0; j < size; j++)
		{
			fout << f->returnState(i, j) << " "; // сохраняем в файл все состояния ячеек
		}
	}
	fout << "|";
	unsigned int * bombsBuf = new unsigned int[f->returnBombsCount()];
	unsigned int count = 0;
	for (unsigned int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (f->ifCellIsBomb(i, j))
			{
				bombsBuf[count] = i;
				count++;
				bombsBuf[count] = j;
				count++;
			}
		}
	}
	fout << gameLogic::encryption(bombsBuf, f); // сохраняем в файл зашифрованные позиции бомб
	fout << endl;
	fout.close();
	cout << "Игра успешно сохранена." << endl;
}

void gameLogic::loadOrDeleteSavedGame(field *f)
{
	system("cls");
	cout << "Доступные сохранения:" << endl;
	ifstream fin("saves.txt");
	string buf;
	unsigned int saveNum = 1;
	while (fin.peek() != EOF)
	{
		getline(fin, buf);
		unsigned int size = buf.length();
		for (unsigned int i = 0; i < size; i++)
		{
			if (buf[i] == '|')
			{
				buf.erase(i, size - 1 - i);
				break;
			}
		}
		cout << saveNum << ". " << buf << endl;
		saveNum++;
	}
	fin.close();
	if (saveNum == 1)
	{
		cout << endl << "Нет доступных сохранений." << endl;
		system("pause");
		currentTurn(f);
	}
	else
	{
		cout << endl << "Выберите действие:" << endl;
		cout << "1. Загрузить игру;" << endl;
		cout << "2. Удалить сохранение." << endl;
		cout << endl << "Номер действия: ";
		string action;
		cin >> action;
		while (action != "1" && action != "2")
		{
			cout << "Неверный номер действия. Введите заново: ";
			cin >> action;
		}
		string save;
		cout << endl << "Введите номер сохранения: ";
		cin >> save;
		while (save < "1" || save >= to_string(saveNum))
		{
			cout << "Неверный номер сохранения. Введите заново: ";
			cin >> save;
		}
		switch (atoi(action.c_str()))
		{
		case 1:
		{
			f->~field();
			fstream fstr("saves.txt");
			string curSave;
			unsigned int curLine = 1;
			while (getline(fstr, curSave)) // ищем подходящую строку в файле по номеру
			{
				if (curLine == atoi(save.c_str()))
				{
					break;
				}
				curLine++;
			}
			fstr.close();
			unsigned int size = 0;
			unsigned int bombsCount = 0;
			string states = "";
			unsigned int * bombs;
			unsigned int lineSize = curSave.length();
			for (int i = 0; i < lineSize; i++) // удаляем информацию о дате сохранения
			{
				if (curSave[i] == '|')
				{
					curSave.erase(0, i + 2);
					break;
				}
			}
			lineSize = curSave.length();
			unsigned int i = 0;
			while (curSave[i] != '|')
			{
				if (curSave[i] != ' ')
				{
					size++;
					states += curSave[i];
				}
				i++;
			}
			size = (unsigned int)sqrt(size);
			curSave.erase(0, i + 1);
			bombs = new unsigned int[2 * (size * size - 1)];
			curSave = decryption(curSave);
			lineSize = curSave.length();
			for (int i = 0; i < lineSize; i++) // ищем кол-во бомб и их расположение
			{
				if (curSave[i] != ' ' && curSave[i - 1] == ' ' && curSave[i + 1] == ' ')
				{
					bombs[bombsCount] = curSave[i] - 48;
					bombsCount++;
				}
				else if (curSave[i] != ' ' && curSave[i + 1] != ' ')
				{
					bombs[bombsCount] = 10 * (curSave[i] - 48) + curSave[i + 1] - 48;
					bombsCount++;
				}
			}
			bombsCount /= 2;
			field * fiel = new field(size, bombsCount, states, bombs);
			if (fiel) currentTurn(fiel);
			break;
		}
		case 2:
		{
			fstream fstr("saves.txt");
			string buf = "";
			while (fstr.peek() != EOF)
			{
				buf += fstr.get();
			}
			unsigned int size = buf.size();
			unsigned int count = 1;
			unsigned int lastEndLine = 0;
			for (unsigned int i = 0; i < size; i++)
			{
				if (buf[i] == '\n')
				{
					if (count == atoi(save.c_str()))
					{
						buf.replace(lastEndLine, i - lastEndLine, "");
						if (count == 1) buf.erase(0, 1);
						break;
					}
					lastEndLine = i;
					count++;
				}
			}
			fstr.close();
			fstr.open("saves.txt", ios::out);
			fstr << buf;
			fstr.close();
			cout << "Сохранение успешно удалено." << endl;
			gameLogic::ifContinue(f);
			break;
		}
		}
	}
}
string gameLogic::encryption(unsigned int * bombs, field *f)
{

	unsigned int minesCount = f->returnBombsCount();
	unsigned int num = 11;
	for (unsigned int k = 0; k < minesCount; k++)
	{
		bombs[2 * k] *= (num - 1);
		bombs[2 * k] += num - 3;
		num = changeNum(num);
		bombs[2 * k + 1] *= (num - 2);
		bombs[2 * k + 1] += num - 5;
		num = changeNum(num);
	}
	string str = "";
	for (unsigned int k = 0; k < minesCount; k++)
	{
		str += " " + to_string(bombs[2 * k]);
		str += " " + to_string(bombs[2 * k + 1]);
	}
	str += " ";
	return str;
}

string gameLogic::decryption(string str)
{
	str += " ";
	string newStr = " ";
	unsigned int num = 11;
	unsigned int size = str.length();
	string bufNum;
	unsigned int state = 0;
	for (unsigned int i = 0; i < size; i++)
	{
		if (str[i] != ' ' && str[i - 1] == ' ' && str[i + 1] == ' ')
		{
			bufNum = str[i];
			if (state == 0)
			{
				newStr += to_string((atoi(bufNum.c_str()) - num + 3) / (num - 1)) + " ";
				state = 1;
			}
			else
			{
				newStr += to_string((atoi(bufNum.c_str()) - num + 5) / (num - 2)) + " ";
				state = 0;
			}
			num = changeNum(num);
		}
		else if (str[i] != ' ' && str[i - 1] == ' ' && str[i + 1] != ' ' && str[i + 2] == ' ')
		{
			bufNum = str[i];
			bufNum += str[i + 1];
			if (state == 0)
			{
				newStr += to_string((atoi(bufNum.c_str()) - num + 3) / (num - 1)) + " ";
				state = 1;
			}
			else
			{
				newStr += to_string((atoi(bufNum.c_str()) - num + 5) / (num - 2)) + " ";
				state = 0;
			}
			num = changeNum(num);
		}
		else if (str[i] != ' ' && str[i + 1] != ' ' && str[i + 2] != ' ')
		{
			bufNum = str[i];
			bufNum += str[i + 1];
			bufNum += str[i + 2];
			if (state == 0)
			{
				newStr += to_string((atoi(bufNum.c_str()) - num + 3) / (num - 1)) + " ";
				state = 1;
			}
			else
			{
				newStr += to_string((atoi(bufNum.c_str()) - num + 5) / (num - 2)) + " ";
				state = 0;
			}
			num = changeNum(num);
		}
	}
	return newStr;
}

unsigned int gameLogic::changeNum(unsigned int num)
{
	if (num == 11) num = 17;
	else if (num == 17) num = 19;
	else if (num == 19) num = 23;
	else if (num == 23) num = 29;
	else if (num == 29) num = 31;
	else if (num == 31) num = 37;
	else if (num == 37) num = 11;
	return num;
}

bool gameLogic::ifStringIsInt(string str)
{
	int curInt = atoi(str.c_str());
	int length = 0;
	while (curInt)
	{
		curInt /= 10;
		length++;
	}
	return (str.length() == length || str == "0") ? true : false;
}

bool gameLogic::checkCellNumber(field * f, string cell)
{
	unsigned int size = f->returnSize();
	char letter = cell[0];
	unsigned int number = atoi(cell.erase(0,1).c_str());
	return (letter >= 65 && letter < 65 + size && number < size) ? true : false;
}

void gameLogic::startNewGame(field *f)
{
	string newGame;
	cout << "Начать новую игру (Y - да, N - нет)? ";
	cin >> newGame;
	while (newGame != "Y" && newGame != "N")
	{
		cout << "Неверный ввод. Введите снова: ";
		cin >> newGame;
	}
	if (newGame == "Y")
	{
		system("cls");
		startGame();
	}
	else
	{
		f->~field();
		cout << "Завершение игры..." << endl;
		system("pause");
	}
}

void gameLogic::ifContinue(field *f)
{
	string cont;
	cout << "Желаете продолжить (Y - да, N - нет)? ";
	cin >> cont;
	while (cont != "Y" && cont != "N")
	{
		cout << "Неверный ввод. Введите снова: ";
		cin >> cont;
	}
	if (cont == "Y")
	{
		system("cls");
		currentTurn(f);
	}
	else
	{
		f->~field();
		cout << "Завершение игры..." << endl;
		system("pause");
	}
}

void gameLogic::openCellsAroundZeroCell(unsigned int x, unsigned int y, field * f)
{
	unsigned int size = f->returnSize();
	if (x > 0 && f->returnState(x - 1, y) != 2)
	{
		f->changeState(x - 1, y, 2);
		if (f->minesCountAroundCell(x - 1, y) == 0) openCellsAroundZeroCell(x - 1, y, f);
	}
	if (y < size - 1 && f->returnState(x, y + 1) != 2)
	{
		f->changeState(x, y + 1, 2);
		if (f->minesCountAroundCell(x, y + 1) == 0) openCellsAroundZeroCell(x, y + 1, f);
	}
	if (x < size - 1 && f->returnState(x + 1, y) != 2)
	{
		f->changeState(x + 1, y, 2);
		if (f->minesCountAroundCell(x + 1, y) == 0) openCellsAroundZeroCell(x + 1, y, f);
	}
	if (y > 0 && f->returnState(x, y - 1) != 2)
	{
		f->changeState(x, y - 1, 2);
		if (f->minesCountAroundCell(x, y - 1) == 0) openCellsAroundZeroCell(x, y - 1, f);
	}
}

unsigned int gameLogic::markedCellsCount(field * f)
{
	int count = 0;
	unsigned int size = f->returnSize();
	for (unsigned int i = 0; i < size; i++)
	{
		for (unsigned int j = 0; j < size; j++)
		{
			if (f->returnState(i, j) == 1) count++;
		}
	}
	return (count > f->returnBombsCount()) ? f->returnBombsCount() : count;
}