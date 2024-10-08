#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// 弾丸を飛ばしてくるお化けの情報
/// </summary>
class Ghost : public GameObject
{
public:
	Ghost(GameObject* scene);
	~Ghost();
	void Update() override;
	void Draw() override;
	//円の当たり判定をする
	void SetPosition(int x, int y);
	bool ColliderCircle(float x, float y, float r);
	
private:
	float sinAngle;
	int hImage_;
	int animeType_;//状況
	int animeFrame_;//駒
	int PictFlame_;
	int flameCounter_;

	int CoolDownAttack_ = 0;
	int timer_ = 90;
	enum State//結局使ってない
	{
		S_WaIk = 0,
		S_Cry,
	};
	State state;

};
