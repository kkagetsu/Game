#define _CRT_SECURE_NO_WARNINGS
#include "playScene.h"
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#define COLUMN_COUNT (256)//��s���Ƃ̃o�t�@
#define COLUMN        (20) //�s��

int fieldGraph[6]  ;                  //�o�g���t�B�[���h�n�`�摜�i�[ 
int playersGraph[3];                  //�L�����̂����G�i�w�i�����j
int GHandleGrass   ;                  //�o�g���t�B�[���h�n�`---��
int GHandleForest  ;                  //�o�g���t�B�[���h�n�`---�X
int GHandleVillage ;                  //�o�g���t�B�[���h�n�`---��
int GHandleWall    ;                  //�o�g���t�B�[���h�n�`---��
int GHandleStone   ;                  //�o�g���t�B�[���h�n�`---��
int GHandleBridge  ;                  //�o�g���t�B�[���h�n�`---��
int GHandleDrive   ;                  //�o�g���t�B�[���h�n�`---��
extern BOOL isScenario    ;           //�V�i���I�pfalg
extern BOOL isEventTutorial ;         //�`���[�g���A���pfalg
char buff[COLUMN_COUNT][COLUMN_COUNT] = { 0 }; // �V�i���I���i�[����o�b�t�@
int lineCount = 0;                    // �ǂݍ��񂾍s��

//�L�����I�����@�w�i�؂�ւ��֐�
unsigned int GetFlashingColor(int time)
{
	int phase = (time / 30) % 3; // 90�t���[�����ƂɐF��ς���
	switch (phase)
	{
	case 0 : return GetColor(0, 0, 0);       // ��
	case 1 : return GetColor(128, 128, 128); // �D�F
	case 2 : return GetColor(255, 255, 255); // ��
	default: return GetColor(0, 0, 0);       //�I������Ă��Ȃ��ꍇ�����F�Ɠ������̂܂�
	}
}

//extern BOOL g_isSnOrBF    ;//�V�i���I�Ȃ̂��o�g���t�B�[���h

//char buff[20][COLUMN_COUNT]     ;//�V�i���I���i�[����o�b�t�@


//�v���C�V�[���̏�����
VOID PlaySceneInit() {

	//�܂Ƃ߂Ĉ�x�����摜�����[�h���܂�
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


	isScenario = true;  //�ŏ��`�悳�������̂̓V�i���I�Ȃ̂Ł@true�ɐݒ肷��
	isEventTutorial = true;//�ŏ��̃o�g���V�[�����`���[�g���A���Ȃ̂Ł@true�ɐݒ肷��
	//FILE* fp = NULL; //�t�@�C������̏��� �t�@�C���|�C���^�ϐ�
	//fp = fopen("scenario.txt", "r"); //text���I�[�v�����܂�
	//if (fp == NULL) {
	//
	//	OutputDebugString("scenario.bin is not opened. abort\n");
	//}
	//int i = 0;
	//while (fgets(buff[i], COLUMN_COUNT, fp) != NULL) {
	//	//��s�Â�buff�ɏ�������
	//	i++;
	//	
	//}
	//fclose(fp); //�������ތ�t�@�C��close���܂�
	//fp = NULL; //fp�|�C���^�����Z�b�g
	 
	// �t�@�C������̏���
	FILE* fp = fopen("scenario.txt", "r"); // �e�L�X�g�t�@�C�����I�[�v�����ǂݎ��
	if (fp == NULL) {                      //debug
		OutputDebugString("scenario.txt is not opened. abort\n");
		return;
	}
	//����buff��[lineCount]�s�ڂ̍Ōオ�k�[������0����Ȃ��ꍇ
	//fp�œǂݎ�����e�L�X�g�����̓��e��buff�ɏ������ށ@�Q�T�U�o�g�����Ƃɍs�؂�ւ�
	//�k�[���������܂�(�e�L�X�g���e�̍Ō�܂ŕK���k�[��'\0')
	while (fgets(buff[lineCount], COLUMN_COUNT, fp) != NULL) {
		lineCount++;
	}
	fclose(fp); // �������݌�t�@�C�����N���[�Y

	return;
}


