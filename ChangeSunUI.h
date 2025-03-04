#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// 天候を晴れに変更するUIを表示するクラス
/// </summary>
class ChangeSunUI :
    public GameObject
{
	int hChangeSunUI;
public:
	ChangeSunUI(GameObject* parent);

	~ChangeSunUI();

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

