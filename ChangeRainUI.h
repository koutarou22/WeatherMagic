#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// 天候を雨に変更するUIを表示するクラス
/// </summary>
class ChangeRainUI :
    public GameObject
{
private:
	int hChangeRainUI;
public:
	ChangeRainUI(GameObject* parent);

	~ChangeRainUI();

	//初期化
	void Initialize() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetPosition(int x, int y)
	{
		transform_.position_.x = x - 100;
		transform_.position_.y = y + 4;//微調整
	}
};

