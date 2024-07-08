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

	Slime(GameObject* parent, float x, float y);
	Slime(GameObject* scene);
	~Slime();
	void Update() override;
	void Draw() override;

	void WeatherEffects(Weather* weather);
	//bool ColliderCircle(float x, float y, float r);

	bool ColliderRect(float x, float y, float w, float h);
	void SetPosition(int x, int y);
	float x;
	float y;

	void RainScale(WeatherState state, Transform& transform,
		float& WeatherSpeed_, float MOVE_SPEED, float WeatherEffect, float& ScaleEffect_);
	
private:
	int hImage;
	bool prevSpaceKey;
	bool onGround;//地面にいるのか？

	int Timer_ = 90;
	int CoolGround_Now = 0;
	float Jump_P = 0.0f;
	float WeatherSpeed_ = 0.0f;
	float RainHappening_ = 0.0f;
	float ScaleEffect_ = 0.0f;
	bool Reverse_ = false;
	int direction = 1;
};

