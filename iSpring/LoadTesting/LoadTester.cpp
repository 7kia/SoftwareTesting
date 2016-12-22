#include "stdafx.h"
#include "LoadTester.h"

CLoadTester::CLoadTester(size_t CpuNumber, size_t MemomrySize)
{
	m_cpuLoad = CpuNumber;
	m_memory.resize(MemomrySize);
}

CLoadTester::~CLoadTester()
{
}

int CLoadTester::GetAffinityMask(size_t amountThread, size_t threadIndex)
{
	int mask = 0x0000;

	if (amountThread / m_amountCpu == 0)
	{
		return 1;
	}

	int cpuIndex = (threadIndex) / (amountThread / m_amountCpu);
	if ((amountThread % m_amountCpu == 1) && (cpuIndex > 0))
	{
		cpuIndex--;
	}
	return int(pow(2.f, cpuIndex));
}

void CLoadTester::CreateThreads()
{
	for (size_t index = 0; index < m_cpuLoad; ++index)
	{
		m_dataForThread.push_back(SDataForThread());

		m_threads.push_back(CreateThread(NULL, 0, &ThreadFunction, &m_dataForThread[index], CREATE_SUSPENDED, NULL));
		SetThreadAffinityMask(m_threads.back(), GetAffinityMask(m_amountCpu, index));
	}
}

void CLoadTester::ResumeThreads()
{
	for (auto & thread : m_threads)
	{
		ResumeThread(thread);
	}
	// ждем, пока все эти потоки завершатся
	WaitForMultipleObjects(m_threads.size(), m_threads.data(), TRUE, INFINITE);
}


DWORD WINAPI CLoadTester::ThreadFunction(LPVOID lpParam)
{
	while (true)
	{
		//Sleep(1);
	}
	return 0;
}