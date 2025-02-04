#include "Weather.h"
#include "Player.h"
#include "WeatherBackGround.h"

Weather::~Weather()
{
}

void Weather::Initialize()
{
    //背景の画像
    hWeatherEffect_[0] = LoadGraph("Assets/BackImage/Sky.png");
    assert(hWeatherEffect_[0] > 0);

    hWeatherEffect_[1] = LoadGraph("Assets/BackImage/Rain.png");
    assert(hWeatherEffect_[1] > 0);

    hWeatherEffect_[2] = LoadGraph("Assets/BackImage/Wind.png");
    assert(hWeatherEffect_[2] > 0);

    hWeatherEffect_[3] = LoadGraph("Assets/BackImage/Snow.png");
    assert(hWeatherEffect_[3] > 0);

    
    //天候のアイコン
    hWeatherIcon_[0] = LoadGraph("Assets/UI/Sun.png");
    assert(hWeatherIcon_[0] > 0);

    hWeatherIcon_[1] = LoadGraph("Assets/UI/Rain1.png");
    assert(hWeatherIcon_[1] > 0);

    hWeatherIcon_[2] = LoadGraph("Assets/UI/Gale.png");
    assert(hWeatherIcon_[2] > 0);

    hWeatherIcon_[3] = LoadGraph("Assets/UI/Snow.png");
    assert(hWeatherIcon_[3] > 0);


    //天候の解説
    hWeatherExplanation_[0] = LoadGraph("Assets/UI/SunText2.png");
    assert(hWeatherExplanation_[0] > 0);

    hWeatherExplanation_[1] = LoadGraph("Assets/UI/RainText2.png");
    assert (hWeatherExplanation_[1] > 0);

    hWeatherExplanation_[2] = LoadGraph("Assets/UI/GaleText3.png");
    assert(hWeatherExplanation_[2] > 0);
  
    hWeatherExplanation_[3] = LoadGraph("Assets/UI/SnowText2.png");
    assert(hWeatherExplanation_[3] > 0);

    hWeatherExplanation_[4] = LoadGraph("Assets/UI/ControllerState.png");
    assert(hWeatherExplanation_[4] > 0);
}

void Weather::Release()
{
    for (int i = 0; i < 4; i++)
    {
        DeleteGraph(hWeatherEffect_[i]);
        DeleteGraph(hWeatherIcon_[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        DeleteGraph(hWeatherExplanation_[i]);
    }
}

void Weather::Update()
{
    ExplanationController();
}

void Weather::Draw()
{
    DrawWeatherUI();
}

void Weather::SetPosition(int x, int y)
{
    transform_.position_.x = x;
    transform_.position_.y = y;
}

float Weather::GetWeatherChange()
{
    switch (weather_)
    {
    case Sun:
        return 1.0f; 
    case Rain:
        return 1.0f;
    case Gale: 
        return 1.2f; //移動速度の上昇
    case Snow:
        return 0.8f; //移動速度の低下
    default:
        return 1.0f;
    }
}

void Weather::ExplanationController()
{

    padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);

    //特定のキー・ボタンが入力されたら操作説明UIを出現させる
    if (CheckHitKey(KEY_INPUT_Q) || input.Buttons[8] || input.Buttons[9])
    {
        IsExplanationDisplay_ = true;
    }
    else
    {
        IsExplanationDisplay_ = false;
    }
}

void Weather::DrawWeatherUI()
{
    Player* pPlayer = GetParent()->FindGameObject<Player>();
    int alpha = 24;

    if (pPlayer != nullptr)
    {
        switch (weather_)
        {
        case Sun:

            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            DrawGraph(600, 0, hWeatherIcon_[0], TRUE);
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
            DrawGraph(0, 0, hWeatherEffect_[0], TRUE);
            break;

        case Rain:

            DrawGraph(600, 0, hWeatherIcon_[1], TRUE);
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
            RainOnChecker = false;
            break;

        case Gale:

            DrawGraph(600, 0, hWeatherIcon_[2], TRUE);
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
            DrawGraph(0, 0, hWeatherEffect_[2], TRUE);
            WindOnChecker = false;
            break;

        case Snow:

            DrawGraph(600, 0, hWeatherIcon_[3], TRUE);
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
            DrawGraph(0, 0, hWeatherEffect_[3], TRUE);
            SnowOnChecker = false;
            break;
        default:
            break;
        }
    }

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//透明度を元に戻す

    //画面暗くしているときに出す説明
    if (IsExplanationDisplay_)
    {
        int x = 20;
        int y = 460;
        switch (weather_)
        {
        case Sun:

            DrawGraph(0, 160, hWeatherExplanation_[0], TRUE);
            DrawGraph(x, y, hWeatherExplanation_[4], TRUE);
            break;
        case Rain:

            DrawGraph(0, 160, hWeatherExplanation_[1], TRUE);
            DrawGraph(x, y, hWeatherExplanation_[4], TRUE);
            break;
        case Gale:

            DrawGraph(0, 160, hWeatherExplanation_[2], TRUE);
            DrawGraph(x, y, hWeatherExplanation_[4], TRUE);
            break;
        case Snow:

            DrawGraph(0, 160, hWeatherExplanation_[3], TRUE);
            DrawGraph(x, y, hWeatherExplanation_[4], TRUE);
            break;
        default:
            break;
        }
    }

}

