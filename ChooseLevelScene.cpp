#include "ChooseLevelScene.h"
#include"Engine/SceneManager.h"

namespace
{
    const int TIMER = 100;
    const int SCREENSIZE_HALF = 610;//スクリーンの中央
    const int CURSOR_POINT = 580;   //"*"の位置

    const int DecideB_x = 570;      //決定ボタンのx座標
    const int DecideB_y = 600;      //決定ボタンのy座標

    const int Easy_y = 200; //Easyのy座標
    const int Normal_y = 250;//Normalのy座標
    const int Hard_y = 300;//Hardのy座標

    const int WHITE = GetColor(255, 255, 255); //白
    const int FontSize = 32;
}

/// <summary>
/// 難易度配列の中からひとつ前にアクセス
/// </summary>
/// <param name="level">今のcurrentlevel_</param>
/// <returns>level_arr_[]の前の値</returns>
int ChooseLevelScene::Previous(int level)
{
	if(level_arr_.empty()) 
        return -1;  // 配列が空の場合

    // インデックスのひとつ前
	// インデックスが0なら、前の要素は配列の最後の要素（2の場合は0）
	return level_arr_[(currentlevel_ - 1 + level_arr_.size()) % level_arr_.size()];
}

/// <summary>
/// 難易度配列の中からひとつ次にアクセス
/// </summary>
/// <param name="currentIndex">今のcurrentlevel_</param>
/// <returns>level_arr_[]の次の値</returns>
int ChooseLevelScene::Next(int currentIndex)
{
	if (level_arr_.empty())
        return -1;  // 配列が空の場合

    // インデックスのひとつ先
	// インデックスが最後なら、次は最初の要素（2の場合は0）
	return level_arr_[(currentIndex + 1) % level_arr_.size()];
}

ChooseLevelScene::ChooseLevelScene(GameObject* parent)
    : GameObject(parent, "ChooseLevelScene"), hBack_(-1),hLevelFont_(-1),hDecideB_(-1),
    hDecideByellow_(-1),SelectSEHandle_(-1),DecisionHandle_(-1),
    keyPushed_(false), keyTimer_(TIMER),
    currentlevel_(0),prevUp_(false),prevDown_(false)
{
    SetFontSize(FontSize);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    level_arr_.push_back(EASY);
    level_arr_.push_back(NORMAL);
    level_arr_.push_back(HARD);

    LevelText1_ = "EASY";
    LevelText2_ = "NORMAL";
    LevelText3_ = "HARD";
      
    CheckDecision_ = false;
}

ChooseLevelScene::~ChooseLevelScene()
{
    Release();
}

void ChooseLevelScene::Initialize()
{
	hBack_ = LoadGraph("Assets/Scene/Back.jpg");//タイトルの背景
	assert(hBack_ > 0);

    hLevelFont_ = LoadGraph("Assets/Font/Level1.png");//難易度を選択してくださいのfont
    assert(hLevelFont_ > 0);

    hDecideB_ = LoadGraph("Assets/UI/XboxBottunUI/decideB3.png");//B決定のUI
    assert(hDecideB_ > 0);

    hDecideByellow_ = LoadGraph("Assets/UI/XboxBottunUI/decideB2.png");//B決定のUI（黄色）
    assert(hDecideByellow_ > 0);

    SelectSEHandle_ = LoadSoundMem("Assets/Music/SE/Select/Select0.mp3");//選択時のSE
    assert(SelectSEHandle_ > 0);

    DecisionHandle_ = LoadSoundMem("Assets/Music/SE/SceneSwitch/Select02.mp3");//選択時のSE
    assert(DecisionHandle_ > 0);

}

void ChooseLevelScene::Update()
{
	padAnalogInput_ = GetJoypadXInputState(DX_INPUT_PAD1, &input_);

    if (CheckHitKey(KEY_INPUT_UP) || input_.Buttons[0] || input_.ThumbLY >= 15000 )
    {
        if (!prevUp_)
        {
            currentlevel_ = Previous(currentlevel_);
            PlaySoundMem(SelectSEHandle_, DX_PLAYTYPE_BACK);
        }
        prevUp_ = true;
    }
    else {
        prevUp_ = false;
    }
 
    if (CheckHitKey(KEY_INPUT_DOWN) || input_.Buttons[1] || input_.ThumbLY <= -15000)
    {
        if (!prevDown_)
        {
            currentlevel_ = Next(currentlevel_);
            PlaySoundMem(SelectSEHandle_, DX_PLAYTYPE_BACK);
        }
        prevDown_ = true;
    }
    else
    {
        prevDown_ = false;
    }


    // SPACEキーorStartボタンorBボタンが押されたらスタートボタンでPlaySceneに遷移
    if (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_RETURN) || input_.Buttons[4] || input_.Buttons[13])
    {
        keyPushed_ = true;

        if (!CheckDecision_)
        {
            PlaySoundMem(DecisionHandle_, DX_PLAYTYPE_BACK);

            CheckDecision_ = true;
        }
    }

    if (keyPushed_)
    {
        keyTimer_--;
    }


    //タイマーが終わったら(暗転が終わったら)
    if (keyTimer_ < 0)
    {
        //SceneManagerに値を渡す(実際のcsvの読み込みはFieldクラスが行う)
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->SetLevelManager(currentlevel_);
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
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hBack_, FALSE);
        DrawGraph(DecideB_x, DecideB_y, hDecideByellow_, TRUE);//中央下
        //DrawGraph(0, 350, hDecideByellow, TRUE);//難易度の下
        al = keyTimer_;
    }
    else
    {
        // 画面全体に背景画像を描画
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hBack_, FALSE);
        DrawGraph(DecideB_x, DecideB_y, hDecideB_, TRUE);//中央下
        //DrawGraph(0, 350, hDecideB, TRUE);//難易度の下
    }


  //  DrawFormatString(0, 0, GetColor(255, 255, 255), "難易度を選択してください");
  //DrawFormatString(0, 120, GetColor(255, 255, 255), "難易度： %d", currentlevel);

    if (!keyPushed_) {
        switch (currentlevel_)
        {
        case 0:
            DrawFormatString(CURSOR_POINT, Easy_y, WHITE, "*");
            break;
        case 1:
            DrawFormatString(CURSOR_POINT, Normal_y, WHITE, "*");
            break;
        case 2:
            DrawFormatString(CURSOR_POINT, Hard_y, WHITE, "*");
            break;
        default:
            break;
        }
    }


    DrawGraph(0, 0, hLevelFont_, TRUE);//難易度を選択してくださいのフォント
    DrawFormatString(SCREENSIZE_HALF, Easy_y,   WHITE, LevelText1_);
    DrawFormatString(SCREENSIZE_HALF, Normal_y, WHITE, LevelText2_);
    DrawFormatString(SCREENSIZE_HALF, Hard_y,   WHITE, LevelText3_);

}

void ChooseLevelScene::Release()
{
    if (hBack_ > 0)
    {
        DeleteGraph(hBack_);
    }
    if (hLevelFont_ > 0)
    {
        DeleteGraph(hLevelFont_);
    }
    if (hDecideB_ > 0)
    {
        DeleteGraph(hDecideB_);
    }
    if (hDecideByellow_ > 0)
    {
        DeleteGraph(hDecideByellow_);
    }

    //SE
    if (SelectSEHandle_ > 0)
    {
        DeleteSoundMem(SelectSEHandle_);
    }
    if (DecisionHandle_ > 0)
    {
        DeleteSoundMem(DecisionHandle_);
    }
}
