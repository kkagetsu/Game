#include "cursorCntrol.h"
#include "playScene.h"

//コンストラクタ　カーソルの情報を初期化
Cursor::Cursor(Player& player) : player(player) {

	this->x1 = (GRID__WIDTH - 1) * MASU___SIZE;

	this->x2 = GRID__WIDTH * MASU___SIZE;

	this->y1 = (GRID_HEIGHT - 1) * MASU___SIZE;
	
	this->y2 = GRID_HEIGHT * MASU___SIZE;
	
	this->color = GetColor(255, 255, 0);
	
	this->isPlayerSelected = false; //by gtp  初期状態ではプレイヤーは選択されていない

	for (int i = 0; i < 256 ; i++) {

		this->key[i] = 0;

	}
}

//ここも要修正　swtich文
VOID Cursor::CursorControl( ) {
	GetHitKeyStateAll(this->key);

	LONGLONG currentTime = GetNowHiPerformanceCount();  // gtp 現在の時刻を取得

	// gtp 移動のタイミングを制御するための間隔（マイクロ秒）
	const LONGLONG moveInterval = 100000;  // gtp 0.2秒

	if (currentTime - lastMoveTime > moveInterval) {
		if (this->key[KEY_INPUT_LEFT] == 1
			&& this->x1 >= MASU___SIZE) {
			this->x1 = this->x1 - MASU___SIZE;
			this->x2 = this->x2 - MASU___SIZE;

			lastMoveTime = currentTime;
		}
		else if (this->key[KEY_INPUT_RIGHT] == 1
			&& this->x1 <= (GRID__WIDTH - 2) * MASU___SIZE) {
			this->x1 = this->x1 + MASU___SIZE;
			this->x2 = this->x2 + MASU___SIZE;

			lastMoveTime = currentTime;
		}
		else if (this->key[KEY_INPUT_UP] == 1
			&& this->y1 >= MASU___SIZE) {
			this->y1 = this->y1 - MASU___SIZE;
			this->y2 = this->y2 - MASU___SIZE;

			lastMoveTime = currentTime;
		}
		else if (this->key[KEY_INPUT_DOWN] == 1
			&& this->y1 <= (GRID_HEIGHT - 2) * MASU___SIZE) {
			this->y1 = this->y1 + MASU___SIZE;
			this->y2 = this->y2 + MASU___SIZE;

			lastMoveTime = currentTime;
		}

		else if (this->key[KEY_INPUT_SPACE] == 1) //かつカーソルの座標　＝　プレイの座標
		{
			//to do　Flag PlayerUiShow

		}
		//gtp
		this->isPlayerSelected = (this->x1 == player.getPosX() * MASU___SIZE && this->y1 == player.getPosY() * MASU___SIZE);
	
	}
}
VOID Cursor::CursorDraw() {

		DrawBox(this->x1, this->y1, this->x2, this->y2, color, TRUE);


	}


VOID Cursor::MapInfoShow() {

	// カーソルがあるマップの座標を計算

	int mapX = this->x1 / MASU___SIZE;
	int mapY = this->y1 / MASU___SIZE;

	if (mapX >= 0 && mapX < GRID__WIDTH && mapY >= 0 && mapY < GRID_HEIGHT) {

		// マップ情報を取得
		E_LAYOUT_T mapInfo = g_layout[mapY][mapX];

		switch (mapInfo) {
		case LAYOUT_GRASS:

			DrawString(200, 0, "草", 0x00ff00);

			break;

		case LAYOUT_VILLAGE:

			DrawString(200, 0, "村", 0xC8BFE7);

			break;

		case LAYOUT_STONE:

			DrawString(200, 0, "石", 0xCCDDE7);

			break;


		case LAYOUT_DRIVE:

			DrawString(200, 0, "川", 0x0000ff);

			break;

		case LAYOUT_FOREST:

			DrawString(200, 0, "森", 0x8E403A);

			break;

		case LAYOUT_WALL:

			DrawString(200, 0, "壁", 0xE7E6CD);

			break;

		case LAYOUT_BRIDGE:

			DrawString(200, 0, "橋", 0xE7C385);

			break;



		default:

			DrawString(200, 0, "エラー", 0xFF0000);

			break;
		}
	}

	//by gtp プレイヤーが選択されている場合にステータスを表示
	if (this->isPlayerSelected) {
		player.StatusShow();
	}
}

