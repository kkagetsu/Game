#pragma once
/*
	myTimer.h

	時間管理用
*/
#pragma once

/////////////////////////////////////////////////////////////
// ↓タイマークラス.

typedef struct tagMyTimer
{
	LARGE_INTEGER m_startTime;
	LARGE_INTEGER m_frequency;

} MyTimer;

void InitMyTimer(MyTimer*);						// タイマー初期化.
void StartTimer(MyTimer*);						// タイマー開始.
void GetPassTime(MyTimer*, LONGLONG*, UINT*);	// 開始からの経過時間を得る.

// ↑タイマークラス.
/////////////////////////////////////////////////////////////
