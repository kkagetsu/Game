#define _CRT_SECURE_NO_WARNINGS
#include "playScene.h"
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#define COLUMN_COUNT (256)//一行ごとのバファ
#define COLUMN        (20) //行数

int fieldGraph[6]  ;                  //バトルフィールド地形画像格納 
int playersGraph[3];                  //キャラのたち絵（背景抜き）
int GHandleGrass   ;                  //バトルフィールド地形---草
int GHandleForest  ;                  //バトルフィールド地形---森
int GHandleVillage ;                  //バトルフィールド地形---村
int GHandleWall    ;                  //バトルフィールド地形---壁
int GHandleStone   ;                  //バトルフィールド地形---石
int GHandleBridge  ;                  //バトルフィールド地形---橋
int GHandleDrive   ;                  //バトルフィールド地形---川
extern BOOL isScenario    ;           //シナリオ用falg
extern BOOL isEventTutorial ;         //チュートリアル用falg
char buff[COLUMN_COUNT][COLUMN_COUNT] = { 0 }; // シナリオを格納するバッファ
int lineCount = 0;                    // 読み込んだ行数

//キャラ選択時　背景切り替え関数
unsigned int GetFlashingColor(int time)
{
	int phase = (time / 30) % 3; // 90フレームごとに色を変える
	switch (phase)
	{
	case 0 : return GetColor(0, 0, 0);       // 黒
	case 1 : return GetColor(128, 128, 128); // 灰色
	case 2 : return GetColor(255, 255, 255); // 白
	default: return GetColor(0, 0, 0);       //選択されていない場合初期色と同じ黒のまま
	}
}

//extern BOOL g_isSnOrBF    ;//シナリオなのかバトルフィールド

//char buff[20][COLUMN_COUNT]     ;//シナリオを格納するバッファ


