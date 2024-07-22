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
	void GaleEffect(WeatherState state);
	//int CollisionUp(int x, int y);

	/// <summary>
	///éläpÇÃìñÇΩÇËîªíË
	/// </summary>
	/// <returns></returns>
	bool ColliderRect(float x, float y, float w, float h);

	float x;
	float y;
	
private:
	bool PressKey_R = false;
	bool PressKey_L = false;
	int WindTimer_ = 300;

	int hImage_;
	float Jump_P = 0.0f;
	bool onGround;//ínñ Ç…Ç¢ÇÈÇÃÇ©ÅH

	float Width_;  
	float Height_; 

};

