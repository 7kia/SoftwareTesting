// LoadTesting.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "LoadTester.h"

int main(int argc, char * argv[])
{
	CLoadTester tester(25.f, size_t(1024));

	tester.CreateThreads();
	tester.ResumeThreads();

    return 0;
}

