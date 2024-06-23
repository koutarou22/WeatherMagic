#include "DxLib.h"
#include "TitleScene.h"
#include "TestScene.h"
#include "Engine/SceneManager.h"

// タイトル画面のテキスト
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
    // スペースキーが押されたらTestSceneに遷移
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TEST);
    }
}

void TitleScene::Draw()
{
    // タイトル画面のテキストを描画
    DrawString(0, 0, TITLE_TEXT, GetColor(255, 255, 255));
}

void TitleScene::Release()
{
}