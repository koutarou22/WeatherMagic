#include "ClearScene.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include"ClearScene.h"

ClearScene::ClearScene(GameObject* parent) : GameObject(parent, "ClearScene")
{
    hImage_ = LoadGraph("Assets/Scene/GAME CLEAR.png");
    assert(hImage_ > 0);
}

void ClearScene::Initialize()
{
}

void ClearScene::Update()
{
    if (CheckHitKey(KEY_INPUT_SPACE)) {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TITLE);
    }
}

void ClearScene::Draw()
{
    /*DrawString(0, 0, "Clear", GetColor(255, 255, 255));
    DrawString(0, 20, "Press SPACE to return to title", GetColor(255, 255, 255));*/
    DrawGraph(0, 0, hImage_, TRUE);
}

void ClearScene::Release()
{

}
