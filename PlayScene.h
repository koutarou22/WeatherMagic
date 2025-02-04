#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h";
#include"ChooseLevelScene.h"

class SceneManager;
class Player;

//�e�X�g�V�[�����Ǘ�����N���X
class PlayScene : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayScene(GameObject* parent);
	~PlayScene();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
private:
	int MapNumber_;//�ǂ�csv��ǂݍ��ނ�
	int MpPass; //Mp�̒l
	int StageBGMHandle; //BGM
	SceneManager* pSceneManager;
	Player* pPlayer;
};