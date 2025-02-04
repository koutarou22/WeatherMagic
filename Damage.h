#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// スライムが攻撃をくらった時の表示
/// </summary>

namespace
{
	const int TIME = 90; //ダメージエフェクトが消えるまでの時間
	XMFLOAT2 POS_MARGE = { 10,20 }; //座標をintに変換する際の調整分
}

class Damage :public GameObject
{
private:
	int dmgImage_;
	int timer_; //タイマー
public:

	Damage(GameObject* parent);
	~Damage();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	//アクセス関数
	void SetPosition(int x, int y) {transform_.position_.x = x;transform_.position_.y = y;}
	void SetPosition(XMFLOAT3 pos) {transform_.position_ = pos;}

};

