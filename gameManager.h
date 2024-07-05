//�Q�[�������p�̃w�b�_�[�t�@�C��

#pragma once

#include "DxLib.h"

#define WINDOW_WIDTH         (800) //��
#define WINDOW_HEIGHT        (600) //�c
#define WINDOW_BIT           (32)  //�J���[�r�b�g��
						     	   
#define ONE_SIZE             (40)  //�}�X�̃T�C�Y�@
#define HEIGHT_SQUARE_CNT    (20)  //���@
#define WIDTHSQUARE_CNT      (15)  //�c
#define SQUARE_CNT           (300) // �}�X�̐�.  ���Q�O�@�c�P�T
#define BOARD_SIZE           (ONE_SIZE*SQUARE_CNT)//�`�悷��Ֆʂ̏c���T�C�Y.
						     
						     
#define GAME_DEBUG           TRUE  //�f�o�b�O���[�h   

#define GAME_SCENE_COUNT     (4)   //�Q�[���V�[���̐�
#define GAME_SCENE_NAME_MAX  (25)  //�Q�[���V�[�����̕�����MAX
#define FLAG_GAME_SCENE      (0)   //�P�̏ꍇ�Q�[���V�[���ɓ����ȊO�̏ꍇ����Ȃ�
#define SHOW_ENDING          (0)   //�Q�[���N���A���ƂɌĂяo���@
#define SHOW_GAME_OVER       (0)   //�Q�[���I�[�o�[���Ăяo��

//�񋓌^

//�؂�ւ��p�̃V�[��
enum tagE_GAME_SCENE {

	TITLE_SCENE,    //�^�C�g���V�[��
	PLAY_SCENE,     //�Q�[���V�[��
	END_SCENE,      //�G���h�V�[��

};

//�O���̃O���[�o���ϐ�

extern enum tagE_GAME_SCENE nowGameScene;//���݂̃Q�[���V�[��

 

//�O���v���g�^�C�v�錾

extern VOID TitleInit();//�^�C�g��������
extern VOID TitleCtrl();//�^�C�g���Ǘ�
extern VOID TitleProc();//�^�C�g������
extern VOID TitleDraw();//�^�C�g���`��

extern VOID LoadInit();//���[�h������
extern VOID LoadCtrl();//���[�h���Ǘ�
extern VOID LoadProc();//���[�h������
extern VOID LoadDraw();//���[�h���`��



extern VOID PlayInit();//�Q�[����������
extern VOID PlayCtrl();//�Q�[�����Ǘ�
extern VOID PlayProc();//�Q�[��������
extern VOID PlayDraw();//�Q�[�����`��
 
extern VOID EndInit();//�G���f�B���O������
extern VOID EndCtrl();//�G���f�B���O�Ǘ�
extern VOID EndProc();//�G���f�B���O����
extern VOID EndDraw();//�G���f�B���O�`��