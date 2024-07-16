#pragma once

#include "DxLib.h"
#include "player.h"
class Cursor {

public:
	int x1;       //カーソルの左上のｘ座標
	int x2;       //カーソルの左上のｙ座標
	int y1;       //カーソルの右下のｘ座標
	int y2;       //カーソルの右下のｙ座標

	int playerX1; //playerUIカーソルの左上のｘ座標
	int playerY1; //playerUIカーソルの左上のｙ座標
	int playerX2; //playerUIカーソルの右下のｘ座標
	int playerY2; //playerUIカーソルの右下のｙ座標

	int color;
	char key[256];
	

	LONGLONG lastMoveTime;  //by gtp 最後に移動した時刻を記録する変数
	LONGLONG lastBlinkTime;  // gtp最後に点滅した時刻
	const LONGLONG blink = 800000;//gtp点滅間隔

	BOOL isPlayerUICursor;//プレイヤUIカーソルの出現／消失
	BOOL isMapCursor;//マップカーソルの出現／消失
	BOOL isBlink;  // gtp点滅効果のための表示フラグ
	BOOL isPlayerSelected; //by gtp プレイヤーが選択されているかを示すフラグ
	BOOL isPlayerMoveShow; //プレイヤーのMove2表示状態フラグ

	Player& player; // /by gtp プレイヤーの参照

	E_PLAYER_UI_T playerUI_Is;//playerUI今はどいう状態なのかの列挙体宣言

	Cursor(Player& player);
	VOID CursorControl();//カーソル制御
	VOID CursorDraw();    //マップカーソル描画
	VOID MapInfoShow();   //マップ上の地形情報を表示

	VOID PlayerUIControl(); //プレイヤUIカーソル制御
	VOID PlayerUICursorDraw();    //playerUIカーソル描画
	VOID Switching();//マップ選択からプレイヤ　プレイヤからマップ
	VOID DrawMoveRange();

};

