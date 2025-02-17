#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// 天候が風の時、石を動かせるUIを表示するクラス
/// </summary>
class MoveStoneUI :
    public GameObject
{
	int hMoveStoneUI;
public:
	MoveStoneUI(GameObject* parent);

	~MoveStoneUI();

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

