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
	void ScaleX();
	void ScaleY();

	bool ColliderRect(float x, float y, float w, float h);
	void SetPosition(int x, int y);
	float x;
	float y;
	
private:
	int hImage;
	bool prevSpaceKey;
	bool onGround;//地面にいるのか？

	float Jump_P = 0.0f;
	float sinAngle;

	float WeatherSpeed_;
	float RainHappening_;
	float ScaleEffect_;
	bool Reverse_ = false;
	int direction = 1;
};

