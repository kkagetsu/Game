#pragma once

#include "Dxlib.h"

//�}�N����`
#define KEYKINDMAX 256 //�L�[�̎��

//�O���̃v���g�^�C�v�錾
extern VOID KeyInit( );              //�L�[�����̏�����
extern VOID KeyUpdata( );            //�L�[�����̍X�V
extern BOOL KeyDown(int KEY_INPUT_);    //����̃L�[����������
extern BOOL KeyClick(int KEY_INPUT_); 	//����̃L�[���N���b�N������
extern int KeyPressFrame(int KEY_INPUT);//����̃L�[���������t���[����


