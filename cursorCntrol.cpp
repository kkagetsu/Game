#include "cursorCntrol.h"
#include "playScene.h"

//コンストラクタ　カーソルの情報を初期化
Cursor::Cursor() {

	this->x1 = (GRID__WIDTH - 1) * MASU___SIZE;

	this->x2 = GRID__WIDTH * MASU___SIZE;

	this->y1 = (GRID_HEIGHT - 1) * MASU___SIZE;
	
	this->y2 = GRID_HEIGHT * MASU___SIZE;
	
	this->color = GetColor(255, 255, 0);
	
	for (int i = 0; i < 256 ; i++) {

		this->key[i] = 0;

	}
}
//ここも要修正　swtich文
VOID Cursor::CursorControl() {
	GetHitKeyStateAll(this->key);
	if      (this->key[KEY_INPUT_LEFT] == 1
		   &&this->x1 >= MASU___SIZE) {
		this->x1 = this->x1 - MASU___SIZE;
		this->x2 = this->x2 - MASU___SIZE;

	}
	else if (this->key[KEY_INPUT_RIGHT] == 1
		   &&this->x1<= (GRID__WIDTH-2)  * MASU___SIZE) {
		this->x1 = this->x1 + MASU___SIZE;
		this->x2 = this->x2 + MASU___SIZE;
	}
	else if (this->key[KEY_INPUT_UP] == 1
		   &&this->y1 >= MASU___SIZE) {
		this->y1 = this->y1 - MASU___SIZE;
		this->y2 = this->y2 - MASU___SIZE;
	}
	else if (this->key[KEY_INPUT_DOWN] == 1
		   &&this->y1<= (GRID_HEIGHT-2) * MASU___SIZE) {
		this->y1 = this->y1 + MASU___SIZE;
		this->y2 = this->y2 + MASU___SIZE;
	}

	else if (this->key[KEY_INPUT_SPACE] == 1) //かつカーソルの座標　＝　プレイの座標
	{
		//to do　Flag PlayerUiShow




	}
}
VOID Cursor::CursorDraw() {

		DrawBox(x1, y1, x2,y2, color, TRUE);


	}


