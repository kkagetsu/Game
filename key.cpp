#include "key.h"

//グローバル変数

//現在のキーを押しているフレーム数
int NowKeyPressFrame[KEYKINDMAX];
//一つ前のキーキーを押しているフレーム数
int OldKeyPressFrame[KEYKINDMAX];

//関数

 //キー処理の初期化
VOID KeyInit( ) {

	for (int i = 0; i < KEYKINDMAX; i++) {

		NowKeyPressFrame[i] = 0;
		OldKeyPressFrame[i] = 0;

	}
	return;
}

 //キー処理の更新

VOID KeyUpdata() {

	char KeyState[KEYKINDMAX];

	//すべてのキー情報を一度取得
	GetHitKeyStateAll(KeyState);

	//キーの情報を更新
	for (int i = 0; i < KEYKINDMAX; i++) {

		//一つ前のキー入力を保存
		OldKeyPressFrame[i] = NowKeyPressFrame[i];

		//現在、キーが押されているとき
		if (KeyState[i] > 0) {

			//押されているフレーム数をカウントアップ
			NowKeyPressFrame[i]++;

		}
		else if (KeyState[i] == 0) {
			//押されていない
			NowKeyPressFrame[i] = 0;
		}
	}
	return;
}

//特定のキーを押したか
BOOL KeyDown(int KEY_INPUT_) {

	
	//現在押されいてキーのフレーム数が0よりも上なら
	if (NowKeyPressFrame[KEY_INPUT_] > 0) {

		return TRUE;

	}

	return FALSE;
}

//特定のキーをクリックしたか?
//引数：DXライブラリのキーコード（KEY_INPUT_で始まるマクロ定義）
//説明:「キーを押す→キーをあげる」で行われたときが、キリック
BOOL KeyClick(int KEY_INPUT_) {
	//現在押されいてキーのフレーム数が0よりも上なら
	//一つ前のキーはおされていたとき
	if (NowKeyPressFrame[KEY_INPUT_] == 0 
        &&OldKeyPressFrame[KEY_INPUT_]>0)
	{

		return TRUE;

	}

	return FALSE;



}
//特定のキーを押したフレーム数
//引数:DXライブライのキーコード（KET_INPUT_で始まるマクロ定義）
//注意:戻り値はミリ秒などではなく，フレーム数!
int KeyPressFrame(int KEY_INPUT_) {

	return NowKeyPressFrame[KEY_INPUT_];
}