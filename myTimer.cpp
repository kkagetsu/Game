/*
	myTimer.cpp

	時間管理用
*/
#include "myTimer.h"
#include <time.h>
#include <tchar.h>
#include "DxLib.h"

// タイマー初期化.
void InitMyTimer(MyTimer* pTimer)
{
	pTimer->m_startTime.QuadPart = 0;
	pTimer->m_frequency.QuadPart = 0;
	QueryPerformanceFrequency(&pTimer->m_frequency);
}

// タイマー開始.
void StartTimer(MyTimer* pTimer)
{
	QueryPerformanceCounter(&pTimer->m_startTime);
}

// 開始からの経過時間を得る.
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
