#pragma once
/*
	myTimer.h

	���ԊǗ��p
*/
#pragma once

/////////////////////////////////////////////////////////////
// ���^�C�}�[�N���X.

typedef struct tagMyTimer
{
	LARGE_INTEGER m_startTime;
	LARGE_INTEGER m_frequency;

} MyTimer;

void InitMyTimer(MyTimer*);						// �^�C�}�[������.
void StartTimer(MyTimer*);						// �^�C�}�[�J�n.
void GetPassTime(MyTimer*, LONGLONG*, UINT*);	// �J�n����̌o�ߎ��Ԃ𓾂�.

// ���^�C�}�[�N���X.
/////////////////////////////////////////////////////////////
