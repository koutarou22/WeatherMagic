#include "Weather.h"


void Weather::Initialize()
{
    hImage_Sunny = LoadGraph("Assets/Sky.png");
    assert(hImage_Sunny > 0);
    hImage_Rainy = LoadGraph("Assets/Rain.png");
    assert(hImage_Rainy > 0);
    hImage_Wind = LoadGraph("Assets/Wind.png");
    assert(hImage_Wind > 0);

    hImage_Book = LoadGraph("Assets/Book.png");
    assert(hImage_Book > 0);
}

void Weather::Update()
{
    if (++flameCounter_ >= 24)
    {
        if (animeFrame_ < 3) 
        {
            animeFrame_ = (animeFrame_ + 1) % 4; //if文を使わない最適解
        }
        flameCounter_ = 0;
    }
}

void Weather::Draw() 
{
    int alpha = 24; 
    int SBookW = 128/3;
    int SBookH = 175/4;
    int AnimeS = animeFrame_ % 4 * SBookH;


    switch (weather_)
    {
    case Sunny:
        DrawFormatString(500, 10, GetColor(255, 255, 0), "天候: 晴れ 『変化なし』");
        DrawRectGraph(480, 10, 0, AnimeS, SBookW, SBookH, hImage_Book, TRUE);

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawGraph(0, 0, hImage_Sunny, TRUE);  // 晴れ
       
        break;
    case Rainy:
        DrawFormatString(500, 10, GetColor(0, 0, 0), "天候: 雨　『地面がぬかるむ..』-移動速度DOWN  +スライム巨大化");
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawGraph(0, 0, hImage_Rainy, TRUE);  // 雨
        break;
    case Gale:
        DrawFormatString(500, 10, GetColor(255, 255, 255), "事象: 強風　『敵が(自分も)吹っ飛ぶ！』");
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawGraph(0, 0, hImage_Wind, TRUE);  // 強風の画像とかあるんか？
        break;
    }

    // 描画モードを元に戻す
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    DrawFormatString(0, 80, GetColor(0, 0, 255), "今どの天候呼んでる？: %d", weather_);
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
    case Sunny:
        return 1.0f; // 晴れの日は通常の速度
    case Rainy:
        return 0.8f; // 雨の日は速度を20%減少
    case Gale: 
        return 1.2f; //強風
    default:
        return 1.0f;
    }
}

