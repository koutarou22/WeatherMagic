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
    hImage_ = LoadGraph("Assets/Scene/CLEAR.png");
    assert(hImage_ > 0);

    hGameClear_ = LoadGraph("Assets/Font/GameClear1.png");
    assert(hGameClear_ > 0);

    //hTitleMenu = LoadGraph("Assets/UI/XboxBottunUI/titleMenu10.png");
    //hTitleMenu = LoadGraph("Assets/UI/XboxBottunUI/titleMenu20.png");
    //hTitleMenu = LoadGraph("Assets/UI/XboxBottunUI/titleMenuClear0.png");
    hTitleMenu = LoadGraph("Assets/UI/XboxBottunUI/titleMenu.png");
    assert(hTitleMenu > 0);

    hTitleMenuYellow = LoadGraph("Assets/UI/XboxBottunUI/titleMenu1.png");
    assert(hTitleMenuYellow > 0);

    keyTimer_ = TIMER;
    keyPushed_ = false;
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    ClearBGMHandle = LoadSoundMem("Assets/Music/BGM/CLEAR_BGM.mp3");
    assert(ClearBGMHandle != -1);

    DecisionHandle = LoadSoundMem("Assets/Music/SE/SceneSwitch/Clear.mp3");//決定時のSE
    assert(DecisionHandle != -1);

    PlaySoundMem(ClearBGMHandle, DX_PLAYTYPE_BACK);
}

ClearScene::~ClearScene()
{
    Release();
}

void ClearScene::Initialize()
{
   Score* sc= Instantiate<Score>(this);//評価
   bool b = false;
   sc->SetPlaying(false);
}

void ClearScene::Update()
{
    padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);
    // Cキーが押されたらスタートボタンでTitleSceneに遷移
    if (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_RETURN) || input.Buttons[4] || input.Buttons[13])
    {
        keyPushed_ = true;
        //PlaySoundMem(DecisionHandle,DX_PLAYTYPE_BACK);
        StopSoundMem(ClearBGMHandle);
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

    //テスト用
  /*if (CheckHitKey(KEY_INPUT_SPACE))
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_LOAD);
    }*/
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
        DrawGraph(400, 240, hGameClear_, TRUE);
        DrawGraph(550, 380, hTitleMenuYellow, TRUE);
        al = keyTimer_;
    }
    else
    {
        // 画面全体に背景画像を描画
        DrawGraph(0, 0, hImage_, TRUE);
        DrawGraph(400, 240, hGameClear_, TRUE);
        DrawGraph(550, 380, hTitleMenu, TRUE);
    }
}

void ClearScene::Release()
{
    if (hImage_ > 0)
    {
        DeleteGraph(hImage_);
    }
    if (hGameClear_ > 0)
    {
        DeleteGraph(hGameClear_);
    }
    if (hTitleMenu > 0)
    {
        DeleteGraph(hTitleMenu);
    }
    if (hTitleMenuYellow > 0)
    {
        DeleteGraph(hTitleMenuYellow);
    }

    //SE BGM
    if (ClearBGMHandle > 0)
    {
        DeleteSoundMem(ClearBGMHandle);
    }
    if (DecisionHandle > 0)
    {
        DeleteSoundMem(DecisionHandle);
    }
}
