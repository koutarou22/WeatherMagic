#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// 触れるとクリアできるオブジェクトの情報(やってることは回復アイテムとほぼ同じ)
/// </summary>
class ClearFlag :public GameObject
{
private:
	int hImage_;
	int hImage_Right;

	int animeType_;//状況
	int animeFrame_;//駒
	int PictFlame_;
	int flameCounter_;
public:

	ClearFlag(GameObject* parent);
	~ClearFlag();
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
};

