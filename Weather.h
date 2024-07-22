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
	WeatherState weather_;
private:
	
	WeatherState NextWeather_;
    int hImage_Sunny;//����̃G�t�F�N�g
	int hImage_Rainy;//�J�̃G�t�F�N�g
	int hImage_Wind;//���̃G�t�F�N�g

	int hImage_SIcon;//����̃A�C�R��
	int hImage_RIcon;//�J�̃A�C�R��
	int hImage_WIcon;//���̃A�C�R��

	int hImage_RainyNoMp;//Mp���g���Ȃ����̍����ւ��p(�J)
	int hImage_WindNoMp;//Mp���g���Ȃ����̍����ւ��p(��)

	bool RainOnChecker;
	bool WindOnChecker;

	int hImage_Book;
    float WeatherChange_; // �V��ɉ������ړ����x�p���l

	int flameCounter_;
	int animeFrame_;
		
};

