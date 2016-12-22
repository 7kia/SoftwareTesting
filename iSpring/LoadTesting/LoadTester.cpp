#include "stdafx.h"
#include "LoadTester.h"

CLoadTester::CLoadTester(float CpuLoad, size_t MemomryLoad)
{
	m_cpuLoad = CpuLoad;
	sizeof(OneMegabyte);
	m_memory.resize(MemomryLoad);
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
	for (size_t index = 0; index < m_amountCpu; ++index)
	{
		m_dataForThread.push_back(SDataForThread());

		m_threads.push_back(CreateThread(NULL, 0, &ThreadFunction, &m_dataForThread[index], CREATE_SUSPENDED, NULL));
		SetThreadAffinityMask(m_threads.back(), GetAffinityMask(index, m_amountCpu));
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