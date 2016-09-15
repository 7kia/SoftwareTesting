// Triangle.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <boost/algorithm/string.hpp>


#include "Triangle.h"

using namespace std;

namespace
{
	static const int AMOUNT_ARGUMENTS = 4;
	static const char SYMBOL_POINT = '.';
}

void CheckParametrs(int argc, char *argv[])
{
	if (argc != AMOUNT_ARGUMENTS)
	{
		throw std::runtime_error(Messages::MESSAGE_AMOUNT_ARGUMENTS_IS_INCORRECT);
	}


	for (size_t index = 1; index < AMOUNT_ARGUMENTS; ++index)
	{
		std::string argument = argv[index];
		if ( ((argument.size() == 1) && (argument[0] == SYMBOL_POINT) )// Одна точка не число
			||
			!all_of(argument.begin()// Может быть число или точка
					, argument.end()
					, [&](auto symbol) {
						return (isdigit(symbol) || (symbol == SYMBOL_POINT));
						}
					)
			|| (std::count(argument.begin()// Не может быть несколько точек
							, argument.end()
							, SYMBOL_POINT) > 1)
			)
		{
			throw std::runtime_error(Messages::MESSAGE_AMOUNT_ARGUMENTS_IS_INCORRECT);
		}

	}
}

int main(int argc, char *argv[])
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	try
	{
		CheckParametrs(argc, argv);
	}
	catch (const std::runtime_error & exception)
	{
		cout << exception.what();
		return 1;
	}

	cout << ToString(GetTriangleType(stof(argv[1])
									, stof(argv[2])
									, stof(argv[3])
									)
					);

    return 0;
}

