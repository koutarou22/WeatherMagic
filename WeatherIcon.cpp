#include "WeatherIcon.h"

WeatherIcon::WeatherIcon(Weather* parent) :Weather(parent)
{
    hImage_S = LoadGraph("Assets/Sun.png");
    assert(hImage_S > 0);
    hImage_R = LoadGraph("Assets/Rain1.png");
    assert(hImage_R > 0);
    hImage_G = LoadGraph("Assets/Wind.png");
    assert(hImage_G > 0);
}

void WeatherIcon::Update()
{
}


void WeatherIcon::Draw()
{
    switch (weather_)
    {
    case Sunny:
        DrawFormatString(500, 10, GetColor(255, 255, 0), "天候: 晴れ 『変化なし』消費Mp0");
        DrawGraph(450, 10, hImage_S, TRUE);  // 晴れ

        break;
    case Rainy:
        DrawFormatString(500, 10, GetColor(100, 149, 237), "天候: 雨　『地面がぬかるむ..』-移動速度DOWN  +スライム巨大化");
        DrawGraph(450, 10, hImage_R, TRUE);  // 雨
        break;
    case Gale:
        DrawFormatString(500, 10, GetColor(0, 250, 154), "事象: 強風　『敵が(自分も)吹っ飛ぶ！』 消費Mp 4");
        //DrawGraph(0, 0, hImage_Wind, TRUE);  // 強風の画像とかあるんか？
        break;
    }
}
