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
	//メンバー変数なので　前にm_を付けましょう 
private:
	char name[20];          //名前
	char job[10];		    //職業
	char speSkill[10];      //特性
	char jobSkill[3][10];   //スキル
	int level;			    //レベル
	int exp;                //経験値
	int hp;				    //体力
	int mp;				    //魔力
	int pow;			    //力
	int def;			    //防御力
	int dex;			    //命中　命中率じゃない
	int lnt;			    //知力
	int mdf;			    //魔法防御力
	int agi;			    //素早さ
	int luc;			    //運
	int move;               //移動力
	int grHandle[COUNT__E];
	int posx, posy;

public:

	Player(); //プレイヤーの初期化
	VOID GraphicLoad();

	VOID StatusShow();
	
	VOID PlayerPosInit();

	VOID PlayerMove();

	VOID PlayerUiShow();

	// gtp ゲッターメソッド
	int getPosX() const { return posx; }
	int getPosY() const { return posy; }
}; 