/*
���s����v1.0�@�}���`�X���b�h
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


//�X���b�h 
void AsyncLoad()
{

	while (1) {
		// ���N�G�X�g���m�F.
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


		//�_�~�[��10�b�҂�
		auto sleepTime = std::chrono::seconds(10);
		std::this_thread::sleep_for(sleepTime);

		SetLockFlag(true);
	}
}

//loading ���  std::thread �ǂݍ��݂̎��s�͂��ׂė���ʂ�
//�����ł�thread���̊֐��́@��ʂ̓ǂݍ���,���y�̓ǂݍ��݁i�b��j�A
BOOL isLoading(BOOL load) {

	std::thread th(AsyncLoad);

	

	//�����_�̓ǂݍ��݂���u�ŏI��邩��sleep�Ŏ��Ԃ��҂�
	std::this_thread::sleep_for(std::chrono::seconds(5));


}

*/


//VOID ScenarioDraw() {
//	    
//
//		int span = 0;      //�s�Ԋu
//		const int x = 80;  //�e�L�X�g�擪�@X
//		const int y = 80 ; //�e�L�X�g�擪�@Y
//		
//		for (int i = 0; i < COLUMN; i++) {
//		
//			DrawString(x, y + span, buff[i], 0xFFFFFF);
//		
//			span += 30;
//		}
//	}


//�V�i���I�`��
VOID ScenarioDraw() {
	static int totalLength = 0; // ���ׂĂ̕����̑���
	static char displayStr[256 * COLUMN_COUNT] = ""; // �\�����镶����
	static int t = 0;//�^�C�}�[
	static int tmax = 15;//�^�C�}�[�̏��
	static int currentPos = 0; // ���݂̕����ʒu
	static bool messageDisplayed = false; // �V�i���I�@���b�Z�[�W�����S�ɕ\�����ꂽ���ǂ����̃t���O

	//�o�b�t�@����e�L�X�g�������R�s�[���鏈��������
	if (totalLength == 0) {     //�����V�i���I�i�[�p��totalLength�̕���������0�̏ꍇ
		for (int i = 0; i < lineCount; i++) {//�Q�T�U���Ƃ�lineCount����Â��₷
			totalLength += strlen(buff[i]);//buff��i�Ԗڂ̗v�f�i������j�̒�����Ԃ��AtotalLength�ɉ�����
		}
	}
	t++;  //�^�C�}�[�J�E���g�J�n(t=t+(1/�ő�fps))
	if (t > tmax && !messageDisplayed) { //�����^�C�}�[�̎��Ԃ�t�̏���ɒ������炩�V�i���I�e�L�X�g���܂��S���`�悳��Ă��Ȃ�
		                                 //(�k�[���Ɏ����Ă��Ȃ�)�ꍇ
		if (currentPos < totalLength)    //totalLength��currentPos(0)�̏ꍇ�͈�����Ȃ��@�e�L�X�g���܂����S�ɕ`��I��ĂȂ��@
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
			messageDisplayed = true; // ���b�Z�[�W�����S�ɕ\�����ꂽ
		}
		t = 0;
	}

	// ��ʃN���A
	ClearDrawScreen();

	// �������`��
	DrawString(80, 50, displayStr, 0xffffff); // ���b�Z�[�W��`��




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

			DrawString(x1, y2 - yUp + 1, "�R�E�^���E\n(���N���b�N�������Ō���)", 0xFB544E);

			if (GetMouseInput() & MOUSE_INPUT_LEFT) {
				static int t = 0;
				const int tMax = 100;
				// ���݂̎��Ԃ��擾
				int nowTime = GetNowCount();

				// �w�i�F��ݒ�
				unsigned int color = GetFlashingColor(nowTime);

				// ��ʑS�̂�h��Ԃ�
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

			DrawString(x1 + span + 10, y2 - yUp + 1, "�{�u\n(������)", 0xF5E496);
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

			DrawString(x1 + span * 2 + 20, y2 - yUp + 1, "�c��\n(������)", 0x825D89);
		}
		else {
			DrawExtendGraph(x1 + span * 2 + 20, y1,
				x2 + span * 2 + 20, y2,
				playersGraph[TANAKA], TRUE);
		}

	}
	// Z�L�[�������ꂽ��Đ����x��{�ɂȂ�
	if (CheckHitKey(KEY_INPUT_Z) == 1) {
		tmax = 1;
	}
	// S�L�[�������ꂽ�當���`�悪��C�ɏI���
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
	
	//�c����`��
	for (int i = 0; i <= GRID_HEIGHT; i++) {
		
		DrawLine(0, MASU___SIZE * i, 800, MASU___SIZE * i, GetColor(255, 0, 0));

	}
	//������`��
	for (int j = 0; j <= GRID__WIDTH; j++) {

		DrawLine(MASU___SIZE * j,0, MASU___SIZE * j ,480, GetColor(255, 0, 0));

	}
	//int GHandle_Grass = LoadGraph("maptile_sogen_02.png");
	//DrawExtendGraph(0,0,40,40, GHandle_Grass, TRUE);
	//DrawExtendGraph(0,0,40,40, GHandle_Grass, TRUE);


}

