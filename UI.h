#pragma once
#include "Engine/GameObject.h"
class UI :
    public GameObject
{
	int hAttB;
	int hChaPad;
	int hJumpA;
	int hExplanLRB;
	int hStkL;
	int hStkR;
public:
	UI(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

