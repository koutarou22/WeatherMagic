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
    hImage_ = LoadGraph("Assets/OIG3.jpg");
    assert(hImage_ >= 0);
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
    int x = (int)transform_.position_.x;
    int y = (int)transform_.position_.y;

    int screenWidth, screenHeight, colorBitDepth;
    GetScreenState(&screenWidth, &screenHeight, &colorBitDepth);

    // ��ʑS�̂ɔw�i�摜��`��
    DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_, FALSE);
    // �^�C�g����ʂ̃e�L�X�g��`��
    DrawString(0, 0, TITLE_TEXT, GetColor(255, 255, 255));
    
}

void TitleScene::Release()
{
}