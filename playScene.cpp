#define _CRT_SECURE_NO_WARNINGS
#include "playScene.h"
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#define COLUMN_COUNT (256)//��s���Ƃ̃o�t�@
#define COLUMN        (20) //�s��

int fieldGraph[6]  ;
int GHandleGrass   ;
int GHandleForest  ;
int GHandleVillage ;
int GHandleWall    ;
int GHandleStone   ;
int GHandleBridge  ;
int GHandleDrive   ;
extern BOOL isScenario    ;

char buff[256][COLUMN_COUNT] = { 0 }; // �V�i���I���i�[����o�b�t�@
int lineCount = 0;                    // �ǂݍ��񂾍s��

//extern BOOL g_isSnOrBF    ;//�V�i���I�Ȃ̂��o�g���t�B�[���h

//char buff[20][COLUMN_COUNT]     ;//�V�i���I���i�[����o�b�t�@

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
	FILE* fp = fopen("scenario.txt", "r"); // �e�L�X�g�t�@�C�����I�[�v��
	if (fp == NULL) {
		OutputDebugString("scenario.txt is not opened. abort\n");
		return;
	}

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
VOID ScenarioDraw() {
	static int totalLength = 0; // ���ׂĂ̕����̑���
	static char displayStr[256 * COLUMN_COUNT] = ""; // �\�����镶����
	static int t = 0;
	static int tmax = 20;
	static int currentPos = 0; // ���݂̕����ʒu
	static bool messageDisplayed = false; // ���b�Z�[�W�����S�ɕ\�����ꂽ���ǂ����̃t���O

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
			messageDisplayed = true; // ���b�Z�[�W�����S�ɕ\�����ꂽ
		}
		t = 0;
	}

	// ��ʃN���A
	ClearDrawScreen();

	// �������`��
	DrawString(100, 100, displayStr, 0xffffff); // ���b�Z�[�W��`��

	if (messageDisplayed ==TRUE) {



		DrawString(100, 150, "�I��", 0xffffff); // ���b�Z�[�W���\�����ꂽ��ɏI����`��
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

//VOID Deleteghandle() {
//	for (int i = 0; i < 6; i++) {
//		DeleteGraph(fieldGraph[i]);
//
//
//	}






