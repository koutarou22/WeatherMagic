#pragma once
#include "Weather.h"
/// <summary>
/// �V���UI
/// </summary>
class WeatherIcon : public Weather
{
	int hImage_S;//����
	int hImage_G;//����
	int hImage_R;//�J
public:
	WeatherIcon(Weather * parent);//�摜�̏����p
	void Update() override;//state
	void Draw()override;
};

