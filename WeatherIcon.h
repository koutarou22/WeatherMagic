#pragma once
#include "Weather.h"
/// <summary>
/// VóÌUI
/// </summary>
class WeatherIcon : public Weather
{
	int hImage_S;//°ê
	int hImage_G;//­
	int hImage_R;//J
public:
	WeatherIcon(Weather * parent);//æÌp
	void Update() override;//state
	void Draw()override;
};

