#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// �X���C�����U��������������̕\��
/// ���������̎������摜���o�邾���Ȃ̂ŏ����͒P��
/// </summary>
class Damage :public GameObject
{
private:
	int hImage_;
	int Timer_ = 90;
	int animeFrame_;
	int flameCounter_;
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

