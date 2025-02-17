#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// 移動UIを表示するクラス
/// </summary>
class MoveUI :
    public GameObject
{
private:
	int hMoveUI;
public:
    MoveUI(GameObject* parent);

    ~MoveUI();

    //初期化
	void Initialize() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetPosition(int x, int y)
	{
		transform_.position_.x = x;
		transform_.position_.y = y+4;//微調整
	}

};

