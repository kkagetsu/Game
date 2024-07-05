#pragma once

#include "DxLib.h"


//マクロ定義
#define GameFPS 60 //設定したいFPS

#define MicroSecond 1000000.0f//１マイクロ秒　
#define MillSecond  1000.0f	  //１ミリ秒
#define WaitTImeMill 3000	  //最大待てるミリ数


typedef struct  _FPS{
	LONGLONG FirstTakeTime = 0;   //１フレーム目の計測時間
	LONGLONG NowTakeTime = 0;	  //現在の計測時間
	LONGLONG OldTakeTime = 0;	  //以前の計測時間
								  
	float Deltatime = 0.000001f;  //デルタタイム（経過時間）
	int FrameConut = 1;			  //現在のフレーム数（１フレーム目～MAXフレーム目まで）
	float Average = 0.0f;		  //平均FPS値

}FPS;

//外部グローバル変数
extern FPS g_pfs;

//外部プロトタイプ宣言
extern VOID FPSInit();  //FPS初期化
extern VOID FPSCheck(); //FPS計測
extern VOID FPSDraw();	 //FPS描画
extern VOID FPSWait();	 //FPS待機
