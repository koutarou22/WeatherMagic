#pragma once
#include"Engine/GameObject.h"
class StartScene :
    public GameObject
{
private:
    int hLogo_;    //�Q�[���̃��S
	int keyTimer_; //�J�ڂ܂ł̃^�C�}�[
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	StartScene(GameObject* parent);

	~StartScene();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

