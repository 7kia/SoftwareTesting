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

bool CheckParametrs(int argc, char *argv[])
{
	if (argc == AMOUNT_ARGUMENTS)
	{
		return true;
	}
	cout << MESSAGE_AMOUNT_ARGUMENTS_IS_INCORRECT + to_string(AMOUNT_ARGUMENTS) << endl;

	return false;
}

int main(int argc, char *argv[])
{
	CheckParametrs(argc, argv);

	TrianlgeType type = GetTriangleType(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    return 0;
}

