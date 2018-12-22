#pragma once

/*
 /* абстрактный класс, обеспечивающий взаимодействие класса field с консолью
 */
class component
{
public:
	/*
	 /* выводит информацию на консоль
	 */
	virtual void draw() = 0;
};