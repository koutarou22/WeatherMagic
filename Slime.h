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
	//bool ColliderCircle(float x, float y, float r);

	bool ColliderRect(float x, float y, float w, float h);
	void SetPosition(int x, int y);
	float x;
	float y;

	void RainScale(WeatherState state, Transform& transform,
		float& WeatherSpeed_, float MOVE_SPEED, float WeatherEffect, float& ScaleEffect_);
	void GaleEffect(WeatherState state);
	
private:
	int hImage;
	bool prevSpaceKey;
	bool PressKey_R = false;
	bool PressKey_L = false;
	bool onGround;//地面にいるのか？
	bool PressRight;
	bool PressLeft;


	int flameCounter_;
	int animeFrame_;

	int StunTimer_;
	int WindTimer_ = 300;
	int Timer_ = 90;
	int CoolGround_Now = 0;
	bool CheckPressRight;
	bool CheckPressLeft;
	float Jump_P = 0.0f;
	float WeatherSpeed_ = 0.0f;
	float RainHappening_ = 0.0f;
	float ScaleEffect_ = 0.0f;
	bool Reverse_ = false;
	int direction = 1;
};

