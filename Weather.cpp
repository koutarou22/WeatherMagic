#include "Weather.h"

void Weather::Initialize()
{
    hImage_Sunny = LoadGraph("Assets/Sky.png");
    assert(hImage_Sunny > 0);
    hImage_Rainy = LoadGraph("Assets/Rain.png");
    assert(hImage_Rainy > 0);
}

void Weather::Update()
{

}

void Weather::Draw() 
{
    int alpha = 24;  // 透明度を半分に設定

    switch (weather_)
    {
    case Sunny:
        DrawFormatString(500, 10, GetColor(255, 255, 0), "天候: 晴れ 『変化なし』");
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawGraph(0, 0, hImage_Sunny, TRUE);  // 晴れ
        break;
    case Rainy:
        DrawFormatString(500, 10, GetColor(0, 0, 0), "天候: 雨　『地面がぬかるむ..』-移動速度DOWN  +スライム巨大化");
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawGraph(0, 0, hImage_Rainy, TRUE);  // 雨
        break;
    }

    // 描画モードを元に戻す
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

float Weather::GetWeatherChange()
{
    switch (weather_)
    {
    case Sunny:
        return 1.0f; // 晴れの日は通常の速度
    case Rainy:
        return 0.8f; // 雨の日は速度を20%減少
    default:
        return 1.0f;
    }
}

