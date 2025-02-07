#include "DxLib.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "Engine/SceneManager.h"

// タイトル画面のテキスト
const char* TITLE_TEXT = "Press Space Key to start";
using std::string;

namespace
{
    const int TIMER = 255;
    const int STRING_TIMER = 100;
    const int FontSize = 32;
    const int TitleText_x = 520;
    const int TitleText_y = 405;
    const int TitleImage_x = 430;
    const int TitleImage_y = 260;
    const int StartImage_x = 560; 
    const int StartImage_y = 360;

    const int YELLOW = GetColor(255, 255, 0); //黄色
    const int WHITE = GetColor(255, 255, 255); //白
}

TitleScene::TitleScene(GameObject* parent)
    : GameObject(parent, "TitleScene")
{
    hBack_ = -1;
    hTitle_ = -1;
    SelectSEHandle_ = -1;
    hStart_ = -1;
    hStartYellow_ = -1;

    keyTimer_ = TIMER;
    keyPushed_ = false;

    LightingTimer_ = STRING_TIMER;
    Lightingend_ = false;

    CheckSelect_ = false;
    SetFontSize(FontSize / 2);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    TitleBGMHandle_ = LoadSoundMem("Assets/Music/BGM/TITLE_BGM.mp3");
    assert(TitleBGMHandle_ != -1);

    PlaySoundMem(TitleBGMHandle_, DX_PLAYTYPE_LOOP);
}

TitleScene::~TitleScene()
{
    Release();
}

void TitleScene::Initialize()
{
    hBack_ = LoadGraph("Assets/Scene/Title.png");//タイトルの背景
    assert(hBack_ >= 0);

    hTitle_ = LoadGraph("Assets/Font/Weather.png");//『WeatherMagic』のタイトルフォント
    assert(hTitle_ >= 0);

    SelectSEHandle_ = LoadSoundMem("Assets/Music/SE/SceneSwitch/select01.mp3");//Pを押した時に効果音がなる(登録)
    assert(SelectSEHandle_ != -1); // 音声ファイルの読み込みに失敗した場合のエラーチェック

    hStart_ = LoadGraph("Assets/UI/XboxBottunUI/startMenu.png");
    assert(hStart_ > 0);

    hStartYellow_ = LoadGraph("Assets/UI/XboxBottunUI/startMenuYellow.png");
    assert(hStartYellow_ > 0);
}

void TitleScene::Update()
{
    padAnalogInput_ = GetJoypadXInputState(DX_INPUT_PAD1, &input_);

    // スペースキーが押されるかスタートボタンでPlaySceneに遷移
    if (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_RETURN) || input_.Buttons[4] || input_.Buttons[13])
    {
        StopSoundMem(TitleBGMHandle_);

        if (!CheckSelect_)
        {
            PlaySoundMem(SelectSEHandle_, DX_PLAYTYPE_BACK);
            CheckSelect_ = true; //ここで一回しか鳴らせない
        }
      
        keyPushed_ = true;
    }

    if (keyPushed_)
    {
        if (Lightingend_)
        {
            keyTimer_--;
        }
        else
        {
            LightingTimer_--;
        }
    }

    //タイマーが終わったら(暗転が終わったら)
    if (keyTimer_ < 0)
    {
        SetFontSize(FontSize); //もとにもどす
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_LEVEL);
    }

    //文字タイマーが終わったら(ぴかぴか終わったら)
    if (LightingTimer_ < 0)
    {
        Lightingend_ = true;
    }
}

void TitleScene::Draw()
{
    int x = (int)transform_.position_.x;
    int y = (int)transform_.position_.y;

    int screenWidth, screenHeight, colorBitDepth;
    GetScreenState(&screenWidth, &screenHeight, &colorBitDepth);
  
//押したらすぐ暗転していく
#if 0
    if (keyPushed_)
    {
        static int al = TIMER;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, al);
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hBack_, FALSE);
        al = keyTimer_;
    }
    else
    {
        // 画面全体に背景画像を描画
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hBack_, FALSE);
        // タイトル画面のテキストを描画
        DrawString(700, 150, TITLE_TEXT, GetColor(255, 255, 255));
        DrawGraph(600, 40, hTitle_, TRUE);
    }
#endif

//押したらPush P~がちょっと光って暗転
#if 1
    if (keyPushed_&&Lightingend_) //文字ぴかぴか終わった
    {
        SetFontSize(16);
        static int al = TIMER;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, al);
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hBack_, FALSE);
        al = keyTimer_;
    }
    else if(keyPushed_&&!Lightingend_) //文字ぴかぴかさせている
    {
        // 画面全体に背景画像を描画
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hBack_, FALSE);
        // タイトル画面のテキストを描画
        DrawString(TitleText_x, TitleText_y, TITLE_TEXT, YELLOW);//黄色
        DrawGraph(TitleImage_x, TitleImage_y, hTitle_, TRUE);
        DrawGraph(StartImage_x, StartImage_y, hStartYellow_, TRUE);
    }
    else //そもそもキーが押されてない
    {
        // 画面全体に背景画像を描画
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hBack_, FALSE);
        // タイトル画面のテキストを描画
        DrawString(TitleText_x, TitleText_y, TITLE_TEXT, WHITE);//白
        DrawGraph(TitleImage_x, TitleImage_y, hTitle_, TRUE);
        DrawGraph(StartImage_x, StartImage_y, hStart_, TRUE);
    }
#endif
}

void TitleScene::Release()
{
    if (hStartYellow_ > 0)
    {
        DeleteGraph(hStartYellow_);
    }
    if (hStart_ > 0)
    {
        DeleteGraph(hStart_);
    }
    if (hTitle_ > 0)
    {
        DeleteGraph(hTitle_);
    }
    if (hBack_ > 0)
    {
        DeleteGraph(hBack_);
    }
    if (TitleBGMHandle_ > 0)
    {
        DeleteSoundMem(TitleBGMHandle_);
    }
    if (SelectSEHandle_ > 0)
    {
        DeleteSoundMem(SelectSEHandle_);
    }

}
