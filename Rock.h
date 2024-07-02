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
	bool IsHitPlayer(Player* player);
	void PushOutPlayer(Player* player);
private:
	
	int hImage_;
	float Jump_P = 0.0f;
	bool onGround;//ínñ Ç…Ç¢ÇÈÇÃÇ©ÅH
};

