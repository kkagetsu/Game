#include "fps.h"
 extern FPS g_fps;

//FPS�̏�����
VOID FPSInit() {
	
	//WINDOWS���N�����Ă��猻�݂܂ł̎��Ԃ𓾂�(�}�C�N���b)
	g_fps.FirstTakeTime = GetNowHiPerformanceCount();
	//���̏�����
	g_fps.NowTakeTime = g_fps.FirstTakeTime;
	g_fps.OldTakeTime = g_fps.FirstTakeTime;
	g_fps.Deltatime = 0.000001f;
	g_fps.FrameConut = 1;
	g_fps.Average = 0.0f;
	return;
}

//�v��
VOID FPSCheck() {

	//���݂̎������擾
	g_fps.NowTakeTime = GetNowHiPerformanceCount();

	//�f���^�^�C�����v�Z
	g_fps.Deltatime = (g_fps.NowTakeTime - g_fps.OldTakeTime) / MicroSecond;

	//���݂̎�����ۑ�
	g_fps.OldTakeTime = g_fps.NowTakeTime;

	//���݂�MAX�@�t���[���ڂȂ�
	if (g_fps.FrameConut == GameFPS) {

		//1�t���[���ځ`MAX�t���[���ڂ܂ł�̍��v���Ԃ��v�Z
		float TotalFrameTime = g_fps.NowTakeTime - g_fps.FirstTakeTime;

		//���v���Ԃ𗝑z��FPS�l�Ŋ����ĕ��ϒl���v�Z
		float CalcAverage = TotalFrameTime / GameFPS;
		//��b������̃t���[�����ɕϊ�
		g_fps.Average = MicroSecond / CalcAverage;

		//�P�v���[���ڂ̎������l��
		g_fps.FirstTakeTime = GetNowHiPerformanceCount();
		//�t���[�������P�ɖ߂�
		g_fps.FrameConut = 1;


	}

	else {

		//�t���[�������J�E���g�A�b�v
		g_fps.FrameConut++;

	}

	return;
}
  
//�`��
VOID FPSDraw() {

	

	DrawFormatString(50, 0, GetColor(255, 255, 255), "FPS:%3.1f", g_fps.Average);

	

	return ;
}

VOID FPSWait() {

	//���������Ƃ��ɑҋ@����~���b
	int wait = 0;


	//�҂����Ԃ��v��
	wait = MicroSecond / GameFPS * g_fps.FrameConut   //���z�̎���<
		- (g_fps.NowTakeTime - g_fps.FirstTakeTime);//���ۂ̎���

	//�}�C�N���b���~���b�ɕϊ�
	wait /= MillSecond;

	//�҂����Ԃ�����Ȃ��
	if (wait > 0 && wait <= WaitTImeMill) {

		//���b�Z�[�W���������Ȃ���҂�
		//WaitTimer(wait);

	}

	return;
}


