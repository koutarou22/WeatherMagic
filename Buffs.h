#pragma once
#include "Engine/GameObject.h"
class Buffs :public GameObject
{
private:
	int hImage_;

	int animeType_;//ó‹µ
	int animeFrame_;//‹î
	int PictFlame_;
	int flameCounter_;

public:

	Buffs(GameObject* parent);
	~Buffs();
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
};

