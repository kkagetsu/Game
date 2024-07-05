#pragma once

#include "DxLib.h"

class Cursor {

public:
	int x1;
	int x2;
	int y1;
	int y2;
	int color;
	char key[256];

	Cursor();
	VOID CursorControl();
	VOID CursorDraw();

    //VOID CursorControl(int x,int y,in);


};

