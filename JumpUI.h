#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// ジャンプUIを表示するクラス
/// </summary>
class JumpUI :
    public GameObject
{
private:
	int hJumpUI;
public:
	JumpUI(GameObject* parent);

	~JumpUI();

	//初期化
	void Initialize() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetPosition(int x, int y)
	{
		transform_.position_.x = x-100;
		transform_.position_.y = y + 4;//微調整
	}

};

