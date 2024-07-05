#include "titleScene.h"
#include "key.h"
#include "gameManager.h"
#include "playScene.h"
//#include "Timer.h"
BOOL isLClickOrSpace;//���N���b�N���X�y�[�X�������ꂽ��@1
float newGameY;  //�@�Q�[���J�n������y�ʒu
float loadGameY; //�@�Q�[�����[�h��y�ʒu
float opitionY;  //�@�Q�[���ݒ��y�ʒu
int cursorY;     //  �J�[�\���ړ��̏㉺���
int gHandle;     //  �o�b�N�O���E���h��ʂ̕ۑ��ꏊ
int cursorHandle;//�@���j���[�I��p�J�[�\��

//���j���[�̏�����
void TitleMenuInit( ) {
	
	isLClickOrSpace = FALSE;
    newGameY  = WINDOW_HEIGHT / 1.4f - MASU___SIZE*3; //�@�Q�[���J�n������y�ʒu
    loadGameY = WINDOW_HEIGHT / 1.4f - MASU___SIZE*2; //�@�Q�[�����[�h��y�ʒu
    opitionY  = WINDOW_HEIGHT / 1.4f - MASU___SIZE*1; //�@�Q�[���ݒ��y�ʒu
	cursorY = 0;

	//�悸�͉摜��ǂݍ���
	gHandle = LoadGraph("picture/RpgTitle.jpg");
	cursorHandle = LoadGraph("picture/yajirushi_right.png");


	return;
}

//�^�C�g���V�[���̕`��
void BackGroundDraw( ) {
	DrawGraph(0, 0, gHandle, TRUE);
	

	
	// �ǂݍ��񂾉摜�̃O���t�B�b�N�n���h�����폜
	//�Ō�̉�������ɓ��ꂽ�����x�X�g
//	DeleteGraph(gHandle);

	return;
}

//�^�C�g�����j���[�̏�������
void TitleMenuUpdate( ) 
{
	if (KeyDown(KEY_INPUT_DOWN)	 == 1)  //���̃L�[��������Ă�����
	{
		nowSelect = (nowSelect + 1) % MENU_NUM; //�I�����������
	}
	if (KeyDown(KEY_INPUT_UP)    == 1)  //���̃L�[��������Ă�����
	{
		nowSelect = (nowSelect + (MENU_NUM - 1)) % MENU_NUM; //�I�����������
	}
	if (KeyDown(KEY_INPUT_RETURN)== 1)  //�G���^�[�L�̃L�[��������Ă�����
	{
		switch (nowSelect) {

		case NEW_GAME:
			FLAG_GAME_SCENE == 1;
			nowGameScene = PLAY_SCENE;
			break;


		case LOAD_GAME:
			break;


		case OPITION:
			break;
		}

	}
	return;
}

	//���j���[��ʂ̕`��
void TitleMenuDraw( )
{   
	if (KeyDown(KEY_INPUT_SPACE) || GetMouseInput() & MOUSE_INPUT_LEFT)	isLClickOrSpace = TRUE;
	
	if (isLClickOrSpace == TRUE)
	{
		int drawStringX = WINDOW_WIDTH / 2 - 50;                  //800/2-50=350
		DrawString(drawStringX, newGameY, "New Game", 0xFFFFFF);
		DrawString(drawStringX, loadGameY, "Load Game", 0xFFFFFF);
		DrawString(drawStringX, opitionY, "Opition", 0xFFFFFF);
		DrawString(1, WINDOW_HEIGHT - 15,
			"Please use the �������� key to control , Enter key to decide on an option",
			0x00FF00);

		  
	
		//�摜�̎��ۃT�C�Y���傫���A�k�����܂��@�@�p��
		//DrawGraph(WINDOW_WIDTH / 2 - 100, cursorY, cursorHandle, FALSE);
		DrawExtendGraph(drawStringX-MASU___SIZE*2, cursorY-10, 
			            drawStringX - MASU___SIZE, cursorY-10 + MASU___SIZE ,
			            cursorHandle, TRUE);
	}
	else {
		(DrawString(WINDOW_WIDTH / 3, WINDOW_HEIGHT - WINDOW_HEIGHT / 4,
			"�X�y�[�X�L�[�܂���\n���N���b�N���Ă�������", GetColor(255, 0, 0)));
	}
	switch (nowSelect) {

	case NEW_GAME:
		cursorY = newGameY;
	
		break;


	case LOAD_GAME:
		cursorY = loadGameY;

		break;


	case OPITION:
		cursorY = opitionY;
		
		break;
	}


	return;
}




