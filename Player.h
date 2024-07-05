#pragma once
#include "Engine/GameObject.h"
#include "Weather.h"

/// <summary>
/// プレイヤーキャラ
/// </summary>
/// 
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
	void Jump();
	int GetHp();

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

	float NDTIME_; //無敵時間
	int Hp_ = 3;
	int hitCount;

	float WeatherSpeed_;//MOVE_SPEEDとWeatherの値を合わせ格納する用の変数
	bool  WeatherSwitch;//高速で天候が切り替わらないようにする対策
	bool CoolDown;
	int MagicPoint;
	enum State
	{
		S_WaIk = 0,
		S_Cry,
	};
	State state;


	int hitX;
	int hitY;
	Player* player_;
};