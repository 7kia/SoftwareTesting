// LoadTesting.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "main.h"
#include "LoadTester.h"

using namespace std;

namespace
{
	void CheckParametrs(int argc)
	{
		if ((argc != AMOUNT_ARGUMENTS) && (argc != AMOUNT_ARGUMENTS_WITH_ADDITIONAL))
		{
			throw invalid_argument(MESSAGE_INCORRECT_AMOUNT_ARGUMENTS
				+ to_string(AMOUNT_ARGUMENTS)
				+ " or "
				+ to_string(AMOUNT_ARGUMENTS_WITH_ADDITIONAL)
				+ "\n If use additional parametr");
		}
	}

	void PrintHelp()
	{
		std::cout <<
			R"(Help
@param 0 - execute exe-file
@param 1 - number load cpu
@param 2 - amount megabyte load memory
@param 3(addirional) - help
		)" << std::endl;
	}

	bool CheckAdditionalParametr(int argc, char * argv[])
	{
		for (size_t index = 1; index < argc; ++index)
		{
			if (argv[index] == HELP_PARAMETER)
			{
				return true;
			}
		}

		return false;
	}


}

int main(int argc, char * argv[])
{
	try
	{

		setlocale(LC_ALL, "RUS");


		if (CheckAdditionalParametr(argc, argv))
		{
			PrintHelp();

			if (argc == 2)
			{
				return 0;
			}
		}

		CheckParametrs(argc);

		CLoadTester tester(size_t(atoi(argv[1])), size_t(atoi(argv[2])));

		tester.CreateThreads();
		tester.ResumeThreads();

	}
	catch (const std::exception & exception)
	{
		std::cout << exception.what() << std::endl;
	}

	system("pause");
	return 0;

}

