#pragma once

/*
 / описание правил игры
 */
void introduction();

/*
 / описание начала игры
 */
void startGame();

/*
 / проверка, что введенна€ строка €вл€етс€ числом
 */
bool ifStringIsInt(std::string str);

/*
 / результаты последнего хода игрока
 */
void currentTurn(field * f);

/*
 / провер€ет, существует ли клетка с именем cell
 / return true, если да, иначе - нет
 */
bool checkCellNumber(field * f, std::string cell);

/*
 / начало новой игры
 */
void startNewGame();

/*
 / открывает все €чейки вокруг €чейки с 0 бомб вокруг нее, выполн€етс€ рекурсивно,
 / пока все такие €чейки не будут открыты
 */
void openCellsAroundZeroCell(unsigned int x, unsigned int y, field * f);

/*
 / возвращает число отмеченных клеток на данный момент
 */
unsigned int markedCellsCount(field * f);

/*
 / выбор подход€щей €чейки и возврат ее
 */
std::string suitableCell(field *f);

/*
 / помечает выбранную €чейку
 */
void markCell(field *f, unsigned int i, unsigned int j);

/*
 / открывает выбранную €чейку
 */
void openCell(field *f, unsigned int i, unsigned int j);

/*
 / сохран€ет текущую игру
 */
void saveGame(field *f);

/*
 / загружает или удал€ет одну из сохраненных игр
 */
void loadOrDeleteSavedGame(field *f);

/*
 / попытка продолжени€ игры
 */
void ifContinue(field *f);

/*
/ измен€ет текущее состо€ние числа шифровани€
*/
unsigned int changeNum(unsigned int num);

/*
 / зашифровывает данные о бомбах
 */
std::string encryption(unsigned int * bombs, field *f);

/*
 / расшифровывает данные о бомбах
 */
std::string decryption(std::string str);
