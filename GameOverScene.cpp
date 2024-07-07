#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include"GameOverScene.h"

GameOverScene::GameOverScene(GameObject* parent) : GameObject(parent, "GameOverScene")
{
    // �R���X�g���N�^�̎���...
}

void GameOverScene::Initialize()
{
    // �Q�[���I�[�o�[�V�[���̏���������...
}

void GameOverScene::Update()
{
    // �X�y�[�X�L�[�������ꂽ��TitleScene�ɑJ��
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TITLE);
    }
}

void GameOverScene::Draw()
{
   
    DrawString(0, 0, "GAME OVER", GetColor(255, 255, 255));
    DrawString(0, 20, "Press SPACE to return to title", GetColor(255, 255, 255));
}

void GameOverScene::Release()
{
    
}