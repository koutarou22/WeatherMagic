#pragma once
#include "Engine/GameObject.h"
class ChooseLevelScene :
    public GameObject
{
private:
	int hImage_;
	int Level_;//��Փx�i�I���ɂ���ēǂ݂���csv��ς���j
	int padAnalogInput;//xbox�̓��͂��󂯎��
	XINPUT_STATE input;//xbox�̓��͂��󂯎��

	int keyTimer_; //�L�[��������Ă���J�ڂ܂ł̃^�C�}�[
	bool keyPushed_; //�L�[�������ꂽ��(�Ó]OK��)�̃t���O

	enum StageLevelChoose
	{
		EASY = 0,
		NORMAL,
		HARD
	};
	StageLevelChoose chooselevel_;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ChooseLevelScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetLevel(int level) { Level_ = level; }
	int GetLevel() { return Level_; }
};

