#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// �ړ�UI��\������N���X
/// </summary>
class MoveUI :
    public GameObject
{
private:
	int hMoveUI;
public:
    MoveUI(GameObject* parent);

    ~MoveUI();

    //������
	void Initialize() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetPosition(int x, int y)
	{
		transform_.position_.x = x;
		transform_.position_.y = y+4;//������
	}

};

