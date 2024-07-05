//ゲーム処理用のヘッダーファイル

#pragma once

#include "DxLib.h"

#define WINDOW_WIDTH         (800) //横
#define WINDOW_HEIGHT        (600) //縦
#define WINDOW_BIT           (32)  //カラービット数
						     	   
#define ONE_SIZE             (40)  //マスのサイズ　
#define HEIGHT_SQUARE_CNT    (20)  //横　
#define WIDTHSQUARE_CNT      (15)  //縦
#define SQUARE_CNT           (300) // マスの数.  横２０　縦１５
#define BOARD_SIZE           (ONE_SIZE*SQUARE_CNT)//描画する盤面の縦横サイズ.
						     
						     
#define GAME_DEBUG           TRUE  //デバッグモード   

#define GAME_SCENE_COUNT     (4)   //ゲームシーンの数
#define GAME_SCENE_NAME_MAX  (25)  //ゲームシーン名の文字数MAX
#define FLAG_GAME_SCENE      (0)   //１の場合ゲームシーンに入れる以外の場合入れない
#define SHOW_ENDING          (0)   //ゲームクリアごとに呼び出す　
#define SHOW_GAME_OVER       (0)   //ゲームオーバー時呼び出す

//列挙型

//切り替え用のシーン
enum tagE_GAME_SCENE {

	TITLE_SCENE,    //タイトルシーン
	PLAY_SCENE,     //ゲームシーン
	END_SCENE,      //エンドシーン

};

//外部のグローバル変数

extern enum tagE_GAME_SCENE nowGameScene;//現在のゲームシーン

 

//外部プロトタイプ宣言

extern VOID TitleInit();//タイトル初期化
extern VOID TitleCtrl();//タイトル管理
extern VOID TitleProc();//タイトル処理
extern VOID TitleDraw();//タイトル描画

extern VOID LoadInit();//ロード中初期
extern VOID LoadCtrl();//ロード中管理
extern VOID LoadProc();//ロード中処理
extern VOID LoadDraw();//ロード中描画



extern VOID PlayInit();//ゲーム中初期化
extern VOID PlayCtrl();//ゲーム中管理
extern VOID PlayProc();//ゲーム中処理
extern VOID PlayDraw();//ゲーム中描画
 
extern VOID EndInit();//エンディング初期化
extern VOID EndCtrl();//エンディング管理
extern VOID EndProc();//エンディング処理
extern VOID EndDraw();//エンディング描画