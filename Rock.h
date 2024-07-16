#pragma once
#include"Engine/GameObject.h"
#include"Player.h"
#include "Weather.h"

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
	//bool ColliderRect(float x, float y, float w, float h);

	//bool IsColliding(const Rect& a, const Rect& b);
	
	bool IsRockPosition(std::list<Rock*> rocks, int x, int y);
	int CollisionRight(std::list<Rock*> rocks, int x, int y);
	int CollisionLeft(std::list<Rock*> rocks, int x, int y);
	int CollisionDown(std::list<Rock*> rocks, int x, int y);
	float x;
	float y;
	
private:
	bool PressKey_R = false;
	bool PressKey_L = false;
	int WindTimer_ = 300;

	int hImage_;
	float Jump_P = 0.0f;
	bool onGround;//地面にいるのか？

	float Width_;  
	float Height_; 

};

