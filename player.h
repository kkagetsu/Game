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


enum tagE_PLAYER_UI_T 
{
	MOVE_E
,   ATTACK_E
,   ITEAM_E
,   WAIT_E
,   SPSKILL_E
,   LEARNSKILL_E
,   SKILL_1_E
,   PLAYER_UI_COUNT

};


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
	int mdf;                //���@�h���
	int agi;                //�f����
	int luc;			    //�^
	int move;               //�ړ���
	int action;             //�s���@�U���@�Q�@�ړ��P�@item�@�Q�@�X�L���@�Q�@action < 0�@�s���I��


	int grHandle[COUNT__E]; //player�P�̂����G
	int grHandleUI[PLAYER_UI_COUNT];//player�P��UI
	int posx, posy;         //���W
	const int pUIMessageX = 730;   //�v���C����UI���̕����\�����W
	const int pUIMessageY = 500;	//�v���C����UI���̕����\�����W

public:

	Player(); //�v���C���[�̏�����
	VOID GraphicLoad();

	VOID StatusShow();
	
	VOID PlayerPosInit();

	VOID PlayerPos();

	VOID PlayerUiShow();
	VOID PlayerMoveMessage();
	VOID PlayerMove();
	VOID PlayerAttack();
	VOID PlayerItem();
	VOID PlayerWait();

	VOID PlayerUiUpdata();
	unsigned int GetFlashingColor(int time);

	// gtp �Q�b�^-���W
	inline int getPosX() const { return posx; } //inline��
	inline int getPosY() const { return posy; }	//inline��

}; 
