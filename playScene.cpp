#define _CRT_SECURE_NO_WARNINGS
#include "playScene.h"
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#define COLUMN_COUNT (256)//一行ごとのバファ
#define COLUMN        (20) //行数

int fieldGraph[6]  ;
int GHandleGrass   ;
int GHandleForest  ;
int GHandleVillage ;
int GHandleWall    ;
int GHandleStone   ;
int GHandleBridge  ;
int GHandleDrive   ;
extern BOOL isScenario    ;

char buff[256][COLUMN_COUNT] = { 0 }; // シナリオを格納するバッファ
int lineCount = 0;                    // 読み込んだ行数

//extern BOOL g_isSnOrBF    ;//シナリオなのかバトルフィールド

//char buff[20][COLUMN_COUNT]     ;//シナリオを格納するバッファ

VOID PlaySceneInit() {

	
	GHandleGrass   = LoadGraph("picture/maptile_sogen_02.png");
	GHandleForest  = LoadGraph("picture/ki_02_01.png");
	GHandleVillage = LoadGraph("picture/ie_front_01_red.png");
	GHandleWall    = LoadGraph("picture/maptile_ganpeki_brown.png");
	GHandleStone   = LoadGraph("picture/iwa_02.png");
	GHandleBridge  = LoadGraph("picture/bridge_side_brown.png");
	GHandleDrive   = LoadGraph("picture/maptile_umi_02.png");

	fieldGraph[0] = GHandleGrass;
	fieldGraph[1] = GHandleVillage;
	fieldGraph[2] = GHandleWall;
	fieldGraph[3] = GHandleStone;
	fieldGraph[4] = GHandleBridge;
	fieldGraph[5] = GHandleDrive;
	
	isScenario = true;

	//FILE* fp = NULL; //ファイル操作の準備 ファイルポインタ変数
	//fp = fopen("scenario.txt", "r"); //textをオープンします
	//if (fp == NULL) {
	//
	//	OutputDebugString("scenario.bin is not opened. abort\n");
	//}
	//int i = 0;
	//while (fgets(buff[i], COLUMN_COUNT, fp) != NULL) {
	//	//一行づつbuffに書き込む
	//	i++;
	//	
	//}
	//fclose(fp); //書き込む語ファイルcloseします
	//fp = NULL; //fpポインタをリセット
	 // ファイル操作の準備
	FILE* fp = fopen("scenario.txt", "r"); // テキストファイルをオープン
	if (fp == NULL) {
		OutputDebugString("scenario.txt is not opened. abort\n");
		return;
	}

	while (fgets(buff[lineCount], COLUMN_COUNT, fp) != NULL) {
		lineCount++;
	}
	fclose(fp); // 書き込み後ファイルをクローズ

	return;
}


/*
試行錯誤v1.0　マルチスレッド
bool isLoaded = false;
//std::mutex isLoadedMutex;

void SetLockFlag(bool _)
{
//	std::lock_guard<std::mutex>  lock(isLoadedMutex);
	isLoaded = true;
}

bool GetLockFlag()
{
//	std::lock_guard<std::mutex>  lock(isLoadedMutex);
	return isLoaded;
}


//スレッド 
void AsyncLoad()
{

	while (1) {
		// リクエストを確認.
		if () {
//			LoadFile();
			GHandleGrass = LoadGraph("picture/maptile_sogen_02.png");
			GHandleForest = LoadGraph("picture/ki_02_01.png");
			GHandleVillage = LoadGraph("picture/ie_front_01_red.png");
			GHandleWall = LoadGraph("picture/maptile_ganpeki_brown.png");
			GHandleStone = LoadGraph("picture/iwa_02.png");
			GHandleBridge = LoadGraph("picture/bridge_side_brown.png");
			GHandleDrive = LoadGraph("picture/maptile_umi_02.png");
		}


		//ダミーで10秒待つ
		auto sleepTime = std::chrono::seconds(10);
		std::this_thread::sleep_for(sleepTime);

		SetLockFlag(true);
	}
}

//loading 画面  std::thread 読み込みの実行はすべて裏画面で
//ここではthread中の関数は　画面の読み込み,音楽の読み込み（暫定）、
BOOL isLoading(BOOL load) {

	std::thread th(AsyncLoad);

	

	//現時点の読み込みが一瞬で終わるからsleepで時間を稼ぎ
	std::this_thread::sleep_for(std::chrono::seconds(5));


}

*/


