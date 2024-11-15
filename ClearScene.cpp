#include "ClearScene.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include"ClearScene.h"
#include "Score.h"

//ここに星を書く追加予定

namespace
{
    const int TIMER = 100;
}

ClearScene::ClearScene(GameObject* parent) : GameObject(parent, "ClearScene")
{
    hImage_ = LoadGraph("Assets/Scene/GAME CLEAR2.png");
    assert(hImage_ > 0);

    keyTimer_ = TIMER;
    keyPushed_ = false;
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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
        keyPushed_ = true;
    }

    if (keyPushed_)
    {

        keyTimer_--;
    }

    //タイマーが終わったら(暗転が終わったら)
    if (keyTimer_ < 0)
    {
        SetFontSize(32); //もとにもどす
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TITLE);
    }
}

void ClearScene::Draw()
{
    /*DrawString(0, 0, "Clear", GetColor(255, 255, 255));
    DrawString(0, 20, "Press SPACE to return to title", GetColor(255, 255, 255));*/
    if (keyPushed_)
    {
        static int al = TIMER;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, al);
        DrawGraph(0, 0, hImage_, TRUE);
        al = keyTimer_;
    }
    else
    {
        // 画面全体に背景画像を描画
        DrawGraph(0, 0, hImage_, TRUE);
    }

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
