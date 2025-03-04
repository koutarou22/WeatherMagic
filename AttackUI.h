#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// �U��UI��\������N���X
/// </summary>
class AttackUI :
    public GameObject
{
private:
	int hAttackUI;

public:
	AttackUI(GameObject* parent);

	~AttackUI();

	//������
	void Initialize() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetPosition(int x, int y)
	{
		transform_.position_.x = x - 100;
		transform_.position_.y = y + 4;//������
	}
};

