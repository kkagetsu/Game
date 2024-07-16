#define _CRT_SECURE_NO_WARNINGS
#include "player.h"
#include "playScene.h"
#include "gameManager.h"

Player::Player() {

	strcpy(this->name, "コウタロウ");
	strcpy(this->job,"剣士");
	strcpy(this->speSkill,"一匹狼");
	strcpy(this->jobSkill[0], "双連撃");
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
	this->move = 3;   //移動量
	this->posx = 0;
	this->posy = 0;
	

	memset(grHandle, NULL, sizeof(grHandle)); //画像のloadと画像を格納用の変数を分けてそれぞれ初期化する ここではゼロクリア
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
	DrawFormatString(200 + 15 * 4, 490, 0xFFFFFF, "Lv  %d",level );
	//p_exp
	DrawFormatString(300 + 15 * 4, 490, 0xFFFFFF,"exp %d", exp);

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


	PlayerUiShow();
}

VOID Player::PlayerPosInit() {

	//チュトリアルのキャラpos設定
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
			OutputDebugString("playMove エラー!!\n");
		}
	}

}

VOID Player::PlayerUiShow() {
	//┃┃┃┃┃縦線
	for (int i = 0; i <= 4; i++) {
		DrawLine(560+i* MASU___SIZE, GRID_HEIGHT * MASU___SIZE, 
			     560+i* MASU___SIZE, WINDOW_HEIGHT, 0xFF0000);
	}
	//横線
	for (int j = 0; j <= 3; j++) {
		DrawLine(560 , GRID_HEIGHT * MASU___SIZE + MASU___SIZE + j * MASU___SIZE,
			560 + 4 * MASU___SIZE, GRID_HEIGHT * MASU___SIZE + MASU___SIZE + j * MASU___SIZE, 0xFF0000);
	}



		//x560y480 x560+40 y480+40
	//移動アイコン
	//int moveGraphic = DrawExtendGraph(560 + 2, GRID_HEIGHT * MASU___SIZE + 2,
	//	                        600 - 2, GRID_HEIGHT * MASU___SIZE+ MASU___SIZE - 2, grHandleUI[MOVE_E], TRUE);
	//if (moveGraphic == -1)
	//{
	//	OutputDebugString("moveG エラー!!\n");
	//}
	for (int i = 0; i <= PLAYER_UI_COUNT-4; i++) {

		// 0移動アイコン 1攻撃　2アイテム　3待機
		DrawExtendGraph(560 + i*MASU___SIZE + 2, GRID_HEIGHT * MASU___SIZE + 2,
			600 + i * MASU___SIZE  - 2, GRID_HEIGHT * MASU___SIZE + MASU___SIZE - 2, grHandleUI[i], TRUE);




	}
	  //特性
	    DrawExtendGraph(560 + 1 * MASU___SIZE + 2, GRID_HEIGHT * MASU___SIZE+ MASU___SIZE + 2,
		600 + 1 * MASU___SIZE - 2, GRID_HEIGHT * MASU___SIZE + 2*MASU___SIZE - 2, grHandleUI[SPSKILL_E], TRUE);

      //スキルアップ
		DrawExtendGraph(560 + 3 * MASU___SIZE + 2, GRID_HEIGHT * MASU___SIZE + MASU___SIZE + 2,
			600 + 3 * MASU___SIZE - 2, GRID_HEIGHT * MASU___SIZE + 2 * MASU___SIZE - 2, grHandleUI[LEARNSKILL_E], TRUE);

	 //スキル１
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
			if (abs(dx) + abs(dy) <= move) { // ダイヤモンド形の範囲内かをチェック
				int x = posx + dx;
				int y = posy + dy;

			// マップ範囲内かどうかをチェック
				if (x >= 0 && x < GRID__WIDTH && y >= 0 && y < GRID_HEIGHT) {
					// マスの中心を計算
					int drawX1 = x * MASU___SIZE;
					int drawY1 = y * MASU___SIZE;
					int drawX2 = drawX1 + MASU___SIZE;
					int drawY2 = drawY1 + MASU___SIZE;
					// 描画ブレンドモードを設定 (透明度設定)
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); // 128は透明度の値 (0: 完全透明, 255: 完全不透明)
					DrawBox(drawX1, drawY1, drawX2, drawY2, 0x0000ff, TRUE); // 蒼色の枠線で描画
					// 描画ブレンドモードを元に戻す
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

	//移動


	//通常攻撃　デバッグ対象がない為最後で作る

	//アイテム

	//待機　プレイヤの最大20%のHPと15%MPを回復する

	//特性　パッシブスキル 効果紹介だけ　一匹狼：自分の１マスに味方がない場合　ステータス＋２

	/*スキル レベルアップごとにスキルポイントが貰える　
	スキル１　双連撃　対象に連撃の二回通常攻撃する　命中率75％/77.5%/80%/85%
	命中率判定し　missの場合　当キャラの攻撃ターンを終了と見なす
	命中の場合　通常攻撃の２回 Critical strikeを判定し
	Critical strike判定成功　通常ダメージの1.5/1.65/1.8/2.0を対象に与える
	MP消耗　７/9/11/9
	冷却時間（cd）3T/3T/3T/2T
	取得可能のキャラのレベル　0/2/4/6 
	　
	*/

}

