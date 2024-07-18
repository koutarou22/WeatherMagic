#pragma once
#include"Engine/GameObject.h"

enum WeatherState
{
	Sunny,//����̓�
	Rainy,//�J�̓�
	Gale,//����(�V�󂩂���...?)
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

private:
	WeatherState weather_;
	WeatherState NextWeather_;
    int hImage_Sunny;
	int hImage_Rainy;
	int hImage_Wind;

	int hImage_Book;
    float WeatherChange_; // �V��ɉ������ړ����x�p���l

	int flameCounter_;
	int animeFrame_;
		
};

