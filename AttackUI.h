#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// 攻撃UIを表示するクラス
/// </summary>
class AttackUI :
    public GameObject
{
private:
	int hAttackUI;

public:
	AttackUI(GameObject* parent);

	~AttackUI();

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

