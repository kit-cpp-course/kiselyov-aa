#pragma once

/*
 /* класс поля для игры
 */
class field : public component
{
	/*
	 /* размер поля (длина и ширина)
	 */
	unsigned int size;

	/*
	 /* количество мин на поле
	 */
	unsigned int minesCount;

	/*
	 /* массив ячеек поля, являющихся бомбами или не бомбами
	 */
	cell ** cells;

	/*
	 /* массив состояний ячеек поля
	 /* значение: 0 - ячейка скрыта, 1 - ячейка помечена, 2 - ячейка открыта, но не является бомбой,
	 /* 3 - ячейка открыта и является бомбой
	 */
	//unsigned int ** states;

public:
	/*
	 /* конструктор класса для создания новой игры
	 */
	field(unsigned int size, unsigned int minesCount);

	/*
	 /* конструктор класса для загрузки сохраненной игры
	 */
	field(unsigned int size, unsigned int bombsCount, std::string states, unsigned int * bombs);

	/*
	 /* расположение бомб на поле до начала игры
	 */
	void plantBombs();

	/*
	 /* количество бомб вокруг данной ячейки
	 /* return количество бомб вокруг данной ячейки
	 */
	unsigned int minesCountAroundCell(unsigned int i, unsigned int j);

	/*
	 /* возвращает текущий размер поля
	 */
	unsigned int returnSize();

	/*
	 /* возвращает число бомб
	 */
	unsigned int returnBombsCount();

	/*
	 /* возвращает bool, является ли ячейка бомбой или нет
	 */
	bool ifCellIsBomb(unsigned int i, unsigned int j);

	/*
	 /* меняет состояние у ячейки str на номер stateNumber
	 */
	void changeState(unsigned int i, unsigned int j, int stateNumber);

	/*
	 /* возвращает текущее состояние ячейки
	 */
	unsigned int returnState(unsigned int i, unsigned int j);

	/*
	 /* проверяет, завершилась ли игра победой
	 */
	bool ifVictory();

	/*
	 /* вывод текущего состояния поля на экран
	 */
	void draw();

	/*
	 /* деструктор класса
	 */
	~field();
};