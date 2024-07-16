#define _CRT_SECURE_NO_WARNINGS
#include "player.h"
#include "playScene.h"
#include "gameManager.h"

Player::Player() {

	strcpy(this->name, "�R�E�^���E");
	strcpy(this->job,"���m");
	strcpy(this->speSkill,"��C�T");
	strcpy(this->jobSkill[0], "�o�A��");
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
	this->move = 3;   //�ړ���
	this->posx = 0;
	this->posy = 0;
	

	memset(grHandle, NULL, sizeof(grHandle)); //�摜��load�Ɖ摜���i�[�p�̕ϐ��𕪂��Ă��ꂼ�ꏉ�������� �����ł̓[���N���A
	memset(grHandleUI, NULL, sizeof(grHandleUI));
}

VOID Player :: GraphicLoad() {

	grHandle[TACHI1_E] = LoadGraph("picture/player1/player_tachie1.png");
	grHandle[TACHI2_E] = LoadGraph("picture/player1/player_tachie2.png");
	grHandle[WAKU1__E] = LoadGraph("picture/player1/player_waku1.png");
	grHandle[WAKU2__E] = LoadGraph("picture/player1/player_waku2.png");
	grHandle[PIXEL__E] = LoadGraph("picture/player1/player_pixel.png");

	grHandleUI[MOVE_E]      = LoadGraph("picture/player1_ui/move.png");
    grHandleUI[ATTACK_E]	= LoadGraph("picture/player1_ui/attack.png");
    grHandleUI[ITEAM_E]		= LoadGraph("picture/player1_ui/iteam.png");
    grHandleUI[WAIT_E]		= LoadGraph("picture/player1_ui/wait.png");
    grHandleUI[SPSKILL_E]	= LoadGraph("picture/player1_ui/wolf.png");
    grHandleUI[LEARNSKILL_E]= LoadGraph("picture/player1_ui/book.png");
    grHandleUI[SKILL_1_E]   = LoadGraph("picture/player1_ui/skill1.png");



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
	DrawFormatString(200 + 15 * 4, 490, 0xFFFFFF, "Lv  %d",level );
	//p_exp
	DrawFormatString(300 + 15 * 4, 490, 0xFFFFFF,"exp %d", exp);

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


	PlayerUiShow();
}

VOID Player::PlayerPosInit() {

	//�`���g���A���̃L����pos�ݒ�
	if (TUTORIAL == 1) {
		this->posx = 16;
		this->posy = 7;
	}


}
VOID Player::PlayerPos() {

	int playMove = DrawExtendGraph(MASU___SIZE * posx,
		MASU___SIZE * posy,
		MASU___SIZE + MASU___SIZE * posx,
		MASU___SIZE + MASU___SIZE * posy,
		grHandle[PIXEL__E],
		TRUE);
	if (playMove == -1)
	{
		{
			OutputDebugString("playMove �G���[!!\n");
		}
	}

}