//プレイシーンの初期化
VOID PlaySceneInit() {

	//まとめて一度だけ画像をロードします
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
	
	playersGraph[KOUTAROU] = LoadGraph("picture/cha_tachie/Kagetsu.png");
	playersGraph[BOBU] = LoadGraph("picture/cha_tachie/Fy1M5bYssjdk.png");
	playersGraph[TANAKA] = LoadGraph("picture/cha_tachie/K2B7jixyorRCt.png");


	isScenario = true;  //最初描画させたいのはシナリオなので　trueに設定する
	isEventTutorial = true;//最初のバトルシーンがチュートリアルなので　trueに設定する
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
	FILE* fp = fopen("scenario.txt", "r"); // テキストファイルをオープンし読み取る
	if (fp == NULL) {                      //debug
		OutputDebugString("scenario.txt is not opened. abort\n");
		return;
	}
	//もしbuffの[lineCount]行目の最後がヌール文字0じゃない場合
	//fpで読み取ったテキスト文字の内容をbuffに書き込む　２５６バトルごとに行切り替え
	//ヌールが現れるまで(テキスト内容の最後まで必ずヌール'\0')
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


//シナリオ描画
VOID ScenarioDraw() {
	static int totalLength = 0; // すべての文字の総数
	static char displayStr[256 * COLUMN_COUNT] = ""; // 表示する文字列
	static int t = 0;//タイマー
	static int tmax = 15;//タイマーの上限
	static int currentPos = 0; // 現在の文字位置
	static bool messageDisplayed = false; // シナリオ　メッセージが完全に表示されたかどうかのフラグ

	//バッファからテキスト文字をコピーする処理↓↓↓
	if (totalLength == 0) {     //もしシナリオ格納用のtotalLengthの文字総数が0の場合
		for (int i = 0; i < lineCount; i++) {//２５６ごとにlineCountが一づつ増やす
			totalLength += strlen(buff[i]);//buffのi番目の要素（文字列）の長さを返し、totalLengthに加える
		}
	}
	t++;  //タイマーカウント開始(t=t+(1/最大fps))
	if (t > tmax && !messageDisplayed) { //もしタイマーの時間がtの上限に超えたらかつシナリオテキストがまだ全部描画されていない
		                                 //(ヌールに至っていない)場合
		if (currentPos < totalLength)    //totalLength＞currentPos(0)の場合は一つしかない　テキストがまだ完全に描画終わてない　
		{
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
	DrawString(80, 50, displayStr, 0xffffff); // メッセージを描画




	if (messageDisplayed == TRUE) {
		
		const int x1 = 100;
		const int x2 = 300;
		const int y1 = 430;
		const int y2 = 590;
		const int span = 200;
		int mx = 0, my = 0;
		const int yUp = 30;

		GetMousePoint(&mx,&my);
		//0
		if (mx >= x1 && mx <= x2 && my >= y1 && my <= y2) {
			DrawExtendGraph(x1, y1 - yUp,
				x2, y2 - yUp,
				playersGraph[KOUTAROU], TRUE);

			DrawString(x1, y2 - yUp + 1, "コウタロウ\n(左クリック長押しで決定)", 0xFB544E);

			if (GetMouseInput() & MOUSE_INPUT_LEFT) {
				static int t = 0;
				const int tMax = 100;
				// 現在の時間を取得
				int nowTime = GetNowCount();

				// 背景色を設定
				unsigned int color = GetFlashingColor(nowTime);

				// 画面全体を塗りつぶす
				DrawBox(x1, y1 - yUp, x2,y2 - yUp, color, TRUE);
				DrawExtendGraph(x1, y1 - yUp,
					x2, y2 - yUp,
					playersGraph[KOUTAROU], TRUE);
				t++;
				if (t > tMax) {
					isScenario = FALSE;
					t = 0;
				}

			}
		}
		else {
			DrawExtendGraph(x1, y1,
				x2, y2,
				playersGraph[KOUTAROU], TRUE);
		}
		//1
	    if(mx >= x1 + span + 10&& mx<= x2 + span + 10 && my>= y1 && my<= y2){
		
			DrawExtendGraph(x1 + span + 10, y1 - yUp,
				x2 + span + 10, y2 - yUp,
				playersGraph[BOBU], TRUE);

			DrawString(x1 + span + 10, y2 - yUp + 1, "ボブ\n(未実装)", 0xF5E496);
		}
		else {
			DrawExtendGraph(x1 + span + 10, y1 ,
				x2 + span + 10, y2 ,
				playersGraph[BOBU], TRUE);
		}
		//2
		if(mx >= x1 + span * 2 + 20 && mx <= x2 + span * 2 + 20 && my >= y1 && my <= y2){
			DrawExtendGraph(x1 + span * 2 + 20, y1 - yUp,
				x2 + span * 2 + 20, y2 - yUp,
				playersGraph[TANAKA], TRUE);

			DrawString(x1 + span * 2 + 20, y2 - yUp + 1, "田中\n(未実装)", 0x825D89);
		}
		else {
			DrawExtendGraph(x1 + span * 2 + 20, y1,
				x2 + span * 2 + 20, y2,
				playersGraph[TANAKA], TRUE);
		}

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
int t1 = 0;
//チュートリアルイベント
VOID EventTutorial() {
	const int xNameStart = 30;
	const int yNameStart = 500;
	const int span = 30;
	const int times = 2;
	DrawExtendGraph(30, 80,480,480, playersGraph[KOUTAROU],TRUE);
	DrawExtendGraph(370,80,920,480, playersGraph[BOBU],TRUE);
	
		if (t1 < 300 * times)
		{
			DrawString(xNameStart, yNameStart, "ボブ", 0xffffff);
			DrawString(xNameStart + span, yNameStart + span, "『コウ~ちょっといいかい』", 0xF5E496);
		}
		
		else if (t1 > 300* times && t1 < 600 * times) {
			DrawString(xNameStart, yNameStart, "コウタロウ", 0xffffff);
			DrawString(xNameStart + span, yNameStart + span, "『ん？なぁに、変な物食っちまったか』", 0xFB544E);
		}
		else if(t1 > 600 * times &&t1 <1200 * times){
			DrawString(xNameStart, yNameStart, "ボブ", 0xffffff);
			DrawString(xNameStart + span, yNameStart + span, "『違う、違う、「惑星G.L」に行く前にちょっと...\n不安だけど、私の実力じゃ皆の足纏かもしれません』", 0xF5E496);
		}
		else if (t1 >1200 * times && t1 < 1800 * times) {
			DrawString(xNameStart, yNameStart, "コウタロウ", 0xffffff);
			DrawString(xNameStart + span, yNameStart + span, "『じゃ、出発まで後一時間あるから、どう俺と稽古しない』", 0xFB544E);
		}
		else if (t1 > 1800 * times && t1 < 2400 * times) {
			DrawString(xNameStart, yNameStart, "ボブ", 0xffffff);
			DrawString(xNameStart + span, yNameStart + span, "『本当ですか！良かったです、よろしくお願いいたします。\n（ボブが戦闘姿勢に入る）』", 0xF5E496);
		}
		else
		{
			DrawString(xNameStart, yNameStart, "コウタロウ", 0xffffff);
			DrawString(xNameStart + span, yNameStart + span, "『良い構えだ、全力で来い！』", 0xFB544E);
			if (t1 > 3000 * times) {
				isEventTutorial = FALSE;
			}
		}

		t1++;
		if (CheckHitKey(KEY_INPUT_Z) == 1) {
			t1 = 3000*times;
		}
}
//VOID Deleteghandle() {
//	for (int i = 0; i < 6; i++) {
//		DeleteGraph(fieldGraph[i]);
//
//
//	}






