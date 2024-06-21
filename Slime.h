#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
#include "Weather.h"
/// <summary>
/// �X���C��
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
	bool onGround;//�n�ʂɂ���̂��H

	float Jump_P = 0.0f;
	float sinAngle;

	float WeatherSpeed_;
	float RainHappening_;

};

