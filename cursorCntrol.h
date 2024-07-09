#pragma once

#include "DxLib.h"
#include "player.h"
class Cursor {

public:
	int x1;
	int x2;
	int y1;
	int y2;
	int color;
	char key[256];
	
	LONGLONG lastMoveTime;  //by gtp 最後に移動した時刻を記録する変数


	bool isBlink;  // gtp点滅効果のための表示フラグ
	LONGLONG lastBlinkTime;  // gtp最後に点滅した時刻
	const LONGLONG blink = 800000;//gtp点滅間隔

	bool isPlayerSelected; //by gtp プレイヤーが選択されているかを示すフラグ

	Player& player; // /by gtp プレイヤーの参照

	Cursor(Player& player);
	VOID CursorControl( );
	VOID CursorDraw();
	VOID MapInfoShow();
	/****************************************************************************
関数名：IsPlayerAction
機能  : 指定されたプレイヤーは今動作できるか（条件：プレイヤーのターン　そして当プレイヤーが未行動）
引数　：cx  int  (in)   カーソルの位置（ｘ座標）
　　　　cy  int  (in)   カーソルの位置（ｙ座標）
		E_TURN_T (in)   現在のプレイヤー　0:TURN_PLAYER / 1:TURN_ENEMY
返却値:	TRUN_NONE	: コマを置くことはできない
		TRUN_PLAYER	: 黒のコマを置いてよい
		TRUN_ENEMY	: 白のコマを置いてよい
*****************************************************************************/


	


};

