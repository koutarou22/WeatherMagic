#pragma once
#include "Engine/GameObject.h"

class TitleScene : public GameObject
{
private:
	int hImage_;
	int charImage_;
	int spaceImage_;
	int soundHandle;
	int padAnalogInput;//xbox�̓��͂��󂯎��
	XINPUT_STATE input;//xbox�̓��͂��󂯎��
	int keyTimer_; //�L�[��������Ă���J�ڂ܂ł̃^�C�}�[
	bool keyPushed_; //�L�[�������ꂽ��(�Ó]OK��)�̃t���O
	int mojiTimer_; //�������҂��҂�����^�C�}�[
	bool mojiend_; //�҂��҂��I��肩�ȃt���O
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

};

