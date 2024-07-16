#pragma once
#include"Engine/GameObject.h"
#include"Player.h"
#include "Weather.h"

struct Rect
{
	float x, y, w, h;
};

class Rock :public GameObject
{
public:
	Rock(GameObject* scene);
	~Rock();
	void Update() override;
	void Draw() override;
	void SetPosition(int x, int y);
	void WeatherEffects(Weather* weather);
	//int CollisionUp(int x, int y);
	bool IsColliding(const Rect& a, const Rect& b);
private:
	bool PressKey_R = false;
	bool PressKey_L = false;
	int WindTimer_ = 300;

	int hImage_;
	float Jump_P = 0.0f;
	bool onGround;//ínñ Ç…Ç¢ÇÈÇÃÇ©ÅH

};