VOID FieldLaOutDraw() {

	FieldLineDraw();
	//���̕����v�C���@switch���ɕύX����
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
//�`���[�g���A���C�x���g
VOID EventTutorial() {
	const int xNameStart = 30;
	const int yNameStart = 500;
	const int span = 30;
	const int times = 2;
	DrawExtendGraph(30, 80,480,480, playersGraph[KOUTAROU],TRUE);
	DrawExtendGraph(370,80,920,480, playersGraph[BOBU],TRUE);
	
		if (t1 < 300 * times)
		{
			DrawString(xNameStart, yNameStart, "�{�u", 0xffffff);
			DrawString(xNameStart + span, yNameStart + span, "�w�R�E~������Ƃ��������x", 0xF5E496);
		}
		
		else if (t1 > 300* times && t1 < 600 * times) {
			DrawString(xNameStart, yNameStart, "�R�E�^���E", 0xffffff);
			DrawString(xNameStart + span, yNameStart + span, "�w��H�Ȃ��ɁA�ςȕ��H�����܂������x", 0xFB544E);
		}
		else if(t1 > 600 * times &&t1 <1200 * times){
			DrawString(xNameStart, yNameStart, "�{�u", 0xffffff);
			DrawString(xNameStart + span, yNameStart + span, "�w�Ⴄ�A�Ⴄ�A�u�f��G.L�v�ɍs���O�ɂ������...\n�s�������ǁA���̎��͂���F�̑��Z��������܂���x", 0xF5E496);
		}
		else if (t1 >1200 * times && t1 < 1800 * times) {
			DrawString(xNameStart, yNameStart, "�R�E�^���E", 0xffffff);
			DrawString(xNameStart + span, yNameStart + span, "�w����A�o���܂Ō�ꎞ�Ԃ��邩��A�ǂ����ƌm�Â��Ȃ��x", 0xFB544E);
		}
		else if (t1 > 1800 * times && t1 < 2400 * times) {
			DrawString(xNameStart, yNameStart, "�{�u", 0xffffff);
			DrawString(xNameStart + span, yNameStart + span, "�w�{���ł����I�ǂ������ł��A��낵�����肢�������܂��B\n�i�{�u���퓬�p���ɓ���j�x", 0xF5E496);
		}
		else
		{
			DrawString(xNameStart, yNameStart, "�R�E�^���E", 0xffffff);
			DrawString(xNameStart + span, yNameStart + span, "�w�ǂ��\�����A�S�͂ŗ����I�x", 0xFB544E);
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






