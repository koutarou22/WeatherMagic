#pragma once
#include "Engine/GameObject.h"
class Hp :
	public GameObject
{
private:
	int hImage_;
	//int bagImage_;
	int Wide_ = 3;//�̗�

public:

	Hp(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void DamageHp();//Player�ő��삵����
};