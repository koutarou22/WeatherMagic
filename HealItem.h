#pragma once
#include "Engine/GameObject.h"
class HealItem :public GameObject
{
private:
	int hImage_;

	int animType;//��
	int animFrame;//��
	int PictFlame;

public:

	HealItem(GameObject* parent);
	~HealItem();
	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;
	//�J��
	void Release() override;
	void SetPosition(int x, int y);
	void SetPosition(XMFLOAT3 pos);
	bool ColliderCircle(float x, float y, float r);
};

