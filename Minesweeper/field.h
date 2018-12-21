#pragma once

/*
 / ����� ���� ��� ����
 */
class field
{
	/*
	 / ������ ���� (����� � ������)
	 */
	unsigned int size;

	/*
	 / ���������� ��� �� ����
	 */
	unsigned int minesCount;

	/*
	 / ������ ����� ����, ���������� ������� ��� �� �������
	 */
	bool ** ifBomb;

	/*
	 / ������ ��������� ����� ����
	 / ��������: 0 - ������ ������, 1 - ������ ��������, 2 - ������ �������, �� �� �������� ������,
	 / 3 - ������ ������� � �������� ������
	 */
	unsigned int ** states;

public:
	/*
	 / ����������� ������ ��� �������� ����� ����
	 */
	field(unsigned int size, unsigned int minesCount);

	/*
	 / ����������� ������ ��� �������� ����������� ����
	 */
	field(unsigned int size, unsigned int bombsCount, std::string states, unsigned int * bombs);

	/*
	/ ������������ ���� �� ���� �� ������ ����
	*/
	void plantBombs();

	/*
	/ ���������� ���� ������ ������ ������
	/ return ���������� ���� ������ ������ ������
	*/
	unsigned int minesCountAroundCell(unsigned int i, unsigned int j);

	/*
	 / ���������� ������� ������ ����
	 */
	unsigned int returnSize();

	/*
	 / ���������� ����� ����
	 */
	unsigned int returnBombsCount();

	/*
	 / ���������� bool, �������� �� ������ ������ ��� ���
	 */
	bool ifCellIsBomb(unsigned int i, unsigned int j);

	/*
	 / ������ ��������� � ������ str �� ����� stateNumber
	 */
	void changeState(unsigned int i, unsigned int j, int stateNumber);

	/*
	 / ���������� ������� ��������� ������
	 */
	unsigned int returnState(unsigned int i, unsigned int j);

	/*
	 / ���������, ����������� �� ���� �������
	 */
	bool ifVictory();

	/*
	 / ����� �������� ��������� ���� �� �����
	 */
	void draw();

	/*
	 / ���������� ������
	 */
	~field();
};