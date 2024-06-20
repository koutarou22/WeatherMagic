#pragma once
#include "Engine/GameObject.h"
#include "Weather.h"

/// <summary>
/// プレイヤーキャラ
/// </summary>
/// 
class Player : public GameObject
{
public:


	Player(GameObject* scene);
	~Player();
	void Update() override;
	void Draw() override;
	void SetPosition(int x, int y);

	void WeatherEffects(Weather* weather);
	
private:
	int hImage;
	GameObject* sceneTop;
	bool prevSpaceKey;
	bool onGround;//地面にいるのか？

	float Jump_P = 0.0f;

	int animType;//状況
	int animFrame;//駒
	int PictFlame;
	int flameCounter;

	float WeatherSpeed_;//MOVE_SPEEDとWeatherの値を合わせ格納する用の変数
	enum State
	{
		S_WaIk = 0,
		S_Cry,
	};
	State state;

	
};