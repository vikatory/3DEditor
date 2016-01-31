#include "TimerClass.h"


TimerClass::TimerClass(void)
{
}


TimerClass::TimerClass(const TimerClass& other)
{
}


TimerClass::~TimerClass(void)
{
}

bool TimerClass::Initialize()
{
	// ���ϵͳ�Ƿ�֧�ָ߾��ȼ�ʱ��.
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	if (m_frequency == 0)
	{
		return false;
	}

	// �õ�ÿ������ٸ�������.
	m_ticksPerMs = (float)(m_frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);

	return true;
}

//ÿ����Ⱦ֡���ᱻ���ã��Ӷ������ÿ֮֡���ʱ��
void TimerClass::Frame()
{
	INT64 currentTime;
	float timeDifference;


	QueryPerformanceCounter((LARGE_INTEGER*)& currentTime);

	timeDifference = (float)(currentTime - m_startTime);

	m_frameTime = timeDifference / m_ticksPerMs;

	m_startTime = currentTime;

	return;
}

float TimerClass::GetTime()
{
	return m_frameTime;
}

