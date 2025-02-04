#pragma once
#include"Engine/GameObject.h"

/// <summary>
/// 天候をの画像、効果を管理するクラス
/// </summary>
enum WeatherState
{
	Sun,//晴れの日
	Rain,//雨の日
	Gale,//強風の日
	Snow,//雪の日
};

class Weather:public GameObject
{
public:
	
	Weather(GameObject* parent) : GameObject(parent), weather_(Sun) {};
	~Weather();
	void Initialize() override;
	void Update() override;
    void Draw() override;
	void Release() override;

	void SetPosition(int x, int y);
	void SetWeather(WeatherState _state) { weather_ = _state ; }
	void SetNextWeather(WeatherState _state) { NextWeather_ = _state; }

    /// <summary>
    /// プレイヤーの移動速度情報を取得する
    /// </summary>
    /// <returns></returns>
    float GetWeather() { return WeatherChange_; }

	WeatherState GetNextWeather() const { return NextWeather_; } 
	WeatherState GetWeatherState() const { return weather_; }

	/// <summary>
	/// 天候を切り替えた時のプレイヤーの移動速度を設定するクラス
	/// </summary>
	/// <returns></returns>
	float GetWeatherChange();
	WeatherState weather_;

	int padAnalogInput;//xboxの入力を受け取る
	XINPUT_STATE input;//xboxの入力を受け取る
    
private:
	
	WeatherState NextWeather_;

	//天候時のエフェクトを保存する変数
	//0:晴れ
	//1:雨
	//2:風
	//3:雪
	int hWeatherEffect_[4];

	//天候時のアイコン画像を保存する変数
    //0:晴れ
	//1:雨
	//2:風
	//3:雪
	int hWeatherIcon_[4];

	//天候時の天候の効果を説明用画像を保存する変数
	//0:晴れ
	//1:雨
	//2:風
	//3:雪
	//4:天候切り替えの割り当て
	int hWeatherExplanation_[5];

	
	//どの天候になっているか確認用変数
	bool RainOnChecker, WindOnChecker, SnowOnChecker;

    float WeatherChange_; // 天候に応じた移動速度用数値

	//現在操作説明が出ているか判定用変数
	bool IsExplanationDisplay_;


	/// <summary>
	/// 説明の画面を出現させる為のキーの入力処理情報
	/// </summary>
	void ExplanationController();

	/// <summary>
	/// 天候がわかるアイコンや効果の説明、エフェクトの情報
	/// </summary>
	void DrawWeatherUI();
		
};

