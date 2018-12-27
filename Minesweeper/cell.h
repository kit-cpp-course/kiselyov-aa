#pragma once

/*
 /* ����� ��� ����� ����
 */
class cell
{
	/*
	 /* ����������, ����������, �������� �� ������ ������
	 */
	bool ifBomb = false;

	/*
	 /* ������� ��������� ������
	 /* ��������: 0 - ������ ������, 1 - ������ ��������, 2 - ������ �������, �� �� �������� ������,
	 /* 3 - ������ ������� � �������� ������
	 */
	unsigned int state = 0;

public:
	/*
	 /* ������������� �������� ������: ����� ��� �� �����
	 */
	void setIfBomb(bool ifBomb);

	/*
	 /* ������������� ��������� ������
	 */
	void setState(unsigned int state);

	/*
	 /* ��������� ��������� ������
	 */
	unsigned int returnState() { return state; };

	/*
	 /* ���������� bool, �������� �� ������ ������ ��� ���
	 */
	bool returnIfBomb() { return ifBomb; };
};