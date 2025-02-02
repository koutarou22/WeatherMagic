#pragma once
#include "Engine/GameObject.h"
class ChangeWindUI :
    public GameObject
{
	int hChangeWindUI;
public:
	ChangeWindUI(GameObject* parent);

	~ChangeWindUI();

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

