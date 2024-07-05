#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// 弾丸を飛ばしてくるお化け君
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
	int hImage;
	int animType;//状況
	int animFrame;//駒
};
