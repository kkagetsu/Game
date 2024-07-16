//�Q�[�������̃\�[�X�t�@�C��

//�w�b�_�t�@�C������������
#include "gameManager.h"
#include "Key.h"
#include "titleScene.h"
#include "playScene.h"


//�O���[�o���ϐ�

enum tagE_GAME_SCENE nowGameScene;//���݂̃Q�[���V�[��

//�Q�[���V�[���̖��O

char GameSceneName[GAME_SCENE_COUNT][GAME_SCENE_NAME_MAX]{

	"�^�C�g�����"
	,"�Q�[�����"
	,"�G���f�B���O���"

};

//�֐�

//�^�C�g�������� 
VOID  TitleInit() {
	if (GAME_DEBUG == TRUE) {
		DrawFormatString(WINDOW_WIDTH - 200, 0, GetColor(255, 255, 255),
			"%s%s", GameSceneName[nowGameScene], "������");

	}

	FLAG_GAME_SCENE == 0;



	return;
}

//�^�C�g���Ǘ�
VOID TitleCtrl() {
	TitleProc(); //���������Ă���
	TitleDraw(); //�`�悷��
	return;
}
//�^�C�g������
VOID TitleProc() {

	TitleMenuUpdate();
	//�^�C�g���V�[������v���C���[�V�[����
	if (KeyClick(KEY_INPUT_RETURN) == TRUE && FLAG_GAME_SCENE == TRUE) { //�G���^�[�L�[��������Ă���game start(flag) 1�@����ȊO��0
		
		PlayInit(); //�v���C�[�V�[����������

		//�V�[���؂�ւ�
		nowGameScene = PLAY_SCENE;
		
		return;
	}
	return;
}
//�^�C�g���`��
VOID TitleDraw() {
	if (GAME_DEBUG == TRUE) {
		DrawFormatString(WINDOW_WIDTH - 200, 0, GetColor(255, 255, 255),
			"%s%s", GameSceneName[nowGameScene], "�`�撆");

	}
	BackGroundDraw();  //�Q�[���^�C�g���ŏ��̔w�i�摜��`��
	TitleMenuDraw();   //�������N���b�N�܂���space�L�[����������@
	                   //�^�C�g����ʂ̃��j���[�I���Ɉڂ�
	return;
}


//�Q�[����������
VOID PlayInit() {
	
	if (GAME_DEBUG == TRUE) {
		DrawFormatString(WINDOW_WIDTH - 200, 0, GetColor(255, 255, 255),
			"%s%s", GameSceneName[nowGameScene], "������");

	}
	return;
}
//�Q�[�����Ǘ�
VOID PlayCtrl() {
	PlayProc(); //���������Ă���
	PlayDraw(); //�`�悷��
	
	return;
}
//�Q�[��������
VOID PlayProc() {


	//�Q�[���N���A�V�[���ɐ؂�ւ�
	if (KeyClick(KEY_INPUT_RETURN) == TRUE && SHOW_ENDING ==TRUE) 
	{

		//�G���^�[�L�[�������ꂽ�� 
		//�v���C�[�V��������
		EndInit();

		//�V�[���؂�ւ�
		nowGameScene = END_SCENE;

		return;
	}
	//�Q�[���I�[�o�[�V�[���ɐ؂�ւ�
	if (KeyClick(KEY_INPUT_RETURN) == TRUE&&SHOW_GAME_OVER == TRUE)
	{

		//�G���^�[�L�[�������ꂽ�� 
		//�v���C�[�V��������
		EndInit();

		//�V�[���؂�ւ�
		nowGameScene = END_SCENE;

		return;
	}
	return;
	
}
//�Q�[�����`��
VOID PlayDraw(){
	if (GAME_DEBUG == TRUE) 
	{
		DrawFormatString(WINDOW_WIDTH - 200, 0, GetColor(255, 255, 255),
			"%s%s", GameSceneName[nowGameScene], "�`�撆");

	}
	return;
}


//�G���f�B���O������
VOID EndInit(){
	if (GAME_DEBUG == TRUE) {
		DrawFormatString(WINDOW_WIDTH - 200, 0, GetColor(255, 255, 255),
			"%s%s", GameSceneName[nowGameScene], "������");
		SHOW_ENDING    == 0;
		SHOW_GAME_OVER == 0;
	}
	return;
}
//�G���f�B���O�Ǘ�
VOID EndCtrl(){
	EndProc(); //���������Ă���
	EndDraw(); //�`�悷��

	return;
}
//�G���f�B���O����
VOID EndProc(){
	//�V�[���؂�ւ�
	if (KeyClick(KEY_INPUT_RETURN) == TRUE) {

		//�G���^�[�L�[�������ꂽ�� 
		//�v���C�[�V��������
		TitleInit();

		//�V�[���؂�ւ�
		nowGameScene = TITLE_SCENE;

		return;
	}
	return;
}
//�G���f�B���O�`��
VOID EndDraw(){
	if (GAME_DEBUG == TRUE) {
		DrawFormatString(WINDOW_WIDTH - 200, 0, GetColor(255, 255, 255),
			"%s%s", GameSceneName[nowGameScene], "�`�撆");

	}
	return;
}