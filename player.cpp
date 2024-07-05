#define _CRT_SECURE_NO_WARNINGS
#include "player.h"
#include "playScene.h"

Player::Player() {

	strcpy(this->name, "プレイヤー");
	strcpy(this->job,"剣士");
	strcpy(this->speSkill,"一匹狼");
	strcpy(this->jobSkill[0], "スキル1");
	strcpy(this->jobSkill[1], "スキル2");
	strcpy(this->jobSkill[2], "スキル3");
	this->level = 1;    
	this->exp = 0;    //100ごとにに if(exp>=100) level++
	this->hp = 17;	  //体力値
	this->mp = 12;	  //魔力値
	this->pow =10;	  //
	this->def = 7;	  //
	this->dex = 6;	  //命中率=100-(agi-dex)*10
	this->lnt = 9;	  //
	this->mdf = 7;	  //
	this->agi = 5;	  //
	this->luc = 8;	  //クリティカルヒット率=(luck*1.25%) ダメージ attack x 1.5
	this->move = 2;   //移動量
	this->posx = 0;
	this->posy = 0;
	memset(grHandle, NULL, sizeof(grHandle)); //画像のloadと画像を格納用の変数を分けてそれぞれ初期化する ここではゼロクリア

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
関数名：StatusShow
機能　：カーソル(座標==プレイヤー座標)がキャラーを選択するたび、画面の下方に表示されるステータス情報一覧
引数　：bool isPlayer(カーソルでplayerを選択中 TRUE)
		以上の条件を満足しいる場合キャラのステータスを表示させる

返却値:	なし
*****************************************************************************/
VOID Player::StatusShow() {


	//0,12*40の座標でキャラアイコンを生成 
	//int playerG = DrawGraph(0, GRID_HEIGHT * MASU___SIZE, grHandle[TACHI1_E],TRUE);
	int playerG = DrawExtendGraph(0, GRID_HEIGHT * MASU___SIZE,120,600, grHandle[WAKU1__E],TRUE);

	if (playerG == -1)
	{
		OutputDebugString("playerG エラー!!\n");
	}
	//p_name キャラ名
	{
	DrawString(130,490,name,0xFF0000);
	}
	//p_jobキャラの職業
	//DrawString(130,490+15,job, 0xFFFFFF);
	DrawFormatString(130, 490 + 15, 0xFFFFFF, "職業: %s",job);
	//p_speSkill 特性
	//DrawString(130,490+15*2,speSkill, 0xFFFFFF);
	DrawFormatString(130, 490 + 15 * 3, 0xFFFFFF, "特性: %s", speSkill);
	
	//p_level
	//DrawString(200,490,"Lv  %d",level, 0xFFFFFF);
	DrawFormatString(200, 490, 0xFFFFFF, "Lv  %d",level );
	//p_exp
	DrawFormatString(200 + 15 * 4, 490, 0xFFFFFF,"exp %d", exp);

	//p_hp
	{
		DrawString(200 + 15*4, 490 + 15 * 1,"Hp",0xFFFFFF);
		//hpのゲージを描画
		for (int i =0; i <= hp; i++) {

			DrawString(200 + 15*5+3*i, 490 + 15 * 1,"l",0x00FF00);
		}
	}
	//p_mp
	{
		DrawString(200 + 15*4, 490 + 15 * 2, "Mp", 0xFFFFFF);
		//mpのゲージを描画
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

	//チュトリアルのキャラpos設定
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
			OutputDebugString("playmove エラー!!\n");
		}
	}

}

VOID Player::PlayerUiShow() {


	  



}

