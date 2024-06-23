#pragma once
#include"Engine/GameObject.h"

enum WeatherState
{
	Sunny,//晴れの日
	Rainy,//雨の日
};

class Weather:public GameObject
{
public:
	
	Weather(GameObject* parent) : GameObject(parent), weather_(Sunny) {}

	void Initialize() override;
	void Update() override;
	void Draw() override;

	void SetWeather(WeatherState _state) { weather_ = _state ; }//外部から天候情報を変更できる
    float GetWeather(){ return WeatherChange_; }//天候を変化させたときの影響を与える数値を持ってこれる

	WeatherState GetWeatherState() const { return weather_; }

	float GetWeatherChange();

private:
	WeatherState weather_;
    int hImage_Sunny;
	int hImage_Rainy;
    float WeatherChange_; // 天候に応じた移動速度用数値
};

