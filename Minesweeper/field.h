#pragma once

/*
 / класс пол€ дл€ игры
 */
class field
{
	/*
	 / размер пол€ (длина и ширина)
	 */
	unsigned int size;

	/*
	 / количество мин на поле
	 */
	unsigned int minesCount;

	/*
	 / массив €чеек пол€, €вл€ющихс€ бомбами или не бомбами
	 */
	bool ** ifBomb;

	/*
	 / массив состо€ний €чеек пол€
	 / значение: 0 - €чейка скрыта, 1 - €чейка помечена, 2 - €чейка открыта, но не €вл€етс€ бомбой,
	 / 3 - €чейка открыта и €вл€етс€ бомбой
	 */
	unsigned int ** states;

public:
	/*
	 / конструктор класса дл€ создани€ новой игры
	 */
	field(unsigned int size, unsigned int minesCount);

	/*
	 / конструктор класса дл€ загрузки сохраненной игры
	 */
	field(unsigned int size, unsigned int bombsCount, std::string states, unsigned int * bombs);

	/*
	/ расположение бомб на поле до начала игры
	*/
	void plantBombs();

	/*
	/ количество бомб вокруг данной €чейки
	/ return количество бомб вокруг данной €чейки
	*/
	unsigned int minesCountAroundCell(unsigned int i, unsigned int j);

	/*
	 / возвращает текущий размер пол€
	 */
	unsigned int returnSize();

	/*
	 / возвращает число бомб
	 */
	unsigned int returnBombsCount();

	/*
	 / возвращает bool, €вл€етс€ ли €чейка бомбой или нет
	 */
	bool ifCellIsBomb(unsigned int i, unsigned int j);

	/*
	 / мен€ет состо€ние у €чейки str на номер stateNumber
	 */
	void changeState(unsigned int i, unsigned int j, int stateNumber);

	/*
	 / возвращает текущее состо€ние €чейки
	 */
	unsigned int returnState(unsigned int i, unsigned int j);

	/*
	 / провер€ет, завершилась ли игра победой
	 */
	bool ifVictory();

	/*
	 / вывод текущего состо€ни€ пол€ на экран
	 */
	void draw();

	/*
	 / деструктор класса
	 */
	~field();
};