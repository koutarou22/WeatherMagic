#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// �V��𐰂�ɕύX����UI��\������N���X
/// </summary>
class ChangeSunUI :
    public GameObject
{
	int hChangeSunUI;
public:
	ChangeSunUI(GameObject* parent);

	~ChangeSunUI();

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

