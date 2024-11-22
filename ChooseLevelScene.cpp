#include "ChooseLevelScene.h"
#include"Engine/SceneManager.h"

namespace
{
    const int TIMER = 100;
    const int SCREENSIZE_HALF = 610;
    const int CURSOR_POINT = 580;
}
int ChooseLevelScene::Previous(int level)
{
	if(level_arr.empty()) 
        return -1;  // 配列が空の場合

	// インデックスが0なら、前の要素は配列の最後の要素（2の場合は0）
	return level_arr[(currentlevel - 1 + level_arr.size()) % level_arr.size()];
}

int ChooseLevelScene::Next(int currentIndex)
{
	if (level_arr.empty())
        return -1;  // 配列が空の場合

	// インデックスが最後なら、次は最初の要素（2の場合は0）
	return level_arr[(currentIndex + 1) % level_arr.size()];
}
ChooseLevelScene::ChooseLevelScene(GameObject* parent)
    : GameObject(parent, "ChooseLevelScene"), hImage_back(-1), keyPushed_(false), keyTimer_(TIMER),
    prevUp(false),prevDown(false)
{
    SetFontSize(32);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    level_arr.push_back(EASY);
    level_arr.push_back(NORMAL);
    level_arr.push_back(HARD);

    LevelText1 = "EASY";
    LevelText2 = "NORMAL";
    LevelText3 = "HARD";

}

void ChooseLevelScene::Initialize()
{
	hImage_back = LoadGraph("Assets/Scene/ChooseLevelBack.png");//タイトルの背景
	assert(hImage_back >= 0);

    hDecideB = LoadGraph("Assets/UI/XboxBottunUI/decideB3.png");//B決定のUI
    assert(hDecideB > 0);
}

void ChooseLevelScene::Update()
{
	padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);

	/*SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_PLAY);*/

    //if (CheckHitKey(KEY_INPUT_A) /*|| input.Buttons[4]*/)
    //{
    //    Level_ = 0;
    //    chooselevel_ = EASY;
    //}
    //if (CheckHitKey(KEY_INPUT_S) /*|| input.Buttons[4]*/)
    //{
    //    Level_ = 100;
    //    chooselevel_ = NORMAL;
    //}
    //if (CheckHitKey(KEY_INPUT_D) /*|| input.Buttons[4]*/)
    //{
    //    Level_ = 200;
    //    chooselevel_ = HARD;
    //}

    
    if (CheckHitKey(KEY_INPUT_UP) || input.Buttons[0] || input.ThumbLY >= 15000 )
    {
        if (!prevUp) 
        {
            currentlevel = Previous(currentlevel);
        }
        prevUp = true;
    }
    else {
        prevUp = false;
    }
 
    if (CheckHitKey(KEY_INPUT_DOWN) || input.Buttons[1] || input.ThumbLY <= -15000)
    {
        if (!prevDown)
        {
            currentlevel = Next(currentlevel);
        }
        prevDown = true;
    }
    else
    {
        prevDown = false;
    }


    // SPACEキーorStartボタンorBボタンが押されたらスタートボタンでPlaySceneに遷移
    if (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_RETURN) || input.Buttons[4] || input.Buttons[13])
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
        //SetFontSize(32); //もとにもどす
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->SetLevelManager(currentlevel);
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
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_back, FALSE);
        DrawGraph(570, 600, hDecideB, TRUE);//中央下
        //DrawGraph(0, 350, hDecideB, TRUE);//難易度の下
        al = keyTimer_;
    }
    else
    {
        // 画面全体に背景画像を描画
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_back, FALSE);
        DrawGraph(570, 600, hDecideB, TRUE);//中央下
        //DrawGraph(0, 350, hDecideB, TRUE);//難易度の下
    }


    DrawFormatString(0, 0, GetColor(255, 255, 255), "難易度を選択してください");
    //DrawFormatString(0, 120, GetColor(255, 255, 255), "難易度： %d", currentlevel);

    if (!keyPushed_) {
        switch (currentlevel)
        {
        case 0:
            DrawFormatString(CURSOR_POINT, 200, GetColor(255, 255, 255), "*");
            break;
        case 1:
            DrawFormatString(CURSOR_POINT, 250, GetColor(255, 255, 255), "*");
            break;
        case 2:
            DrawFormatString(CURSOR_POINT, 300, GetColor(255, 255, 255), "*");
            break;
        default:
            break;
        }
    }

    DrawFormatString(SCREENSIZE_HALF, 200, GetColor(255, 255, 255), LevelText1);
    DrawFormatString(SCREENSIZE_HALF, 250, GetColor(255, 255, 255), LevelText2);
    DrawFormatString(SCREENSIZE_HALF, 300, GetColor(255, 255, 255), LevelText3);
}

void ChooseLevelScene::Release()
{
    DeleteGraph(hDecideB);
    DeleteGraph(hImage_back);
}
