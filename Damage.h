#pragma once
#include "Engine/GameObject.h"
class Damage :public GameObject
{
private:
	int hImage_;
	int Timer_ = 90;

public:

	Damage(GameObject* parent);
	~Damage();
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

};

