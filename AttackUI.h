#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// UUIð\¦·éNX
/// </summary>
class AttackUI :
    public GameObject
{
private:
	int hAttackUI;

public:
	AttackUI(GameObject* parent);

	~AttackUI();

	//ú»
	void Initialize() override;

	//`æ
	void Draw() override;

	//Jú
	void Release() override;

	void SetPosition(int x, int y)
	{
		transform_.position_.x = x - 100;
		transform_.position_.y = y + 4;//÷²®
	}
};

