#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// �V����J�ɕύX����UI��\������N���X
/// </summary>
class ChangeRainUI :
    public GameObject
{
private:
	int hChangeRainUI;
public:
	ChangeRainUI(GameObject* parent);

	~ChangeRainUI();

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

