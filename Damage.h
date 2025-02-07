#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// �X���C�����U��������������̕\��
/// </summary>

namespace
{
	const int TIME = 90; //�_���[�W�G�t�F�N�g��������܂ł̎���
	XMFLOAT2 POS_MARGE = { 10,20 }; //���W��int�ɕϊ�����ۂ̒�����
}

class Damage :public GameObject
{
private:
	int dmgImage_;
	int timer_; //�^�C�}�[
public:

	Damage(GameObject* parent);
	~Damage();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	//�A�N�Z�X�֐�
	void SetPosition(int x, int y) {transform_.position_.x = x;transform_.position_.y = y;}
	void SetPosition(XMFLOAT3 pos) {transform_.position_ = pos;}

};

