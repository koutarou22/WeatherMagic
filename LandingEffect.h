#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// 着地したときに起きる砂埃的なアレ
/// </summary>
class LandingEffect :public GameObject
{
	int hImage_;
	int animeFrame;
	int FrameCounter;
	int eraseCounter;
public:

	LandingEffect(GameObject* parent);
	~LandingEffect();

	//更新
	void Update() override;
	//描画
	void Draw() override;
	//開放
	void Release() override;

	void SetPosition(int x, int y);
};