#include "StartScene.h"
#include "DxLib.h"
#include "TitleScene.h"
#include "Engine/SceneManager.h"

namespace
{
    const int TIMER = 512;
}

StartScene::StartScene(GameObject* parent)
    :GameObject(parent,"StartScene"),hImage_(-1),keyTimer_(TIMER)
{
}

StartScene::~StartScene()
{
    Release();
}

void StartScene::Initialize()
{
    hImage_ = LoadGraph("Assets/Scene/GameLogoBack.png");//ƒQ[ƒ€‚ÌƒƒS
    assert(hImage_ >= 0);

}

void StartScene::Update()
{
    keyTimer_ -= 5;
    if (keyTimer_ < 0)
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TITLE);
    }
}

void StartScene::Draw()
{  
    //static int al = TIMER;
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, keyTimer_);
    DrawGraph(0, 0, hImage_, TRUE);
    
}

void StartScene::Release()
{
    if (hImage_ > 0)
    {
        DeleteGraph(hImage_);
    }
}
