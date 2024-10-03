#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// ’¹i“GjŒ»İ‚Ìg‚Á‚Ä‚È‚¢
/// </summary>
class Bird : public GameObject
{
public:
	Bird(GameObject* scene);
	~Bird();
	void Update() override;
	void Draw() override;
	//‰~‚Ì“–‚½‚è”»’è‚ğ‚·‚é
	void SetPosition(int x, int y);
	bool ColliderCircle(float x, float y, float r);

private:
	float sinAngle;
	int hImage;

};
