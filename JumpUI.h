#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// �W�����vUI��\������N���X
/// </summary>
class JumpUI :
    public GameObject
{
private:
	int hJumpUI;
public:
	JumpUI(GameObject* parent);

	~JumpUI();

	//������
	void Initialize() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetPosition(int x, int y)
	{
		transform_.position_.x = x-100;
		transform_.position_.y = y + 4;//������
	}

};

