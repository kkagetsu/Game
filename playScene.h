#pragma once
#include "Dxlib.h"

#define GRID__WIDTH  (20)
#define GRID_HEIGHT  (12)
#define MASU___SIZE  (40)
#define TUTORIAL     (1)


typedef enum 
{
	LAYOUT_GRASS	  //草
,   LAYOUT_GRASS_SP   //草SP
,	LAYOUT_VILLAGE	  //村
,	LAYOUT_STONE	  //岩
,	LAYOUT_DRIVE	  //川
,	LAYOUT_FOREST	  //森
,	LAYOUT_WALL	      //壁
,	LAYOUT_BRIDGE	  //橋
	
,	LAYOUT_PLAYER =10 //プレイヤー
,	LAYOUT_ENEMY      //敵
,   LAYOUT_COUNT
,   LAYOUT_INVALID = -1
,   LAYOUT_BEGIN
	
} E_LAYOUT_T;


//CSVファイルを読み込んで
// その配列を使って描写した方が分かりやすい
// フィールド　レイアウト
static E_LAYOUT_T g_layout[GRID_HEIGHT][GRID__WIDTH] = {
	{ LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_DRIVE,LAYOUT_DRIVE,
	  LAYOUT_DRIVE,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS }, //0
	{ LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_DRIVE,LAYOUT_DRIVE,
	  LAYOUT_DRIVE,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS }, //1
	{ LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_DRIVE,LAYOUT_DRIVE,
	  LAYOUT_DRIVE,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS }, //2
	{ LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_DRIVE,LAYOUT_DRIVE,
	  LAYOUT_DRIVE,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS }, //3
    { LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_DRIVE,LAYOUT_DRIVE,
	  LAYOUT_DRIVE,LAYOUT_FOREST,LAYOUT_FOREST,LAYOUT_FOREST,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS }, //4
	{ LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_STONE,LAYOUT_BRIDGE,LAYOUT_BRIDGE,
	  LAYOUT_BRIDGE,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS}, //5
	{ LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_DRIVE,LAYOUT_DRIVE,
	  LAYOUT_DRIVE,LAYOUT_FOREST,LAYOUT_FOREST,LAYOUT_FOREST,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS }, //6
    { LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_DRIVE,LAYOUT_DRIVE,
	  LAYOUT_DRIVE,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_FOREST,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS }, //7
	{ LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_DRIVE,LAYOUT_DRIVE,
	  LAYOUT_DRIVE,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_WALL,LAYOUT_WALL,LAYOUT_WALL }, // 8 
	{ LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_DRIVE,LAYOUT_DRIVE,
	  LAYOUT_DRIVE,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_WALL,LAYOUT_VILLAGE,LAYOUT_WALL }, // 9
	{ LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_DRIVE,LAYOUT_DRIVE,
	  LAYOUT_DRIVE,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_WALL,LAYOUT_GRASS,LAYOUT_WALL }, // 10
	{ LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_DRIVE,LAYOUT_DRIVE,
	 LAYOUT_DRIVE,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_FOREST,LAYOUT_GRASS,LAYOUT_GRASS,LAYOUT_GRASS }, //11
};

//プレイの初期化
extern VOID PlaySceneInit();
//シナリオ描画
extern VOID ScenarioDraw();
//フィールドの線を描く
extern VOID FieldLineDraw();
//フィールドの背景を描く
extern VOID FieldLaOutDraw();

extern VOID CursorDraw();