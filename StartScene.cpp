#include "StartScene.h"
#include "DxLib.h"
#include "TitleScene.h"
#include "Engine/SceneManager.h"

namespace
{
    const int TIMER = 512;
}

StartScene::StartScene(GameObject* parent)
    :GameObject(parent,"StartScene"),hLogo_(-1),keyTimer_(TIMER)
{
}

StartScene::~StartScene()
{
    Release();
}

void StartScene::Initialize()
{
    hLogo_ = LoadGraph("Assets/Scene/GameLogoBack.png");//ゲームのロゴ
    assert(hLogo_ >= 0);

}

void StartScene::Update()
{
    //ロゴを大きく表示してから徐々に透過させていく
    keyTimer_ -= 5;
    if (keyTimer_ < 0)
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TITLE);
    }
}

void StartScene::Draw()
{  
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, keyTimer_);
    DrawGraph(0, 0, hLogo_, TRUE); 
}

void StartScene::Release()
{
    if (hLogo_ > 0)
    {
        DeleteGraph(hLogo_);
    }
}
