#pragma once
#include "Engine/GameObject.h"
class MoveStoneUI :
    public GameObject
{
	int hMoveStoneUI;
public:
	MoveStoneUI(GameObject* parent);

	~MoveStoneUI();

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