//VOID ScenarioDraw() {
//	    
//
//		int span = 0;      //行間隔
//		const int x = 80;  //テキスト先頭　X
//		const int y = 80 ; //テキスト先頭　Y
//		
//		for (int i = 0; i < COLUMN; i++) {
//		
//			DrawString(x, y + span, buff[i], 0xFFFFFF);
//		
//			span += 30;
//		}
//	}
VOID ScenarioDraw() {
	static int totalLength = 0; // すべての文字の総数
	static char displayStr[256 * COLUMN_COUNT] = ""; // 表示する文字列
	static int t = 0;
	static int tmax = 20;
	static int currentPos = 0; // 現在の文字位置
	static bool messageDisplayed = false; // メッセージが完全に表示されたかどうかのフラグ

	if (totalLength == 0) {
		for (int i = 0; i < lineCount; i++) {
			totalLength += strlen(buff[i]);
		}
	}

	t++;
	if (t > tmax && !messageDisplayed) {
		if (currentPos < totalLength) {
			int line = 0;
			int pos = currentPos;
			while (pos >= strlen(buff[line])) {
				pos -= strlen(buff[line]);
				line++;
			}
			displayStr[currentPos] = buff[line][pos];
			currentPos++;
			displayStr[currentPos] = '\0';
		}
		else {
			messageDisplayed = true; // メッセージが完全に表示された
		}
		t = 0;
	}

	// 画面クリア
	ClearDrawScreen();

	// 文字列を描画
	DrawString(100, 100, displayStr, 0xffffff); // メッセージを描画

	if (messageDisplayed ==TRUE) {



		DrawString(100, 150, "終了", 0xffffff); // メッセージが表示された後に終了を描画
	}
	// Zキーが押されたら再生速度二倍になる
	if (CheckHitKey(KEY_INPUT_Z) == 1) {
		tmax = 1;
	}
	// Sキーが押されたら文字描画が一気に終わる
	if (CheckHitKey(KEY_INPUT_S) == 1 && !messageDisplayed) {
		while (currentPos < totalLength) {
			int line = 0;
			int pos = currentPos;
			while (pos >= strlen(buff[line])) {
				pos -= strlen(buff[line]);
				line++;
			}
			displayStr[currentPos] = buff[line][pos];
			currentPos++;
			displayStr[currentPos] = '\0';
		}
		messageDisplayed = true;
	}
}




VOID FieldLineDraw() {
	
	//縦線を描く
	for (int i = 0; i <= GRID_HEIGHT; i++) {
		
		DrawLine(0, MASU___SIZE * i, 800, MASU___SIZE * i, GetColor(255, 0, 0));

	}
	//横線を描く
	for (int j = 0; j <= GRID__WIDTH; j++) {

		DrawLine(MASU___SIZE * j,0, MASU___SIZE * j ,480, GetColor(255, 0, 0));

	}
	//int GHandle_Grass = LoadGraph("maptile_sogen_02.png");
	//DrawExtendGraph(0,0,40,40, GHandle_Grass, TRUE);
	//DrawExtendGraph(0,0,40,40, GHandle_Grass, TRUE);


}

VOID FieldLaOutDraw() {

	FieldLineDraw();
	//この部分要修正　switch文に変更する
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	for (int x = 0; x < GRID_HEIGHT; x++) {

		for (int y = 0; y <= GRID__WIDTH; y++) {

			//if (g_layout[x][y] == LAYOUT_GRASS) {
			//
			//	DrawExtendGraph(MASU___SIZE * y, MASU___SIZE * x, MASU___SIZE+ MASU___SIZE * y, MASU___SIZE + MASU___SIZE * x, fieldGraph[0],TRUE);
			//
			//}
			//
			//else if (g_layout[x][y] == LAYOUT_FOREST) {
			//
			//	DrawExtendGraph(MASU___SIZE * y, MASU___SIZE * x, MASU___SIZE + MASU___SIZE * y, MASU___SIZE + MASU___SIZE * x, GHandleForest, TRUE);
			//
			//}
			//
			//else if (g_layout[x][y] == LAYOUT_VILLAGE) {
			//
			//	DrawExtendGraph(MASU___SIZE * y, MASU___SIZE * x, MASU___SIZE + MASU___SIZE * y, MASU___SIZE + MASU___SIZE * x, GHandleVillage, TRUE);
			//
			//}
			//else if (g_layout[x][y] == LAYOUT_WALL) {
			//
			//	DrawExtendGraph(MASU___SIZE * y, MASU___SIZE * x, MASU___SIZE + MASU___SIZE * y, MASU___SIZE + MASU___SIZE * x, GHandleWall, TRUE);
			//
			//}
			//else if (g_layout[x][y] == LAYOUT_DRIVE) {
			//
			//	DrawExtendGraph(MASU___SIZE * y, MASU___SIZE * x, MASU___SIZE + MASU___SIZE * y, MASU___SIZE + MASU___SIZE * x, GHandleDrive, TRUE);
			//
			//}
			//else if (g_layout[x][y] == LAYOUT_BRIDGE) {
			//
			//	DrawExtendGraph(MASU___SIZE * y, MASU___SIZE * x, MASU___SIZE + MASU___SIZE * y, MASU___SIZE + MASU___SIZE * x, GHandleBridge, TRUE);
			//
			//}
			//else if (g_layout[x][y] == LAYOUT_STONE) {
			//
			//	DrawExtendGraph(MASU___SIZE * y, MASU___SIZE * x, MASU___SIZE + MASU___SIZE * y, MASU___SIZE + MASU___SIZE * x, GHandleStone, TRUE);
			//}		

			int graphHandle;
			switch (g_layout[x][y]) {
			case LAYOUT_GRASS:
				graphHandle = GHandleGrass;
				break;
			case LAYOUT_FOREST:
				graphHandle = GHandleForest;
				break;
			case LAYOUT_VILLAGE:
				graphHandle = GHandleVillage;
				break;
			case LAYOUT_WALL:
				graphHandle = GHandleWall;
				break;
			case LAYOUT_DRIVE:
				graphHandle = GHandleDrive;
				break;
			case LAYOUT_BRIDGE:
				graphHandle = GHandleBridge;
				break;
			case LAYOUT_STONE:
				graphHandle = GHandleStone;
				break;
			default:
				continue;
			}
			DrawExtendGraph(MASU___SIZE * y, MASU___SIZE * x, MASU___SIZE + MASU___SIZE * y, MASU___SIZE + MASU___SIZE * x, graphHandle, TRUE);
		
		}
	
	}

}

//VOID Deleteghandle() {
//	for (int i = 0; i < 6; i++) {
//		DeleteGraph(fieldGraph[i]);
//
//
//	}






