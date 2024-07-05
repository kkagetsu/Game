#pragma once

#include "Dxlib.h"

//マクロ定義
#define KEYKINDMAX 256 //キーの種類

//外部のプロトタイプ宣言
extern VOID KeyInit( );              //キー処理の初期化
extern VOID KeyUpdata( );            //キー処理の更新
extern BOOL KeyDown(int KEY_INPUT_);    //特定のキーを押したか
extern BOOL KeyClick(int KEY_INPUT_); 	//特定のキーをクリックしたか
extern int KeyPressFrame(int KEY_INPUT);//特定のキーを押したフレーム数


