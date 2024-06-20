#include "Weather.h"

void Weather::Update() 
{

}

void Weather::Draw() {
    // 天候に応じた描画処理
    switch (weather_) {
    case Sunny:
        DrawFormatString(500, 10, GetColor(255, 255, 0), "天候: 晴れ 『元気！』");
        break;
    case Rainy:
        DrawFormatString(500, 10, GetColor(255, 255, 0), "天候: 雨　『地面がぬかるむ..』");
        break;
    }
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

