#pragma once

#include "DxLib.h"
#include "player.h"
class Cursor {

public:
	int x1;
	int x2;
	int y1;
	int y2;
	int color;
	char key[256];
	
	LONGLONG lastMoveTime;  //by gtp �Ō�Ɉړ������������L�^����ϐ�


	bool isBlink;  // gtp�_�Ō��ʂ̂��߂̕\���t���O
	LONGLONG lastBlinkTime;  // gtp�Ō�ɓ_�ł�������
	const LONGLONG blink = 800000;//gtp�_�ŊԊu

	bool isPlayerSelected; //by gtp �v���C���[���I������Ă��邩�������t���O

	Player& player; // /by gtp �v���C���[�̎Q��

	Cursor(Player& player);
	VOID CursorControl( );
	VOID CursorDraw();
	VOID MapInfoShow();
	/****************************************************************************
�֐����FIsPlayerAction
�@�\  : �w�肳�ꂽ�v���C���[�͍�����ł��邩�i�����F�v���C���[�̃^�[���@�����ē��v���C���[�����s���j
�����@�Fcx  int  (in)   �J�[�\���̈ʒu�i�����W�j
�@�@�@�@cy  int  (in)   �J�[�\���̈ʒu�i�����W�j
		E_TURN_T (in)   ���݂̃v���C���[�@0:TURN_PLAYER / 1:TURN_ENEMY
�ԋp�l:	TRUN_NONE	: �R�}��u�����Ƃ͂ł��Ȃ�
		TRUN_PLAYER	: ���̃R�}��u���Ă悢
		TRUN_ENEMY	: ���̃R�}��u���Ă悢
*****************************************************************************/


	


};

