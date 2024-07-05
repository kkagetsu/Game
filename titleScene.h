#pragma once

#include "Dxlib.h"

//タイトル画面用の選択肢
//タイトルシーンのメッセージ描画
/*
  タイトル名
  選択肢　　 GAME START ゲーム画面へ（タイトル画面→loading 中画面→ゲーム画面）
  　         LOAD GAME　　
	 　　    OPTION   BGM サイズ

		　　04//11  start
*/


typedef enum tagE_TITLEMENU   //メニューの構造体
{
	NEW_GAME, //ゲーム開始   0
	LOAD_GAME,//ゲームロード 1
	OPITION,//設定           2

	MENU_NUM//カウンター　　 3

} E_TITLEMENU;


static int nowSelect = NEW_GAME; //現在の選択がゲーム開始


extern VOID TitleMenuInit();//メニューの初期化

extern VOID BackGroundDraw();//タイトルの背景画像を描画

//関数せず　そのまま使う　　廃棄
//extern VOID BackGroundMessageDraw();//タイトル背景メッセージを描画

extern VOID TitleMenuUpdate();//メニュー選択の処理

extern VOID TitleMenuDraw();//メニュー内容の描画
