#pragma once
#include "Engine/GameObject.h"
class Hp :
	public GameObject
{
private:
	int hImage_;
	//int bagImage_;
	int Wide_ = 3;//体力

public:

	Hp(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void DamageHp();//Playerで操作したい
};