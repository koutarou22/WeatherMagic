#include "ClearScene.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include"ClearScene.h"
#include "Score.h"

//ここに星を書く追加予定

ClearScene::ClearScene(GameObject* parent) : GameObject(parent, "ClearScene")
{
    hImage_ = LoadGraph("Assets/Scene/GAME CLEAR2.png");
    assert(hImage_ > 0);
}

void ClearScene::Initialize()
{
    Instantiate<Score>(this);//評価
}

void ClearScene::Update()
{
    padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);
    // Cキーが押されたらスタートボタンでTitleSceneに遷移
    if (CheckHitKey(KEY_INPUT_X) || input.Buttons[14]) 
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TITLE);
    }
}

void ClearScene::Draw()
{
    /*DrawString(0, 0, "Clear", GetColor(255, 255, 255));
    DrawString(0, 20, "Press SPACE to return to title", GetColor(255, 255, 255));*/
    DrawGraph(0, 0, hImage_, TRUE);

    //SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
    //int mp = pSceneManager->GetMagicPoint();//GetMp
    //
    ////Imaha Kantan na Syori
    //if (mp > 80)
    //{
    //    DrawFormatString(200, 60, GetColor(0, 255, 0), "評価☆3");
    //}
    //else if (mp > 60)
    //{
    //    DrawFormatString(200, 60, GetColor(0, 255, 0), "評価☆2");
    //}
    //else 
    //{
    //    DrawFormatString(200, 60, GetColor(0, 255, 0), "評価☆1");
    //}

}

void ClearScene::Release()
{
}
