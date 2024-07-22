#pragma once
#include"Engine/GameObject.h"

enum WeatherState
{
	Sunny,//晴れの日
	Rainy,//雨の日
	Gale,//強風(天候かこれ...?)
};
class Weather:public GameObject
{
public:
	
	Weather(GameObject* parent) : GameObject(parent), weather_(Sunny) {}

	void Initialize() override;
	void Update() override;
	void Draw() override;

	void SetPosition(int x, int y);
	void SetWeather(WeatherState _state) { weather_ = _state ; }
	void SetNextWeather(WeatherState _state) { NextWeather_ = _state; }
    float GetWeather(){ return WeatherChange_; }

	WeatherState GetNextWeather() const { return NextWeather_; } 
	WeatherState GetWeatherState() const { return weather_; }

	float GetWeatherChange();
	WeatherState weather_;
private:
	
	WeatherState NextWeather_;
    int hImage_Sunny;//晴れのエフェクト
	int hImage_Rainy;//雨のエフェクト
	int hImage_Wind;//風のエフェクト

	int hImage_SIcon;//晴れのアイコン
	int hImage_RIcon;//雨のアイコン
	int hImage_WIcon;//風のアイコン

	int hImage_RainyNoMp;//Mpが使えない時の差し替え用(雨)
	int hImage_WindNoMp;//Mpが使えない時の差し替え用(風)

	bool RainOnChecker;
	bool WindOnChecker;

	int hImage_Book;
    float WeatherChange_; // 天候に応じた移動速度用数値

	int flameCounter_;
	int animeFrame_;
		
};

