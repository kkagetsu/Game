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
,   PLAYER_UI_E_COUNT

};
enum tagE_PLAYER_UI_T {
	  PLAYER_UI_MOVE
,     PLAYER_UI_ATTACK
,     PLAYER_UI_ITEM
,     PLAYER_UI_WAIT
,     PLAYER_UI_SPSKILL
,     PLAYER_UI_SKILLPOINT
,     PLAYER_UI_SKILL1
,     PLAYER_UI_SKILL2
,     PLAYER_UI_SKILL3
,     PLAYER_UI_SKILL4

,     PLAYER_UI_COUNT
,     PLAYER_UI_INVALID = -1
,     PLAYER_UI_BEGIN

};

enum tagE_PLAYER_ACTION {
	PLAYER_ACTION_NONE   //COST 0
	, PLAYER_ACTION_MOVE	 //COST 1
	, PLAYER_ACTION_ATTACK //COST 2
	, PLAYER_ACTION_ITEM	 //COST 2
	, PLAYER_ACTION_WAIT	 //COST 2
	, PLAYER_ACTION_SPSKILL//COST 2
	, PLAYER_ACTION_SKILL1 //COST 2
	, PLAYER_ACTION_SKILL2 //COST 2
	, PLAYER_ACTION_SKILL3 //COST 2
	, PLAYER_ACTION_SKILL4 //COST 2

	, PLAYER_ACTION_COUNT
	, PLAYER_ACTION_INVALID = - 1
    , PLAYER_ACTION_BEGIN

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
	int action;             //�s���@�U���@�Q�@�ړ��P�@item�@�Q�@�X�L���@�Q�@action < = 0�@�s���I��


	int grHandle[COUNT__E]; //player�P�̂����G
	int grHandleUI[PLAYER_UI_E_COUNT];//player�P��UI
	int posx, posy;         //���W
	const int pUIMessageX = 730;   //�v���C����UI���̕����\�����W
	const int pUIMessageY = 500;	//�v���C����UI���̕����\�����W
	tagE_PLAYER_ACTION arPlayerAction;

public:

	Player(); //�v���C���[�̏�����
	VOID GraphicLoad();//player1���g���G�����ׂĂ����Ń��[�h����

	VOID StatusShow();//�v���C����UI�`��͂��ׂĂ��̊֐��̒��@�X�e�[�^�X��ʁ@+ �R�}���h�w�߉��(PlayerUiShow)
	
	VOID PlayerPosInit();//�v���C���P�̐����ꍇ���w��i�������j

	VOID PlayerPos();//�v���C���̂����ꏊ��`��

	VOID PlayerUiShow();//�R�}���h�w�߉�ʂ�`��
	VOID PlayerMoveMessage();//�L�[��
	VOID PlayerAbleMove();//�ړ��͈͓W�J�̕`��
	VOID PlayerAttackMessage();//�L�[��
	VOID PlayerItemMessage();//�L�[��
	VOID PlayerWaitMessage();//�L�[��
	//VOID PlayerAction();//�v���C����
	VOID PlayerUiUpdata();
	unsigned int GetFlashingColor(int time);

	//  �Q�b�^-���W
	inline int getPosX() const { return posx; } //inline��
	inline int getPosY() const { return posy; }	//inline��
	inline int getMove() const { return move; }	//inline��

	VOID setPosX(int x) { this->posx = x; }
	VOID setPosY(int y) { this->posy = y; }

}; 
