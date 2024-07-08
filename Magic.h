#pragma once
#include "Engine/GameObject.h"
#include "Player.h"

/// <summary>
/// プレイヤーが放つ魔法
/// </summary>
class Magic : public GameObject
{
public:
	Magic(GameObject* scene);
	~Magic();
	void Update() override;
	void Draw() override;
	void SetPosition(int x, int y);
	void SetPosition(XMFLOAT3 pos);
	void SetDirection(VECTOR _direction) { direction_ = _direction; }
	void SetSpeed(float _speed) { speed_ = _speed; }
	bool ColliderCircle(float x, float y, float r);
private:
	int hImage_;
	int timer_;
	VECTOR direction_;//方向
    float speed_;//弾丸の速度
	
};
