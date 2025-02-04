#include "ClearScene.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include"ClearScene.h"
#include "Score.h"
namespace
{
    const int TIMER = 100;
}

ClearScene::ClearScene(GameObject* parent) : GameObject(parent, "ClearScene")
{
    hBack_ = LoadGraph("Assets/Scene/CLEAR.png");
    assert(hBack_ > 0);

    hGameClear_ = LoadGraph("Assets/Font/GameClear1.png");
    assert(hGameClear_ > 0);

    //hTitleMenu = LoadGraph("Assets/UI/XboxBottunUI/titleMenu10.png");
    //hTitleMenu = LoadGraph("Assets/UI/XboxBottunUI/titleMenu20.png");
    //hTitleMenu = LoadGraph("Assets/UI/XboxBottunUI/titleMenuClear0.png");
    hTitleMenu_ = LoadGraph("Assets/UI/XboxBottunUI/titleMenu.png");
    assert(hTitleMenu_ > 0);

    hTitleMenuYellow_ = LoadGraph("Assets/UI/XboxBottunUI/titleMenu1.png");
    assert(hTitleMenuYellow_ > 0);

    keyTimer_ = TIMER;
    keyPushed_ = false;
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    ClearBGMHandle_ = LoadSoundMem("Assets/Music/BGM/CLEAR_BGM.mp3");
    assert(ClearBGMHandle_ != -1);

    DecisionHandle_ = LoadSoundMem("Assets/Music/SE/SceneSwitch/Clear.mp3");//決定時のSE
    assert(DecisionHandle_ != -1);

    PlaySoundMem(ClearBGMHandle_, DX_PLAYTYPE_BACK);
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
    padAnalogInput_ = GetJoypadXInputState(DX_INPUT_PAD1, &input_);
    // Cキーが押されたらスタートボタンでTitleSceneに遷移
    if (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_RETURN) || input_.Buttons[4] || input_.Buttons[13])
    {
        keyPushed_ = true;
        //PlaySoundMem(DecisionHandle,DX_PLAYTYPE_BACK);
        StopSoundMem(ClearBGMHandle_);
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
        DrawGraph(0, 0, hBack_, TRUE);
        DrawGraph(400, 240, hGameClear_, TRUE);
        DrawGraph(550, 380, hTitleMenuYellow_, TRUE);
        al = keyTimer_;
    }
    else
    {
        // 画面全体に背景画像を描画
        DrawGraph(0, 0, hBack_, TRUE);
        DrawGraph(400, 240, hGameClear_, TRUE);
        DrawGraph(550, 380, hTitleMenu_, TRUE);
    }
}

void ClearScene::Release()
{
    if (hBack_ > 0)
    {
        DeleteGraph(hBack_);
    }
    if (hGameClear_ > 0)
    {
        DeleteGraph(hGameClear_);
    }
    if (hTitleMenu_ > 0)
    {
        DeleteGraph(hTitleMenu_);
    }
    if (hTitleMenuYellow_ > 0)
    {
        DeleteGraph(hTitleMenuYellow_);
    }

    //SE BGM
    if (ClearBGMHandle_ > 0)
    {
        DeleteSoundMem(ClearBGMHandle_);
    }
    if (DecisionHandle_ > 0)
    {
        DeleteSoundMem(DecisionHandle_);
    }
}
