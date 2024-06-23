#include "DxLib.h"
#include "TitleScene.h"
#include "TestScene.h"
#include "Engine/SceneManager.h"

// �^�C�g����ʂ̃e�L�X�g
const char* TITLE_TEXT = "Press SPACE to start";

TitleScene::TitleScene(GameObject* parent)
    : GameObject(parent, "TitleScene")
{
}

void TitleScene::Initialize()
{
}

void TitleScene::Update()
{
    // �X�y�[�X�L�[�������ꂽ��TestScene�ɑJ��
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TEST);
    }
}

void TitleScene::Draw()
{
    // �^�C�g����ʂ̃e�L�X�g��`��
    DrawString(0, 0, TITLE_TEXT, GetColor(255, 255, 255));
}

void TitleScene::Release()
{
}