#pragma once
#include"Engine/GameObject.h"

enum WeatherState
{
	Sunny,//����̓�
	Rainy,//�J�̓�
};

class Weather:public GameObject
{
public:
	
	Weather(GameObject* parent) : GameObject(parent), weather_(Sunny) {}

	void Initialize() override;
	void Update() override;
	void Draw() override;

	void SetWeather(WeatherState _state) { weather_ = _state ; }//�O������V�����ύX�ł���
    float GetWeather(){ return WeatherChange_; }//�V���ω��������Ƃ��̉e����^���鐔�l�������Ă����

	WeatherState GetWeatherState() const { return weather_; }

	float GetWeatherChange();

private:
	WeatherState weather_;
    int hImage_Sunny;
	int hImage_Rainy;
    float WeatherChange_; // �V��ɉ������ړ����x�p���l
};

