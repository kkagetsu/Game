//ゲーム処理のソースファイル

//ヘッダファイルを書き込む
#include "gameManager.h"
#include "Key.h"
#include "titleScene.h"
#include "playScene.h"


//グローバル変数

enum tagE_GAME_SCENE nowGameScene;//現在のゲームシーン

//ゲームシーンの名前

char GameSceneName[GAME_SCENE_COUNT][GAME_SCENE_NAME_MAX]{

	"タイトル画面"
	,"ゲーム画面"
	,"エンディング画面"

};

//関数

//タイトル初期化 
VOID  TitleInit() {
	if (GAME_DEBUG == TRUE) {
		DrawFormatString(WINDOW_WIDTH - 200, 0, GetColor(255, 255, 255),
			"%s%s", GameSceneName[nowGameScene], "初期化");

	}

	FLAG_GAME_SCENE == 0;



	return;
}

//タイトル管理
VOID TitleCtrl() {
	TitleProc(); //処理をしてから
	TitleDraw(); //描画する
	return;
}
//タイトル処理
VOID TitleProc() {

	TitleMenuUpdate();
	//タイトルシーンからプレイヤーシーンに
	if (KeyClick(KEY_INPUT_RETURN) == TRUE && FLAG_GAME_SCENE == TRUE) { //エンターキーが押されてかつgame start(flag) 1　それ以外は0
		
		PlayInit(); //プレイーシーンを初期化

		//シーン切り替え
		nowGameScene = PLAY_SCENE;
		
		return;
	}
	return;
}
//タイトル描画
VOID TitleDraw() {
	if (GAME_DEBUG == TRUE) {
		DrawFormatString(WINDOW_WIDTH - 200, 0, GetColor(255, 255, 255),
			"%s%s", GameSceneName[nowGameScene], "描画中");

	}
	BackGroundDraw();  //ゲームタイトル最初の背景画像を描画
	TitleMenuDraw();   //もし左クリックまたはspaceキーを押したら　
	                   //タイトル画面のメニュー選択に移す
	return;
}


//ゲーム中初期化
VOID PlayInit() {
	
	if (GAME_DEBUG == TRUE) {
		DrawFormatString(WINDOW_WIDTH - 200, 0, GetColor(255, 255, 255),
			"%s%s", GameSceneName[nowGameScene], "初期化");

	}
	return;
}
//ゲーム中管理
VOID PlayCtrl() {
	PlayProc(); //処理をしてから
	PlayDraw(); //描画する
	
	return;
}
//ゲーム中処理
VOID PlayProc() {


	//ゲームクリアシーンに切り替え
	if (KeyClick(KEY_INPUT_RETURN) == TRUE && SHOW_ENDING ==TRUE) 
	{

		//エンターキーが押された時 
		//プレイーシを初期化
		EndInit();

		//シーン切り替え
		nowGameScene = END_SCENE;

		return;
	}
	//ゲームオーバーシーンに切り替え
	if (KeyClick(KEY_INPUT_RETURN) == TRUE&&SHOW_GAME_OVER == TRUE)
	{

		//エンターキーが押された時 
		//プレイーシを初期化
		EndInit();

		//シーン切り替え
		nowGameScene = END_SCENE;

		return;
	}
	return;
	
}
//ゲーム中描画
VOID PlayDraw(){
	if (GAME_DEBUG == TRUE) 
	{
		DrawFormatString(WINDOW_WIDTH - 200, 0, GetColor(255, 255, 255),
			"%s%s", GameSceneName[nowGameScene], "描画中");

	}
	return;
}


//エンディング初期化
VOID EndInit(){
	if (GAME_DEBUG == TRUE) {
		DrawFormatString(WINDOW_WIDTH - 200, 0, GetColor(255, 255, 255),
			"%s%s", GameSceneName[nowGameScene], "初期化");
		SHOW_ENDING    == 0;
		SHOW_GAME_OVER == 0;
	}
	return;
}
//エンディング管理
VOID EndCtrl(){
	EndProc(); //処理をしてから
	EndDraw(); //描画する

	return;
}
//エンディング処理
VOID EndProc(){
	//シーン切り替え
	if (KeyClick(KEY_INPUT_RETURN) == TRUE) {

		//エンターキーが押された時 
		//プレイーシを初期化
		TitleInit();

		//シーン切り替え
		nowGameScene = TITLE_SCENE;

		return;
	}
	return;
}
//エンディング描画
VOID EndDraw(){
	if (GAME_DEBUG == TRUE) {
		DrawFormatString(WINDOW_WIDTH - 200, 0, GetColor(255, 255, 255),
			"%s%s", GameSceneName[nowGameScene], "描画中");

	}
	return;
}