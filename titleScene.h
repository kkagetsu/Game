#pragma once

#include "Dxlib.h"

//�^�C�g����ʗp�̑I����
//�^�C�g���V�[���̃��b�Z�[�W�`��
/*
  �^�C�g����
  �I�����@�@ GAME START �Q�[����ʂցi�^�C�g����ʁ�loading ����ʁ��Q�[����ʁj
  �@         LOAD GAME�@�@
	 �@�@    OPTION   BGM �T�C�Y

		�@�@04//11  start
*/


typedef enum tagE_TITLEMENU   //���j���[�̍\����
{
	NEW_GAME, //�Q�[���J�n   0
	LOAD_GAME,//�Q�[�����[�h 1
	OPITION,//�ݒ�           2

	MENU_NUM//�J�E���^�[�@�@ 3

} E_TITLEMENU;


static int nowSelect = NEW_GAME; //���݂̑I�����Q�[���J�n


extern VOID TitleMenuInit();//���j���[�̏�����

extern VOID BackGroundDraw();//�^�C�g���̔w�i�摜��`��

//�֐������@���̂܂܎g���@�@�p��
//extern VOID BackGroundMessageDraw();//�^�C�g���w�i���b�Z�[�W��`��

extern VOID TitleMenuUpdate();//���j���[�I���̏���

extern VOID TitleMenuDraw();//���j���[���e�̕`��
