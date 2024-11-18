#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// 雪の時敵が凍ってるのを表現する用のアレ
/// </summary>
class FreezeEffect :
    public GameObject
{
	int hImage_;
	int animeFrame;
	int FrameCounter;
	int eraseCounter;

	bool ReverseFrame;//フレームを判定させる用のフラグ
public:

	FreezeEffect(GameObject* parent);
	~FreezeEffect();

	//更新
	void Update() override;
	//描画
	void Draw() override;
	//開放
	void Release() override;;

	void SetPosition(int x, int y);
};

