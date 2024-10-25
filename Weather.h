#pragma once
#include"Engine/GameObject.h"

/// <summary>
/// 天候を操作するクラス
/// </summary>

enum WeatherState
{
	Sun,//晴れの日
	Rain,//雨の日
	Gale,//強風の日(天候かこれ...?)
	Snow,//雪の日
};

class Weather:public GameObject
{
public:
	
	Weather(GameObject* parent) : GameObject(parent), weather_(Sun) {}

	void Initialize() override;
	void Update() override;
    void Draw() override;

	void SetPosition(int x, int y);
	void SetWeather(WeatherState _state) { weather_ = _state ; }
	void SetNextWeather(WeatherState _state) { NextWeather_ = _state; }
    float GetWeather() { return WeatherChange_; }

	WeatherState GetNextWeather() const { return NextWeather_; } 
	WeatherState GetWeatherState() const { return weather_; }

	float GetWeatherChange();
	WeatherState weather_;

    
private:
	
	//ここかっこ悪いなぁ
	WeatherState NextWeather_;
    int hImage_Sun;//晴れのエフェクト(背景)
	int hImage_Rain;//雨のエフェクト(背景)
	int hImage_Wind;//風のエフェクト(背景)
	int hImage_Snow;//雪のエフェクト(背景)


	int Sun_Icon;//晴れのアイコン
	int Rain_Icon;//雨のアイコン
	int Gale_Icon;//風のアイコン
	int Snow_Icon;//雪のアイコン

	int hImage_RainNoMp;//Mpが使えない時の差し替え用(雨)
	int hImage_WindNoMp;//Mpが使えない時の差し替え用(風)
    int hImage_SnowNoMp;//Mpが使えない時の差し替え用(雪)

	int hImage_StateSun;
	int hImage_StateWind;
	int hImage_StateRain;
    int hImage_StateSnow;

	int Weather_ChangeMagic;//天候変えたときのアニメーション(まだ定義してない)

	bool RainOnChecker;
	bool WindOnChecker;
    bool  SnowOnChecker; 

	int hImage_Book;
    float WeatherChange_; // 天候に応じた移動速度用数値

	int flameCounter_;
	int animeFrame_;

	bool DebugLog_;
		
};

