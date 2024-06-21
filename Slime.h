#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
#include "Weather.h"
/// <summary>
/// スライム
/// </summary>
class Slime : public GameObject
{
public:
	Slime(GameObject* scene);
	~Slime();
	void Update() override;
	void Draw() override;

	void WeatherEffects(Weather* weather);
private:
	int hImage;
	bool prevSpaceKey;
	bool onGround;//地面にいるのか？

	float Jump_P = 0.0f;
	float sinAngle;

	float WeatherSpeed_;
	float RainHappening_;

};

