#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// 鳥（敵）現在使ってない
/// </summary>
class Bird : public GameObject
{
public:
	Bird(GameObject* scene);
	~Bird();
	void Update() override;
	void Draw() override;
	//円の当たり判定をする
	void SetPosition(int x, int y);
	bool ColliderCircle(float x, float y, float r);

private:
	float sinAngle;
	int hImage;

};
