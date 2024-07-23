#pragma once
#include "Engine/GameObject.h"

class ClearFlag :public GameObject
{
private:
	int hImage_;
	int hImage_Right;

	int animeType_;//ó‹µ
	int animeFrame_;//‹î
	int PictFlame_;
	int flameCounter_;
public:

	ClearFlag(GameObject* parent);
	~ClearFlag();
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

