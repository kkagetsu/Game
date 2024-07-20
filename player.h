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
	int mdf;                //魔法防御力
	int agi;                //素早さ
	int luc;			    //運
	int move;               //移動力
	int action;             //行動　攻撃　２　移動１　item　２　スキル　２　action < = 0　行動終了


	int grHandle[COUNT__E]; //player１のたち絵
	int grHandleUI[PLAYER_UI_E_COUNT];//player１のUI
	int posx, posy;         //座標
	const int pUIMessageX = 730;   //プレイヤのUI情報の文字表示座標
	const int pUIMessageY = 500;	//プレイヤのUI情報の文字表示座標
	tagE_PLAYER_ACTION arPlayerAction;

public:

	Player(); //プレイヤーの初期化
	VOID GraphicLoad();//player1が使う絵をすべてここでロードする

	VOID StatusShow();//プレイヤのUI描画はすべてこの関数の中　ステータス画面　+ コマンド指令画面(PlayerUiShow)
	
	VOID PlayerPosInit();//プレイヤ１の生成場合を指定（初期化）

	VOID PlayerPos();//プレイヤのい居場所を描画

	VOID PlayerUiShow();//コマンド指令画面を描画
	VOID PlayerMoveMessage();//キー提示
	VOID PlayerAbleMove();//移動範囲展開の描画
	VOID PlayerAttackMessage();//キー提示
	VOID PlayerItemMessage();//キー提示
	VOID PlayerWaitMessage();//キー提示
	//VOID PlayerAction();//プレイヤの
	VOID PlayerUiUpdata();
	unsigned int GetFlashingColor(int time);

	//  ゲッタ-座標
	inline int getPosX() const { return posx; } //inline化
	inline int getPosY() const { return posy; }	//inline化
	inline int getMove() const { return move; }	//inline化

	VOID setPosX(int x) { this->posx = x; }
	VOID setPosY(int y) { this->posy = y; }

}; 
