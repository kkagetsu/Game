#include "fps.h"
 extern FPS g_fps;

//FPSの初期化
VOID FPSInit() {
	
	//WINDOWSが起動してから現在までの時間を得る(マイクロ秒)
	g_fps.FirstTakeTime = GetNowHiPerformanceCount();
	//他の初期化
	g_fps.NowTakeTime = g_fps.FirstTakeTime;
	g_fps.OldTakeTime = g_fps.FirstTakeTime;
	g_fps.Deltatime = 0.000001f;
	g_fps.FrameConut = 1;
	g_fps.Average = 0.0f;
	return;
}

//計測
VOID FPSCheck() {

	//現在の時刻を取得
	g_fps.NowTakeTime = GetNowHiPerformanceCount();

	//デルタタイムを計算
	g_fps.Deltatime = (g_fps.NowTakeTime - g_fps.OldTakeTime) / MicroSecond;

	//現在の時刻を保存
	g_fps.OldTakeTime = g_fps.NowTakeTime;

	//現在がMAX　フレーム目なら
	if (g_fps.FrameConut == GameFPS) {

		//1フレーム目～MAXフレーム目までんの合計時間を計算
		float TotalFrameTime = g_fps.NowTakeTime - g_fps.FirstTakeTime;

		//合計時間を理想のFPS値で割って平均値を計算
		float CalcAverage = TotalFrameTime / GameFPS;
		//一秒あたりのフレーム数に変換
		g_fps.Average = MicroSecond / CalcAverage;

		//１プレーム目の時刻を獲得
		g_fps.FirstTakeTime = GetNowHiPerformanceCount();
		//フレーム数を１に戻す
		g_fps.FrameConut = 1;


	}

	else {

		//フレーム数をカウントアップ
		g_fps.FrameConut++;

	}

	return;
}
  
//描画
VOID FPSDraw() {

	

	DrawFormatString(50, 0, GetColor(255, 255, 255), "FPS:%3.1f", g_fps.Average);

	

	return ;
}

VOID FPSWait() {

	//早すぎたときに待機するミリ秒
	int wait = 0;


	//待ち時間を計測
	wait = MicroSecond / GameFPS * g_fps.FrameConut   //理想の時間<
		- (g_fps.NowTakeTime - g_fps.FirstTakeTime);//実際の時間

	//マイクロ秒をミリ秒に変換
	wait /= MillSecond;

	//待ち時間があるならば
	if (wait > 0 && wait <= WaitTImeMill) {

		//メッセージを処理しながら待つ
		//WaitTimer(wait);

	}

	return;
}


