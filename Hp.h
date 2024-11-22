#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// プレイヤーのHpのUI
/// ※このクラスとプレイヤークラスのHP(変数)を共有させている
/// </summary>
class Hp :
	public GameObject
{
private:
	int hImage_;
	int BgImage_;
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
	void HeelHp();
};