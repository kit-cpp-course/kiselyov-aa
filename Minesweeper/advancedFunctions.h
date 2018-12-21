#pragma once

/*
 / �������� ������ ����
 */
void introduction();

/*
 / �������� ������ ����
 */
void startGame();

/*
 / ��������, ��� ��������� ������ �������� ������
 */
bool ifStringIsInt(std::string str);

/*
 / ���������� ���������� ���� ������
 */
void currentTurn(field * f);

/*
 / ���������, ���������� �� ������ � ������ cell
 / return true, ���� ��, ����� - ���
 */
bool checkCellNumber(field * f, std::string cell);

/*
 / ������ ����� ����
 */
void startNewGame();

/*
 / ��������� ��� ������ ������ ������ � 0 ���� ������ ���, ����������� ����������,
 / ���� ��� ����� ������ �� ����� �������
 */
void openCellsAroundZeroCell(unsigned int x, unsigned int y, field * f);

/*
 / ���������� ����� ���������� ������ �� ������ ������
 */
unsigned int markedCellsCount(field * f);

/*
 / ����� ���������� ������ � ������� ��
 */
std::string suitableCell(field *f);

/*
 / �������� ��������� ������
 */
void markCell(field *f, unsigned int i, unsigned int j);

/*
 / ��������� ��������� ������
 */
void openCell(field *f, unsigned int i, unsigned int j);

/*
 / ��������� ������� ����
 */
void saveGame(field *f);

/*
 / ��������� ��� ������� ���� �� ����������� ���
 */
void loadOrDeleteSavedGame(field *f);

/*
 / ������� ����������� ����
 */
void ifContinue(field *f);

/*
/ �������� ������� ��������� ����� ����������
*/
unsigned int changeNum(unsigned int num);

/*
 / ������������� ������ � ������
 */
std::string encryption(unsigned int * bombs, field *f);

/*
 / �������������� ������ � ������
 */
std::string decryption(std::string str);
