#define _CRT_SECURE_NO_WARNINGS
#include "playScene.h"
#include <thread>
#include <stdio.h>
#include <stdlib.h>

int fieldGraph[6]  ;
int GHandleGrass   ;
int GHandleForest  ;
int GHandleVillage ;
int GHandleWall    ;
int GHandleStone   ;
int GHandleBridge  ;
int GHandleDrive   ;

//extern BOOL g_isSnOrBF    ;//シナリオなのかバトルフィールド
char buff[256]     ;//シナリオを格納するバッファ
FILE* fp; //ファイル操作の準備 ファイルポインタ変数
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
	

	fp = fopen("scenario.txt", "r"); //binをオープンします
	if (fp == NULL) {

		DrawString(100, 100, "scenario.bin is not opened. abort", 0xFF0000, FALSE);
	}

	return;
}


/*
試行錯誤v1.0
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


VOID ScenarioDraw() {
	
		int span = 0;
		int x =50;
		int y =50 +span;
		int ySpeed = 0;
		while (fgets(buff, sizeof(buff), fp) != NULL) {
			
			DrawString(50, 50+span, buff, 0xFFFFFF);
			span += 30;
			
			
		}
		fclose(fp);
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

			if (g_layout[x][y] == LAYOUT_GRASS) {
			
				DrawExtendGraph(MASU___SIZE * y, MASU___SIZE * x, MASU___SIZE+ MASU___SIZE * y, MASU___SIZE + MASU___SIZE * x, fieldGraph[0],TRUE);
			
			}
			
			else if (g_layout[x][y] == LAYOUT_FOREST) {
			
				DrawExtendGraph(MASU___SIZE * y, MASU___SIZE * x, MASU___SIZE + MASU___SIZE * y, MASU___SIZE + MASU___SIZE * x, GHandleForest, TRUE);

			}

			else if (g_layout[x][y] == LAYOUT_VILLAGE) {

				DrawExtendGraph(MASU___SIZE * y, MASU___SIZE * x, MASU___SIZE + MASU___SIZE * y, MASU___SIZE + MASU___SIZE * x, GHandleVillage, TRUE);

			}
			else if (g_layout[x][y] == LAYOUT_WALL) {

				DrawExtendGraph(MASU___SIZE * y, MASU___SIZE * x, MASU___SIZE + MASU___SIZE * y, MASU___SIZE + MASU___SIZE * x, GHandleWall, TRUE);

			}
			else if (g_layout[x][y] == LAYOUT_DRIVE) {

				DrawExtendGraph(MASU___SIZE * y, MASU___SIZE * x, MASU___SIZE + MASU___SIZE * y, MASU___SIZE + MASU___SIZE * x, GHandleDrive, TRUE);

			}
			else if (g_layout[x][y] == LAYOUT_BRIDGE) {

				DrawExtendGraph(MASU___SIZE * y, MASU___SIZE * x, MASU___SIZE + MASU___SIZE * y, MASU___SIZE + MASU___SIZE * x, GHandleBridge, TRUE);

			}
			else if (g_layout[x][y] == LAYOUT_STONE) {

				DrawExtendGraph(MASU___SIZE * y, MASU___SIZE * x, MASU___SIZE + MASU___SIZE * y, MASU___SIZE + MASU___SIZE * x, GHandleStone, TRUE);
			}		
			
		}
	
	}

}

//VOID Deleteghandle() {
//	for (int i = 0; i < 6; i++) {
//		DeleteGraph(fieldGraph[i]);
//
//
//	}






