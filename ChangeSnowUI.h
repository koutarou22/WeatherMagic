#pragma once
#include "Engine/GameObject.h"
class ChangeSnowUI :
    public GameObject
{
	int hChangeSnowUI;
public:
	ChangeSnowUI(GameObject* parent);

	~ChangeSnowUI();

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

