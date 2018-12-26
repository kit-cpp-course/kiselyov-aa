#pragma once

/*
 /* класс стандартной игры Сапер
 */
class standartGame : public game
{
public:
	/*
	 /* конструктор стандартной игры
	 */
	standartGame() {};

	/*
	 /* описание правил игры
	 */
	void introduction();

	/*
	 /* описание начала игры
	 */
	void startGame();

	/*
	 /* проверка, что введенная строка является числом
	 */
	bool ifStringIsInt(std::string str);

	/*
	 /* результаты последнего хода игрока
	 */
	void currentTurn(field * f);

	/*
	 /* проверяет, существует ли клетка с именем cell
	 /* return true, если да, иначе - нет
	 */
	bool checkCellNumber(field * f, std::string cell);

	/*
	 /* начало новой игры
	 */
	void startNewGame(field *f);

	/*
	 /* открывает все ячейки вокруг ячейки с 0 бомб вокруг нее, выполняется рекурсивно,
	 /* пока все такие ячейки не будут открыты
	 */
	void openCellsAroundZeroCell(unsigned int x, unsigned int y, field * f);

	/*
	 /* возвращает число отмеченных клеток на данный момент
	 */
	unsigned int markedCellsCount(field * f);

	/*
	 /* выбор подходящей ячейки и возврат ее
	 */
	std::string suitableCell(field *f);

	/*
	 /* помечает выбранную ячейку
	 */
	void markCell(field *f, unsigned int i, unsigned int j);

	/*
	 /* открывает выбранную ячейку
	 */
	void openCell(field *f, unsigned int i, unsigned int j);

	/*
	 /* сохраняет текущую игру
	 */
	void saveGame(field *f);

	/*
	 /* загружает или удаляет одну из сохраненных игр
	 */
	void loadOrDeleteSavedGame(field *f);

	/*
	 /* попытка продолжения игры
	 */
	void ifContinue(field *f);

	/*
	 /* изменяет текущее состояние числа шифрования
	 */
	unsigned int changeNum(unsigned int num);

	/*
	 /* зашифровывает данные о бомбах
	 */
	std::string encryption(unsigned int * bombs, field *f);

	/*
	 /* расшифровывает данные о бомбах
	 */
	std::string decryption(std::string str);
};

