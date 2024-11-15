#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include"GameOverScene.h"

GameOverScene::GameOverScene(GameObject* parent) : GameObject(parent, "GameOverScene")
{
    hImage_ = LoadGraph("Assets/Scene/GAME OVER1.png");
    assert(hImage_ > 0);
}

void GameOverScene::Initialize()
{
    // ゲームオーバーシーンの初期化処理...
}

void GameOverScene::Update()
{
    padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);
    // スペースキーが押されたらスタートボタンでTitleSceneに遷移
    if (CheckHitKey(KEY_INPUT_SPACE) || input.Buttons[14]) {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TITLE);
    }
}

void GameOverScene::Draw()
{
    DrawGraph(0, 0, hImage_, TRUE);
  /*  DrawString(0, 0, "GAME OVER", GetColor(255, 255, 255));
    DrawString(0, 20, "Press SPACE to return to title", GetColor(255, 255, 255));*/
}

void GameOverScene::Release()
{
    
}