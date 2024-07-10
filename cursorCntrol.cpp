#include "cursorCntrol.h"
#include "playScene.h"

//�R���X�g���N�^�@�J�[�\���̏���������
Cursor::Cursor(Player& player) : player(player) {

	this->x1 = (GRID__WIDTH - 1) * MASU___SIZE;

	this->x2 = GRID__WIDTH * MASU___SIZE;

	this->y1 = (GRID_HEIGHT - 1) * MASU___SIZE;
	
	this->y2 = GRID_HEIGHT * MASU___SIZE;

	this->mapCursor = TRUE; //TRUE�̏ꍇ�@�}�b�v�J�[�\���`��ON
	


	this->playerX1 = 560;
	this->playerY1 = GRID_HEIGHT * MASU___SIZE;
	this->playerX2 = 560 + MASU___SIZE;
	this->playerY2 = GRID_HEIGHT * MASU___SIZE + MASU___SIZE;

	this->playerUICursor = FALSE;//�������s�\�����

	this->color = GetColor(255, 255, 0);
	
	this->isPlayerSelected = false; //by gtp  ������Ԃł̓v���C���[�͑I������Ă��Ȃ�

	this->isBlink = true;  //gto ������Ԃŕ\��
	this->lastBlinkTime = GetNowHiPerformanceCount();  //gtp ���݂̎������擾
	

	for (int i = 0; i < 256 ; i++) {

		this->key[i] = 0;

	}
}

//�������v�C���@swtich��
VOID Cursor::CursorControl( ) {
	GetHitKeyStateAll(this->key);

	LONGLONG currentTime = GetNowHiPerformanceCount();  // gtp ���݂̎������擾

	// gtp �ړ��̃^�C�~���O�𐧌䂷�邽�߂̊Ԋu�i�}�C�N���b�j
	const LONGLONG moveInterval = 100000;  // gtp 0.2�b

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

		else if (this->key[KEY_INPUT_SPACE] == 1) //���J�[�\���̍��W�@���@�v���C�̍��W
		{
			//to do�@Flag PlayerUiShow

		}
		//gtp
		
		//�J�[�\���̂������W�@�����@��player�̌����W�̏ꍇ�@isPlayerSelected��true;
		this->isPlayerSelected = (this->x1 == player.getPosX() * MASU___SIZE && this->y1 == player.getPosY() * MASU___SIZE);
	
	}
}
VOID Cursor::CursorDraw() {

	LONGLONG currentTime = GetNowHiPerformanceCount();

	// �_�ł̊Ԋu���o�߂�����\���t���O��؂�ւ���
	if (currentTime - lastBlinkTime > blink) {
		isBlink = !isBlink;
		lastBlinkTime = currentTime;
	}


	if (isBlink) {
		DrawBox(this->x1, this->y1, this->x2, this->y2, color, TRUE);
	}

	}


VOID Cursor::MapInfoShow() {

	// �J�[�\��������}�b�v�̍��W���v�Z

	int mapX = this->x1 / MASU___SIZE;
	int mapY = this->y1 / MASU___SIZE;

	if (mapX >= 0 && mapX < GRID__WIDTH && mapY >= 0 && mapY < GRID_HEIGHT) {

		// �}�b�v�����擾
		E_LAYOUT_T mapInfo = g_layout[mapY][mapX];

		switch (mapInfo) {
		case LAYOUT_GRASS:

			DrawString(200, 0, "��", 0x00ff00);

			break;

		case LAYOUT_VILLAGE:

			DrawString(200, 0, "��", 0xC8BFE7);

			break;

		case LAYOUT_STONE:

			DrawString(200, 0, "��", 0xCCDDE7);

			break;


		case LAYOUT_DRIVE:

			DrawString(200, 0, "��", 0x0000ff);

			break;

		case LAYOUT_FOREST:

			DrawString(200, 0, "�X", 0x8E403A);

			break;

		case LAYOUT_WALL:

			DrawString(200, 0, "��", 0xE7E6CD);

			break;

		case LAYOUT_BRIDGE:

			DrawString(200, 0, "��", 0xE7C385);

			break;



		default:

			DrawString(200, 0, "�G���[", 0xFF0000);

			break;
		}
	}

	//by gtp �v���C���[���I������Ă���ꍇ�ɃX�e�[�^�X��\��
	if (this->isPlayerSelected) {
		player.StatusShow();
	}
}


VOID Cursor ::PlayerUICursorDraw() {
	
	DrawBox(playerX1+1, playerY1+1,playerX2-1,playerY2-1,0x00ff00,FALSE);
}


VOID Cursor::PlayerControl() {

	GetHitKeyStateAll(this->key);

	// �v���C���[UI�J�[�\���̈ړ�����
	const int playerMinX = 560;
	const int playerMaxX = 720;
	const int playerMinY = 480;
	const int playerMaxY = 600;

	if (mapCursor == FALSE) { //FALSE�̏ꍇ�@�v���C���J�[�\������ON
		if (this->key[KEY_INPUT_LEFT] == 1
			&& this->playerX1 >= playerMinX) {
			this->playerX1 = this->playerX1 + MASU___SIZE;
			this->playerX2 = this->playerX2 + MASU___SIZE;

		}

		else if (this->key[KEY_INPUT_RIGHT] == 1
			&& this->playerX1 <= playerMaxX) {
			this->playerX1 = this->playerX1 - MASU___SIZE;
			this->playerX2 = this->playerX2 - MASU___SIZE;

		}
		else if (this->key[KEY_INPUT_UP] == 1
			&& this->y1 >= playerMinY) {
			this->playerY1 = this->playerY1 + MASU___SIZE;
			this->playerY2 = this->playerY2 + MASU___SIZE;

		}
		else if (this->key[KEY_INPUT_DOWN] == 1
			&& this->y1 <= playerMaxY) {
			this->playerY1 = this->playerY1 - MASU___SIZE;
			this->playerY2 = this->playerY2 - MASU___SIZE;

		}
	}
}

VOID Cursor::Switching() {
	
	if (isPlayerSelected == TRUE && this->key[KEY_INPUT_SPACE] == 1)//�J�[�\�����v���C���P�w�肵����space���������ꍇ
	{
		
		mapCursor = FALSE;        //FALSE�̏ꍇ�@�}�b�v�J�[�\���`��OFF
		PlayerUICursorDraw();     //�����ăv���C��UI�J�[�\���`�悷��
	
	}


}
	