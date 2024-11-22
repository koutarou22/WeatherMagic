#include "StartScene.h"
#include "DxLib.h"
#include "TitleScene.h"
#include "Engine/SceneManager.h"

namespace
{
    const int TIMER = 100;
}

StartScene::StartScene(GameObject* parent)
    :GameObject(parent,"StartScene"),hImage_(-1)
{
}

StartScene::~StartScene()
{
}

void StartScene::Initialize()
{
    hImage_ = LoadGraph("Assets/Scene/WeatherMagicLogo.jpeg");//ƒ^ƒCƒgƒ‹‚Ì”wŒi
    assert(hImage_ >= 0);

}

void StartScene::Update()
{
    keyTimer_--;
    if (keyTimer_ < 0)
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TITLE);
    }
}

void StartScene::Draw()
{  
    static int al = TIMER;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, al);
        DrawGraph(0, 0, hImage_, TRUE);
        al = keyTimer_;
    
}

void StartScene::Release()
{
}
