// Triangle.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream>
#include <string>

#include "Triangle.h"

using namespace std;

namespace
{
	static const int AMOUNT_ARGUMENTS = 4;
	static std::string MESSAGE_AMOUNT_ARGUMENTS_IS_INCORRECT = "Amount arguments is incorrect";
}

void CheckParametrs(int argc, char *argv[])
{
	if (argc != AMOUNT_ARGUMENTS)
	{
		throw std::runtime_error(MESSAGE_AMOUNT_ARGUMENTS_IS_INCORRECT + to_string(AMOUNT_ARGUMENTS));
	}
}

int main(int argc, char *argv[])
{

	try
	{
		CheckParametrs(argc, argv);
	}
	catch (const std::runtime_error & exception)
	{
		cout << exception.what();
		return 1;
	}

	cout << ToString(GetTriangleType(float(atof(argv[1]))
									, float(atof(argv[2]))
									, float(atof(argv[3]))
									)
					);

    return 0;
}

