/*
	myTimer.cpp

	���ԊǗ��p
*/
#include "myTimer.h"
#include <time.h>
#include <tchar.h>
#include "DxLib.h"

// �^�C�}�[������.
void InitMyTimer(MyTimer* pTimer)
{
	pTimer->m_startTime.QuadPart = 0;
	pTimer->m_frequency.QuadPart = 0;
	QueryPerformanceFrequency(&pTimer->m_frequency);
}

// �^�C�}�[�J�n.
void StartTimer(MyTimer* pTimer)
{
	QueryPerformanceCounter(&pTimer->m_startTime);
}

// �J�n����̌o�ߎ��Ԃ𓾂�.
void GetPassTime(MyTimer* pTimer, LONGLONG* pMicroSec, UINT* pFps)
{
	LARGE_INTEGER endTime;
	LARGE_INTEGER elapsedMS;

	QueryPerformanceCounter(&endTime);
	elapsedMS.QuadPart = endTime.QuadPart - pTimer->m_startTime.QuadPart;

	elapsedMS.QuadPart *= 1000000;
	elapsedMS.QuadPart /= pTimer->m_frequency.QuadPart;

	*pMicroSec = elapsedMS.QuadPart;
	*pFps = (UINT)(1000000 / elapsedMS.QuadPart);
}
