#pragma once
#include "Engine/GameObject.h"

class GameOverScene : public GameObject
{
	int hImage_;
	int padAnalogInput;//xbox�̓��͂��󂯎��
	XINPUT_STATE input;//xbox�̓��͂��󂯎��
	int keyTimer_; //�L�[��������Ă���J�ڂ܂ł̃^�C�}�[
	bool keyPushed_; //�L�[�������ꂽ��(�Ó]OK��)�̃t���O

	int GameOverBGMHandle;

	//�J�ڗp
	bool isLeft; //true:Retry(left) false:Title(right)
	void DrawScene(); //�J�ڂ̕����Ƃ��摜�Ƃ��p
	void ChangeScene(); //�V�[���J�ڎ��ۂɂ���Ƃ���
	void CheckRL(); //���E�̔���
 
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	GameOverScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};