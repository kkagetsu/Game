#pragma once

#include "DxLib.h"
#include "player.h"
class Cursor {

public:
	int x1;       //�J�[�\���̍���̂����W
	int x2;       //�J�[�\���̍���̂����W
	int y1;       //�J�[�\���̉E���̂����W
	int y2;       //�J�[�\���̉E���̂����W

	int playerX1; //playerUI�J�[�\���̍���̂����W
	int playerY1; //playerUI�J�[�\���̍���̂����W
	int playerX2; //playerUI�J�[�\���̉E���̂����W
	int playerY2; //playerUI�J�[�\���̉E���̂����W

	int color;
	char key[256];
	

	LONGLONG lastMoveTime;  //by gtp �Ō�Ɉړ������������L�^����ϐ�
	LONGLONG lastBlinkTime;  // gtp�Ō�ɓ_�ł�������
	const LONGLONG blink = 800000;//gtp�_�ŊԊu

	BOOL isPlayerUICursor;//�v���C��UI�J�[�\���̏o���^����
	BOOL isMapCursor;//�}�b�v�J�[�\���̏o���^����
	BOOL isBlink;  // gtp�_�Ō��ʂ̂��߂̕\���t���O
	BOOL isPlayerSelected; //by gtp �v���C���[���I������Ă��邩�������t���O
	BOOL isPlayerMoveShow; //�v���C���[��Move2�\����ԃt���O

	Player& player; // /by gtp �v���C���[�̎Q��

	E_PLAYER_UI_T playerUI_Is;//playerUI���͂ǂ�����ԂȂ̂��̗񋓑̐錾

	Cursor(Player& player);
	VOID CursorControl();//�J�[�\������
	VOID CursorDraw();    //�}�b�v�J�[�\���`��
	VOID MapInfoShow();   //�}�b�v��̒n�`����\��

	VOID PlayerUIControl(); //�v���C��UI�J�[�\������
	VOID PlayerUICursorDraw();    //playerUI�J�[�\���`��
	VOID Switching();//�}�b�v�I������v���C���@�v���C������}�b�v
	VOID DrawMoveRange();

};

