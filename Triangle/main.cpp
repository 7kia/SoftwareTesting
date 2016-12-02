// Triangle.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string.hpp>


#include "Triangle.h"

using namespace std;

namespace
{
	static const int AMOUNT_ARGUMENTS = 4;
	static const char SYMBOL_POINT = '.';
	static const char SYMBOL_COMMA = ',';
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
		boost::replace_all(argument, ".", ",");
		if ( ((argument.size() == 1) && (argument[0] == SYMBOL_COMMA) )// Одна точка не число
			||
			!all_of(argument.begin()// Может быть число или точка
					, argument.end()
					, [&](auto symbol) {
						return (((int(symbol) > 47) && (int(symbol) < 58)) || (symbol == SYMBOL_COMMA));//isdigit(symbol)
						}
					)
			|| (std::count(argument.begin()// Не может быть несколько точек
							, argument.end()
							, SYMBOL_COMMA) > 1)
			)
		{
			throw std::runtime_error(Messages::MESSAGE_AMOUNT_ARGUMENTS_IS_INCORRECT);
		}

	}
}

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");

	try
	{
		char p = char(44);

		CheckParametrs(argc, argv);
	}
	catch (const std::runtime_error & exception)
	{
		cout << exception.what();
		return 1;
	}

	std::string arguments[AMOUNT_ARGUMENTS - 1];
	for (size_t index = 1; index < AMOUNT_ARGUMENTS; ++index)
	{
		arguments[index - 1] = argv[index];
		boost::replace_all(arguments[index - 1], ".", ",");
	}
	cout << ToString(GetTriangleType(stof(arguments[0])
									, stof(arguments[1])
									, stof(arguments[2])
									)
					);

    return 0;
}

