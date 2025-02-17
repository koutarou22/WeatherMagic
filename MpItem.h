#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// Mp回復アイテムの情報
/// </summary>
class MpItem :public GameObject
{
private:
	int hMpItem_;
	int hMpIEffect_;
	int animeType_;//状況
	int animeFrame_;//駒
	//int PictFlame_;
	int FrameCounter_;
public:

	MpItem(GameObject* parent);
	~MpItem();
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;
	//開放
	void Release() override;
	void SetPosition(int x, int y);
	void SetPosition(XMFLOAT3 pos);
	bool ColliderCircle(float x, float y, float r);
	bool Judgement_ = false;
};