VOID Player::PlayerUiShow() {
	//�����������c��
	for (int i = 0; i <= 4; i++) {
		DrawLine(560+i* MASU___SIZE, GRID_HEIGHT * MASU___SIZE, 
			     560+i* MASU___SIZE, WINDOW_HEIGHT, 0xFF0000);
	}
	//����
	for (int j = 0; j <= 3; j++) {
		DrawLine(560 , GRID_HEIGHT * MASU___SIZE + MASU___SIZE + j * MASU___SIZE,
			560 + 4 * MASU___SIZE, GRID_HEIGHT * MASU___SIZE + MASU___SIZE + j * MASU___SIZE, 0xFF0000);
	}



		//x560y480 x560+40 y480+40
	//�ړ��A�C�R��
	//int moveGraphic = DrawExtendGraph(560 + 2, GRID_HEIGHT * MASU___SIZE + 2,
	//	                        600 - 2, GRID_HEIGHT * MASU___SIZE+ MASU___SIZE - 2, grHandleUI[MOVE_E], TRUE);
	//if (moveGraphic == -1)
	//{
	//	OutputDebugString("moveG �G���[!!\n");
	//}
	for (int i = 0; i <= PLAYER_UI_COUNT-4; i++) {

		// 0�ړ��A�C�R�� 1�U���@2�A�C�e���@3�ҋ@
		DrawExtendGraph(560 + i*MASU___SIZE + 2, GRID_HEIGHT * MASU___SIZE + 2,
			600 + i * MASU___SIZE  - 2, GRID_HEIGHT * MASU___SIZE + MASU___SIZE - 2, grHandleUI[i], TRUE);




	}
	  //����
	    DrawExtendGraph(560 + 1 * MASU___SIZE + 2, GRID_HEIGHT * MASU___SIZE+ MASU___SIZE + 2,
		600 + 1 * MASU___SIZE - 2, GRID_HEIGHT * MASU___SIZE + 2*MASU___SIZE - 2, grHandleUI[SPSKILL_E], TRUE);

      //�X�L���A�b�v
		DrawExtendGraph(560 + 3 * MASU___SIZE + 2, GRID_HEIGHT * MASU___SIZE + MASU___SIZE + 2,
			600 + 3 * MASU___SIZE - 2, GRID_HEIGHT * MASU___SIZE + 2 * MASU___SIZE - 2, grHandleUI[LEARNSKILL_E], TRUE);

	 //�X�L���P
		DrawExtendGraph(560 + 0 * MASU___SIZE + 2, GRID_HEIGHT * MASU___SIZE + 2*MASU___SIZE + 2,
			600 + 0 * MASU___SIZE - 2, GRID_HEIGHT * MASU___SIZE + 3 * MASU___SIZE - 2, grHandleUI[SKILL_1_E], TRUE);



	
}
VOID Player::PlayerMoveMessage(){

	DrawString(pUIMessageX, pUIMessageY,"Move\nkey: m",0xffffff);
	

}

VOID Player::PlayerAttack(){

	DrawString(pUIMessageX, pUIMessageY, "Attack\nkey: a", 0xffffff);

	if (true)
	{

	}

}
VOID Player::PlayerItem(){

	DrawString(pUIMessageX, pUIMessageY, "Item\nkey: b", 0xffffff);


}
VOID Player::PlayerMove() {

	for (int dy = -move; dy <= move; ++dy) {
		for (int dx = -move; dx <= move; ++dx) {
			if (abs(dx) + abs(dy) <= move) { // �_�C�������h�`�͈͓̔������`�F�b�N
				int x = posx + dx;
				int y = posy + dy;

			// �}�b�v�͈͓����ǂ������`�F�b�N
				if (x >= 0 && x < GRID__WIDTH && y >= 0 && y < GRID_HEIGHT) {
					// �}�X�̒��S���v�Z
					int drawX1 = x * MASU___SIZE;
					int drawY1 = y * MASU___SIZE;
					int drawX2 = drawX1 + MASU___SIZE;
					int drawY2 = drawY1 + MASU___SIZE;
					// �`��u�����h���[�h��ݒ� (�����x�ݒ�)
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); // 128�͓����x�̒l (0: ���S����, 255: ���S�s����)
					DrawBox(drawX1, drawY1, drawX2, drawY2, 0x0000ff, TRUE); // ���F�̘g���ŕ`��
					// �`��u�����h���[�h�����ɖ߂�
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				}
			}
		}
	}
}


VOID Player::PlayerWait(){

	DrawString(pUIMessageX, pUIMessageY, "Wait\nkey: s", 0xffffff);

}



VOID Player::PlayerUiUpdata() {

	//�ړ�


	//�ʏ�U���@�f�o�b�O�Ώۂ��Ȃ��׍Ō�ō��

	//�A�C�e��

	//�ҋ@�@�v���C���̍ő�20%��HP��15%MP���񕜂���

	//�����@�p�b�V�u�X�L�� ���ʏЉ���@��C�T�F�����̂P�}�X�ɖ������Ȃ��ꍇ�@�X�e�[�^�X�{�Q

	/*�X�L�� ���x���A�b�v���ƂɃX�L���|�C���g���Ⴆ��@
	�X�L���P�@�o�A���@�ΏۂɘA���̓��ʏ�U������@������75��/77.5%/80%/85%
	���������肵�@miss�̏ꍇ�@���L�����̍U���^�[�����I���ƌ��Ȃ�
	�����̏ꍇ�@�ʏ�U���̂Q�� Critical strike�𔻒肵
	Critical strike���萬���@�ʏ�_���[�W��1.5/1.65/1.8/2.0��Ώۂɗ^����
	MP���Ձ@�V/9/11/9
	��p���ԁicd�j3T/3T/3T/2T
	�擾�\�̃L�����̃��x���@0/2/4/6 
	�@
	*/

}

