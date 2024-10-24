#include "ClearScene.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include"ClearScene.h"
#include "Score.h"

//‚±‚±‚É¯‚ğ‘‚­’Ç‰Á—\’è

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

    Instantiate<Score>(this);//•]‰¿

    if (CheckHitKey(KEY_INPUT_C))
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
    //    DrawFormatString(200, 60, GetColor(0, 255, 0), "•]‰¿™3");
    //}
    //else if (mp > 60)
    //{
    //    DrawFormatString(200, 60, GetColor(0, 255, 0), "•]‰¿™2");
    //}
    //else 
    //{
    //    DrawFormatString(200, 60, GetColor(0, 255, 0), "•]‰¿™1");
    //}

}

void ClearScene::Release()
{
}
