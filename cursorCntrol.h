#pragma once

#include "DxLib.h"
#include "player.h"
class Cursor {

public:
	int x1;       //�J�[�\���̍���̂����W
	int x2;       //�J�[�\���̍���̂����W
	int y1;       //�J�[�\���̉E���̂����W
	int y2;       //�J�[�\���̉E���̂����W

	BOOL mapCursor;//�}�b�v�J�[�\���̏o���^����
	

	int playerX1; //playerUI�J�[�\���̍���̂����W
	int playerY1; //playerUI�J�[�\���̍���̂����W
	int playerX2; //playerUI�J�[�\���̉E���̂����W
	int playerY2; //playerUI�J�[�\���̉E���̂����W

	BOOL playerUICursor;//�v���C��UI�J�[�\���̏o���^����

	int color;
	char key[256];
	
	LONGLONG lastMoveTime;  //by gtp �Ō�Ɉړ������������L�^����ϐ�


	bool isBlink;  // gtp�_�Ō��ʂ̂��߂̕\���t���O
	LONGLONG lastBlinkTime;  // gtp�Ō�ɓ_�ł�������
	const LONGLONG blink = 800000;//gtp�_�ŊԊu

	bool isPlayerSelected; //by gtp �v���C���[���I������Ă��邩�������t���O

	Player& player; // /by gtp �v���C���[�̎Q��

	Cursor(Player& player);
	VOID CursorControl();//�J�[�\������
	VOID CursorDraw();    //�}�b�v�J�[�\���`��
	VOID MapInfoShow();   //�}�b�v��̒n�`����\��

	VOID PlayerControl(); //�v���C��UI�J�[�\������
	VOID PlayerUICursorDraw();    //playerUI�J�[�\���`��
	VOID Switching();//�}�b�v�I������v���C���@�v���C������}�b�v


};

