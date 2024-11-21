#include "ChooseLevelScene.h"
#include"Engine/SceneManager.h"

namespace
{
    const int TIMER = 100;
}
ChooseLevelScene::ChooseLevelScene(GameObject* parent)
	: GameObject(parent, "ChooseLevelScene"),hImage_(-1),Level_(0)
{
}

void ChooseLevelScene::Initialize()
{
	hImage_ = LoadGraph("Assets/Scene/Title.jpg");//タイトルの背景
	//assert(hImage_ >= 0);
}

void ChooseLevelScene::Update()
{
	padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);

	/*SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_PLAY);*/

    if (CheckHitKey(KEY_INPUT_A) /*|| input.Buttons[4]*/)
    {
        Level_ = 0;
    }
    if (CheckHitKey(KEY_INPUT_S) /*|| input.Buttons[4]*/)
    {
        Level_ = 100;
    }
    if (CheckHitKey(KEY_INPUT_D) /*|| input.Buttons[4]*/)
    {
        Level_ = 200;
    }


    // SPACEキーが押されたらスタートボタンでPlaySceneに遷移
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

}

void ChooseLevelScene::Draw()
{
    int screenWidth, screenHeight, colorBitDepth;
    GetScreenState(&screenWidth, &screenHeight, &colorBitDepth);

    if (keyPushed_)
    {
        static int al = TIMER;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, al);
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_, FALSE);
        al = keyTimer_;
    }
    else
        // 画面全体に背景画像を描画
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_, FALSE);

    DrawFormatString(0, 0, GetColor(0, 0, 0), "難易度: %d", Level_);
}

void ChooseLevelScene::Release()
{
}
