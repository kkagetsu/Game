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
	int agi;                //素早さ
	int luc;			    //運
	int move;               //移動力
	int grHandle[COUNT__E];
	int grHandleUI[PLAYER_UI_COUNT];
	int posx, posy;

public:

	Player(); //プレイヤーの初期化
	VOID GraphicLoad();

	VOID StatusShow();
	
	VOID PlayerPosInit();

	VOID PlayerMove();

	VOID PlayerUiShow();

	// gtp ゲッターメソッド
	inline int getPosX() const { return posx; } //inline化
	inline int getPosY() const { return posy; }	//inline化
}; 
