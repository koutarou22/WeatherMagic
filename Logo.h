#pragma once
#include "Engine/GameObject.h"
class Logo :
    public GameObject
{
private:
	int hImage_;
public:
    Logo(GameObject* parent);
	~Logo();
	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;
	//�J��
	void Release() override;
};

