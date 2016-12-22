#pragma once

#include <vector>
#include <array>
#include <Windows.h>

class CLoadTester
{
public:
	CLoadTester(size_t CpuNumber, size_t MemomrySize);
	~CLoadTester();

	struct SDataForThread
	{

	};
//////////////////////////////////////////////////////////////////////
// Methods
public:
	using OneKilobyte = std::array<char, 1024>;
	using OneMegabyte = std::array<OneKilobyte, 1024>;

	int	GetAffinityMask(size_t amountThread, size_t threadIndex);
	void CreateThreads();

	void ResumeThreads();

	static DWORD WINAPI ThreadFunction(LPVOID lpParam);

//////////////////////////////////////////////////////////////////////
// Data
private:
	std::vector<HANDLE>				m_threads;
	std::vector<SDataForThread>		m_dataForThread;
	std::vector<OneMegabyte>		m_memory;

	float							m_cpuLoad = 0.f;
	size_t							m_amountCpu = 4;

};