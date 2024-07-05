#include "key.h"

//�O���[�o���ϐ�

//���݂̃L�[�������Ă���t���[����
int NowKeyPressFrame[KEYKINDMAX];
//��O�̃L�[�L�[�������Ă���t���[����
int OldKeyPressFrame[KEYKINDMAX];

//�֐�

 //�L�[�����̏�����
VOID KeyInit( ) {

	for (int i = 0; i < KEYKINDMAX; i++) {

		NowKeyPressFrame[i] = 0;
		OldKeyPressFrame[i] = 0;

	}
	return;
}

 //�L�[�����̍X�V

VOID KeyUpdata() {

	char KeyState[KEYKINDMAX];

	//���ׂẴL�[������x�擾
	GetHitKeyStateAll(KeyState);

	//�L�[�̏����X�V
	for (int i = 0; i < KEYKINDMAX; i++) {

		//��O�̃L�[���͂�ۑ�
		OldKeyPressFrame[i] = NowKeyPressFrame[i];

		//���݁A�L�[��������Ă���Ƃ�
		if (KeyState[i] > 0) {

			//������Ă���t���[�������J�E���g�A�b�v
			NowKeyPressFrame[i]++;

		}
		else if (KeyState[i] == 0) {
			//������Ă��Ȃ�
			NowKeyPressFrame[i] = 0;
		}
	}
	return;
}

//����̃L�[����������
BOOL KeyDown(int KEY_INPUT_) {

	
	//���݉����ꂢ�ăL�[�̃t���[������0������Ȃ�
	if (NowKeyPressFrame[KEY_INPUT_] > 0) {

		return TRUE;

	}

	return FALSE;
}

//����̃L�[���N���b�N������?
//�����FDX���C�u�����̃L�[�R�[�h�iKEY_INPUT_�Ŏn�܂�}�N����`�j
//����:�u�L�[���������L�[��������v�ōs��ꂽ�Ƃ����A�L���b�N
BOOL KeyClick(int KEY_INPUT_) {
	//���݉����ꂢ�ăL�[�̃t���[������0������Ȃ�
	//��O�̃L�[�͂�����Ă����Ƃ�
	if (NowKeyPressFrame[KEY_INPUT_] == 0 
        &&OldKeyPressFrame[KEY_INPUT_]>0)
	{

		return TRUE;

	}

	return FALSE;



}
//����̃L�[���������t���[����
//����:DX���C�u���C�̃L�[�R�[�h�iKET_INPUT_�Ŏn�܂�}�N����`�j
//����:�߂�l�̓~���b�Ȃǂł͂Ȃ��C�t���[����!
int KeyPressFrame(int KEY_INPUT_) {

	return NowKeyPressFrame[KEY_INPUT_];
}