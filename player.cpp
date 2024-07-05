#define _CRT_SECURE_NO_WARNINGS
#include "player.h"
#include "playScene.h"

Player::Player() {

	strcpy(this->name, "�v���C���[");
	strcpy(this->job,"���m");
	strcpy(this->speSkill,"��C�T");
	strcpy(this->jobSkill[0], "�X�L��1");
	strcpy(this->jobSkill[1], "�X�L��2");
	strcpy(this->jobSkill[2], "�X�L��3");
	this->level = 1;    
	this->exp = 0;    //100���Ƃɂ� if(exp>=100) level++
	this->hp = 17;	  //�̗͒l
	this->mp = 12;	  //���͒l
	this->pow =10;	  //
	this->def = 7;	  //
	this->dex = 6;	  //������=100-(agi-dex)*10
	this->lnt = 9;	  //
	this->mdf = 7;	  //
	this->agi = 5;	  //
	this->luc = 8;	  //�N���e�B�J���q�b�g��=(luck*1.25%) �_���[�W attack x 1.5
	this->move = 2;   //�ړ���
	this->posx = 0;
	this->posy = 0;
	memset(grHandle, NULL, sizeof(grHandle)); //�摜��load�Ɖ摜���i�[�p�̕ϐ��𕪂��Ă��ꂼ�ꏉ�������� �����ł̓[���N���A

}

VOID Player :: GraphicLoad() {

	grHandle[TACHI1_E] = LoadGraph("picture/player1/player_tachie1.png");
	grHandle[TACHI2_E] = LoadGraph("picture/player1/player_tachie2.png");
	grHandle[WAKU1__E] = LoadGraph("picture/player1/player_waku1.png");
	grHandle[WAKU2__E] = LoadGraph("picture/player1/player_waku2.png");
	grHandle[PIXEL__E] = LoadGraph("picture/player1/player_pixel.png");


	//return true;
}

/****************************************************************************
�֐����FStatusShow
�@�\�@�F�J�[�\��(���W==�v���C���[���W)���L�����[��I�����邽�сA��ʂ̉����ɕ\�������X�e�[�^�X���ꗗ
�����@�Fbool isPlayer(�J�[�\����player��I�� TRUE)
		�ȏ�̏����𖞑�������ꍇ�L�����̃X�e�[�^�X��\��������

�ԋp�l:	�Ȃ�
*****************************************************************************/
VOID Player::StatusShow() {


	//0,12*40�̍��W�ŃL�����A�C�R���𐶐� 
	//int playerG = DrawGraph(0, GRID_HEIGHT * MASU___SIZE, grHandle[TACHI1_E],TRUE);
	int playerG = DrawExtendGraph(0, GRID_HEIGHT * MASU___SIZE,120,600, grHandle[WAKU1__E],TRUE);

	if (playerG == -1)
	{
		OutputDebugString("playerG �G���[!!\n");
	}
	//p_name �L������
	{
	DrawString(130,490,name,0xFF0000);
	}
	//p_job�L�����̐E��
	//DrawString(130,490+15,job, 0xFFFFFF);
	DrawFormatString(130, 490 + 15, 0xFFFFFF, "�E��: %s",job);
	//p_speSkill ����
	//DrawString(130,490+15*2,speSkill, 0xFFFFFF);
	DrawFormatString(130, 490 + 15 * 3, 0xFFFFFF, "����: %s", speSkill);
	
	//p_level
	//DrawString(200,490,"Lv  %d",level, 0xFFFFFF);
	DrawFormatString(200, 490, 0xFFFFFF, "Lv  %d",level );
	//p_exp
	DrawFormatString(200 + 15 * 4, 490, 0xFFFFFF,"exp %d", exp);

	//p_hp
	{
		DrawString(200 + 15*4, 490 + 15 * 1,"Hp",0xFFFFFF);
		//hp�̃Q�[�W��`��
		for (int i =0; i <= hp; i++) {

			DrawString(200 + 15*5+3*i, 490 + 15 * 1,"l",0x00FF00);
		}
	}
	//p_mp
	{
		DrawString(200 + 15*4, 490 + 15 * 2, "Mp", 0xFFFFFF);
		//mp�̃Q�[�W��`��
		for (int i = 0; i <= mp; i++) {
			DrawString(200 + 15*5 + 3 * i, 490 + 15 * 2, "l", 0x0000FF);
		}
	}
	//p_pow
	//DrawString(200 + 15, 490 + 15 *3,"Pow  %d",pow, 0xFFFFFF);
	DrawFormatString(200 + 15*4, 490 + 15 * 3, 0xFFFFFF, "Pow  %d", pow);
	//p_def
	//DrawString(200 + 15, 490 + 15 *4,"Def  %d",def, 0xFFFFFF);
	DrawFormatString(200 + 15*4, 490 + 15 * 4, 0xFFFFFF, "Def  %d", def);
	//p_dex
	//DrawString(200 + 15, 490 + 15 *5,"Dex  %d",dex, 0xFFFFFF);
	DrawFormatString(200 + 15*4, 490 + 15 * 5, 0xFFFFFF, "Dex % d",dex);

	//p_lnt
	//DrawString(200 + 15*2, 490 + 15 * 3,"lnt  %d", lnt,0xFFFFFF);
	DrawFormatString(200 + 15 * 10, 490 + 15 * 3, 0xFFFFFF, "lnt  %d", lnt);
	//p_mdf
	//DrawString(200 + 15*2, 490 + 15 * 4,"mdf  %d", mdf,0xFFFFFF);
	DrawFormatString(200 + 15 * 10, 490 + 15 * 4, 0xFFFFFF, "mdf  %d", mdf);

	//agi
	//DrawString(200 + 15 * 3, 490 + 15 * 3, "agi  %d", agi, 0xFFFFFF);
	DrawFormatString(200 + 15 * 15, 490 + 15 * 3, 0xFFFFFF, "agi  %d", agi);
	//luc
	//DrawString(200 + 15 * 3, 490 + 15 * 4, "luc  %d", luc, 0xFFFFFF);
	DrawFormatString(200 + 15 * 15, 490 + 15 * 4, 0xFFFFFF, "luc  %d", luc);
}

VOID Player::PlayerPosInit() {

	//�`���g���A���̃L����pos�ݒ�
	if (TUTORIAL == 1) {
		this->posx = 16;
		this->posy = 7;
	}
	DrawExtendGraph(MASU___SIZE * posx, 
		            MASU___SIZE * posy, 
		            MASU___SIZE + MASU___SIZE * posx, 
		            MASU___SIZE + MASU___SIZE * posy, 
		            grHandle[PIXEL__E], 
		            TRUE);

}
VOID Player::PlayerMove() {

	int playmove = DrawExtendGraph(MASU___SIZE * posx,
		MASU___SIZE * posy,
		MASU___SIZE + MASU___SIZE * posx,
		MASU___SIZE + MASU___SIZE * posy,
		grHandle[PIXEL__E],
		TRUE);
	if (playmove == -1)
	{
		{
			OutputDebugString("playmove �G���[!!\n");
		}
	}

}

VOID Player::PlayerUiShow() {


	  



}
