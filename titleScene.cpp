#include "titleScene.h"
#include "key.h"
#include "gameManager.h"
#include "playScene.h"
//#include "Timer.h"
BOOL isLClickOrSpace;//左クリックかスペースが押されたら　1
float newGameY;  //　ゲーム開始文字のy位置
float loadGameY; //　ゲームロードのy位置
float opitionY;  //　ゲーム設定のy位置
int cursorY;     //  カーソル移動の上下情報
int gHandle;     //  バックグラウンド画面の保存場所
int cursorHandle;//　メニュー選択用カーソル
LONGLONG titleLastMoveTime = 0; //  最後に移動した時刻を記録する変数
const LONGLONG titleMoveInterval = 200000;  //   移動のタイミングを制御するための間隔（マイクロ秒）

//メニューの初期化
void TitleMenuInit( ) {
	
	isLClickOrSpace = FALSE;
    newGameY  = WINDOW_HEIGHT / 1.4f - MASU___SIZE*3; //　ゲーム開始文字のy位置
    loadGameY = WINDOW_HEIGHT / 1.4f - MASU___SIZE*2; //　ゲームロードのy位置
    opitionY  = WINDOW_HEIGHT / 1.4f - MASU___SIZE*1; //　ゲーム設定のy位置
	cursorY = 0;

	//先ずは画像を読み込む
	gHandle = LoadGraph("picture/RpgTitle.jpg");
	cursorHandle = LoadGraph("picture/yajirushi_right.png");


	return;
}

//タイトルシーンの描画
void BackGroundDraw( ) {

	//背景画像を描画
	DrawGraph(0, 0, gHandle, TRUE);
	

	
	// 読み込んだ画像のグラフィックハンドルを削除
	//最後の解放部分に入れた方がベスト
//	DeleteGraph(gHandle);

	return;
}

//タイトルメニュー選択制御の処理部分
void TitleMenuUpdate( ) 
{

	LONGLONG currentTime = GetNowHiPerformanceCount();  //  現在の時刻を取得

	if (currentTime - titleLastMoveTime > titleMoveInterval) { //現在の時間　-　過去の時間　＞　自分が設定した時間の場合
		if (KeyDown(KEY_INPUT_DOWN) == 1)  //↓のキーが押されていたら
		{
			nowSelect = (nowSelect + 1) % MENU_NUM; //選択肢が一つ↓に

			titleLastMoveTime = currentTime; // 先の現在時間は　過去の時間に代入
		}
		if (KeyDown(KEY_INPUT_UP) == 1)  //↑のキーが押されていたら
		{
			nowSelect = (nowSelect + (MENU_NUM - 1)) % MENU_NUM; //選択肢が一つ↑に

			titleLastMoveTime = currentTime; // 先の現在時間は　過去の時間に代入
		}
		if (KeyDown(KEY_INPUT_RETURN) == 1)  //エンターキのキーが押されていたら
		{   //パターン検査
			switch (nowSelect) {

			case NEW_GAME:  //new gameの場合　シーン切り替えします　title →　playに
				FLAG_GAME_SCENE == 1;
				nowGameScene = PLAY_SCENE;
				break;


			case LOAD_GAME:   //未実装
				break;


			case OPITION:     //未実装
				break;
			}

		}
	}
	return;
}

	//メニュー画面の描写
void TitleMenuDraw( )
{   //もし左クリックまたはspaceキーを押したら　
	if (KeyDown(KEY_INPUT_SPACE) || GetMouseInput() & MOUSE_INPUT_LEFT)	isLClickOrSpace = TRUE;
	

	if (isLClickOrSpace == TRUE)
	{   //タイトル画面の真中しのところに描画する
		int drawStringX = WINDOW_WIDTH / 2 - 50;                    //800/2-50=350
		DrawString(drawStringX, newGameY, "New Game", 0xFFFFFF);    //new game
		DrawString(drawStringX, loadGameY, "Load Game", 0xFFFFFF);	//load gamen
		DrawString(drawStringX, opitionY, "Opition", 0xFFFFFF);		//opition
		DrawString(1, WINDOW_HEIGHT - 15,
			"Please use the ↑↓←→ key to control , Enter key to decide on an option",
			0x00FF00);                                              //操作説明

		  
	                     
		DrawExtendGraph(drawStringX-MASU___SIZE*2, cursorY-10, 
			            drawStringX - MASU___SIZE, cursorY-10 + MASU___SIZE ,
			            cursorHandle, TRUE);                        //タイトルメニュー選択カーソルを描画
	} 
	//左クリックまたはspaceキーを押してない場合、操作説明を描画
	else {
		(DrawString(WINDOW_WIDTH / 3, WINDOW_HEIGHT - WINDOW_HEIGHT / 4,
			"スペースキーまたは\n左クリックしてください", GetColor(255, 0, 0)));
	}
	switch (nowSelect) {

	case NEW_GAME:
		cursorY = newGameY;
	
		break;


	case LOAD_GAME:
		cursorY = loadGameY;

		break;


	case OPITION:
		cursorY = opitionY;
		
		break;
	}


	return;
}




