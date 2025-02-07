#pragma once
#include "Engine/GameObject.h"

class GameOverScene : public GameObject
{
	int hBack_;//�w�i
	int hDecideB_;//����UI
	int hDecideBYellow_;//����UI�i���F�j
	int padAnalogInput;//xbox�̓��͂��󂯎��
	XINPUT_STATE input;//xbox�̓��͂��󂯎��
	int keyTimer_; //�L�[��������Ă���J�ڂ܂ł̃^�C�}�[
	bool keyPushed_; //�L�[�������ꂽ��(�Ó]OK��)�̃t���O

	int GameOverBGMHandle_;

	//�J�ڗp
	bool isLeft_; //true:Retry(left) false:Title(right)
	void DrawScene(); //�J�ڂ̕����Ƃ��摜�p
	void ChangeScene(); //�V�[���J�ڎ��ۂɂ���Ƃ���
	void CheckRL(); //���E�̔���


	bool RightCheck_;//�E������������ĉ����o��̂�h���p
	bool LeftCheck_; //��������������ĉ����o��̂�h���p
	int SelectSEHandle_;//�I��pSE
	int DecisionHandle_;//����pSE
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	GameOverScene(GameObject* parent);
	~GameOverScene();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};