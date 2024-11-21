#include "LoadScene.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Score.h"
#include "Field.h"

//ここに星を書く追加予定

namespace
{
    const int TIMER = 100;
}

LoadScene::LoadScene(GameObject* parent) : GameObject(parent, "LoadScene")
{
    hImage_ = LoadGraph("Assets/Scene/LOADTEST.png");
    assert(hImage_ > 0);

    keyTimer_ = TIMER;
    keyPushed_ = false;
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void LoadScene::Initialize()
{
}

void LoadScene::Update()
{
    padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);
    // Cキーが押されたらスタートボタンでTitleSceneに遷移
    if (CheckHitKey(KEY_INPUT_SPACE) || input.Buttons[4])
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
        pSceneManager->ChangeScene(SCENE_ID_PLAY);
    }

    //テスト用
  /*if (CheckHitKey(KEY_INPUT_SPACE))
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_LOAD);
    }*/
}

void LoadScene::Draw()
{
    /*DrawString(0, 0, "Load", GetColor(255, 255, 255));
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
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        // 画面全体に背景画像を描画
        DrawGraph(0, 0, hImage_, TRUE);
       // DrawString(100, 100, "現在ロード画面にいます", GetColor(255, 255, 255));
        switch (pSceneManager->GetClearCount())
        {
        case 0:
            DrawString(0, 100, "1-1", GetColor(255, 255, 255));
            DrawString(0, 120, "はじまりの大地", GetColor(255, 255, 255));
            break;
        case 100:
            DrawString(0, 100, "2-2", GetColor(255, 255, 255));
            DrawString(0, 100, "落としの谷", GetColor(255, 255, 255));
            break;
        case 200:
            DrawString(0, 100, "Stage3 Final Stage", GetColor(255, 255, 255));
            DrawString(0, 120, "不気味な森林", GetColor(255, 255, 255));
            break;
        default:
            DrawString(0, 100, "終わりだよ！なにもないよ！", GetColor(255, 255, 255));
            break;
        }
    }
}

void LoadScene::Release()
{
}
