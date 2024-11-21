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
    const int MOJI_TIMER = 100;
}

TitleScene::TitleScene(GameObject* parent)
    : GameObject(parent, "TitleScene")
{
    hImage_ = -1;
    charImage_ = -1;
    spaceImage_ = -1;
    soundHandle = -1;

    keyTimer_ = TIMER;
    keyPushed_ = false;

    mojiTimer_ = MOJI_TIMER;
    mojiend_ = false;

    SetFontSize(16);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    hStart = -1;
    hStartYellow = -1;
}

void TitleScene::Initialize()
{
    hImage_ = LoadGraph("Assets/Scene/Title.jpg");//タイトルの背景
    assert(hImage_ >= 0);

    charImage_ = LoadGraph("Assets/Font/Weather.png");//『WeatherMagic』のタイトルフォント
    assert(charImage_ >= 0);

   /* spaceImage_ = LoadGraph("Assets/Space.png");//『space』を押してくれ！的なフォント　結局未使用
    assert(spaceImage_ >= 0);*/

    soundHandle = LoadSoundMem("Assets/Music/SE/select01.mp3");//Pを押した時に効果音がなる(登録)
    assert(soundHandle != -1); // 音声ファイルの読み込みに失敗した場合のエラーチェック

    hStart = LoadGraph("Assets/UI/XboxBottunUI/startMenu.png");
    assert(hStart > 0);

    hStartYellow = LoadGraph("Assets/UI/XboxBottunUI/startMenuYellow.png");
    assert(hStartYellow > 0);
}

void TitleScene::Update()
{
    padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);

    // スペースキーが押されるかスタートボタンでPlaySceneに遷移
    if (CheckHitKey(KEY_INPUT_SPACE) || input.Buttons[4]) {
        PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK); // 音声を再生
        keyPushed_ = true;
    }

    if (keyPushed_)
    {
        if (mojiend_)
        {
            keyTimer_--;
        }
        else
        {
            mojiTimer_--;
        }
    }

    //タイマーが終わったら(暗転が終わったら)
    if (keyTimer_ < 0)
    {
        SetFontSize(32); //もとにもどす
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_LEVEL);
        PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
    }

    //文字タイマーが終わったら(ぴかぴか終わったら)
    if (mojiTimer_ < 0)
    {
        mojiend_ = true;
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
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_, FALSE);
        al = keyTimer_;
    }
    else
    {
        // 画面全体に背景画像を描画
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_, FALSE);
        // タイトル画面のテキストを描画
        DrawString(700, 150, TITLE_TEXT, GetColor(255, 255, 255));
        DrawGraph(600, 40, charImage_, TRUE);
    }
#endif

//押したらPush P~がちょっと光って暗転
#if 1
    if (keyPushed_&&mojiend_) //文字ぴかぴか終わった
    {
        SetFontSize(16);
        static int al = TIMER;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, al);
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_, FALSE);
        al = keyTimer_;
    }
    else if(keyPushed_&&!mojiend_) //文字ぴかぴかさせている
    {
        //SetFontSize(18); //一瞬文字が大きく協調されます
        // 画面全体に背景画像を描画
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_, FALSE);
        // タイトル画面のテキストを描画
        DrawString(700, 150, TITLE_TEXT, GetColor(255, 255, 0));//黄色
        DrawGraph(600, 40, charImage_, TRUE);
        DrawGraph(920, 130, hStartYellow, TRUE);
    }
    else //そもそもキーが押されてない
    {
        // 画面全体に背景画像を描画
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_, FALSE);
        // タイトル画面のテキストを描画
        DrawString(700, 150, TITLE_TEXT, GetColor(255, 255, 255));//白
        DrawGraph(600, 40, charImage_, TRUE);
        DrawGraph(920, 130, hStart, TRUE);
    }
#endif
}

void TitleScene::Release()
{
}