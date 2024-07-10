#pragma once
#include "Engine/GameObject.h"
class HealItem :public GameObject
{
private:
	int hImage_;

	int animType;//ó‹µ
	int animFrame;//‹î
	int PictFlame;

public:

	HealItem(GameObject* parent);
	~HealItem();
	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;
	//ŠJ•ú
	void Release() override;
	void SetPosition(int x, int y);
	void SetPosition(XMFLOAT3 pos);
	bool ColliderCircle(float x, float y, float r);
};

