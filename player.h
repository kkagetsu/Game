#pragma once
#include "DxLib.h"

enum tagE_PLAYER_T
{
	TACHI1_E
,	TACHI2_E
,   WAKU1__E
,   WAKU2__E
,   PIXEL__E
,   COUNT__E


} ;

class Player {
	//�����o�[�ϐ��Ȃ̂Ł@�O��m_��t���܂��傤 
private:
	char name[20];          //���O
	char job[10];		    //�E��
	char speSkill[10];      //����
	char jobSkill[3][10];   //�X�L��
	int level;			    //���x��
	int exp;                //�o���l
	int hp;				    //�̗�
	int mp;				    //����
	int pow;			    //��
	int def;			    //�h���
	int dex;			    //�����@����������Ȃ�
	int lnt;			    //�m��
	int mdf;			    //���@�h���
	int agi;			    //�f����
	int luc;			    //�^
	int move;               //�ړ���
	int grHandle[COUNT__E];
	int posx, posy;

public:

	Player(); //�v���C���[�̏�����
	VOID GraphicLoad();

	VOID StatusShow();
	
	VOID PlayerPosInit();

	VOID PlayerMove();

	VOID PlayerUiShow();

	// gtp �Q�b�^�[���\�b�h
	int getPosX() const { return posx; }
	int getPosY() const { return posy; }
}; 
