#pragma once

#include "DxLib.h"


//�}�N����`
#define GameFPS 60 //�ݒ肵����FPS

#define MicroSecond 1000000.0f//�P�}�C�N���b�@
#define MillSecond  1000.0f	  //�P�~���b
#define WaitTImeMill 3000	  //�ő�҂Ă�~����


typedef struct  _FPS{
	LONGLONG FirstTakeTime = 0;   //�P�t���[���ڂ̌v������
	LONGLONG NowTakeTime = 0;	  //���݂̌v������
	LONGLONG OldTakeTime = 0;	  //�ȑO�̌v������
								  
	float Deltatime = 0.000001f;  //�f���^�^�C���i�o�ߎ��ԁj
	int FrameConut = 1;			  //���݂̃t���[�����i�P�t���[���ځ`MAX�t���[���ڂ܂Łj
	float Average = 0.0f;		  //����FPS�l

}FPS;

//�O���O���[�o���ϐ�
extern FPS g_pfs;

//�O���v���g�^�C�v�錾
extern VOID FPSInit();  //FPS������
extern VOID FPSCheck(); //FPS�v��
extern VOID FPSDraw();	 //FPS�`��
extern VOID FPSWait();	 //FPS�ҋ@
