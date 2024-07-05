#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// ’eŠÛ‚ğ”ò‚Î‚µ‚Ä‚­‚é‚¨‰»‚¯ŒN
/// </summary>
class Ghost : public GameObject
{
public:
	Ghost(GameObject* scene);
	~Ghost();
	void Update() override;
	void Draw() override;
	//‰~‚Ì“–‚½‚è”»’è‚ğ‚·‚é
	void SetPosition(int x, int y);
	bool ColliderCircle(float x, float y, float r);

private:
	float sinAngle;
	int hImage;
	int animType;//ó‹µ
	int animFrame;//‹î
};
