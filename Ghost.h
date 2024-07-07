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
	bool ColliderRect(float x, float y, float w, float h);
private:
	float sinAngle;
	int hImage_;
	int animeType_;//ó‹µ
	int animeFrame_;//‹î
	int PictFlame_;
	int flameCounter_;

	int CoolDownAttack_ = 0;
	int timer_ = 90;
	enum State
	{
		S_WaIk = 0,
		S_Cry,
	};
	State state;

};
