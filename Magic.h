#pragma once
#include "Engine/GameObject.h"
#include<array>

/// <summary>
/// �v���C���[�������@�N���X
/// </summary>
class Magic : public GameObject
{
public:
	Magic(GameObject* scene);
	~Magic();
	void Update() override;
	void Draw() override;
	void UpdateIdle();
	void UpdateMove();
	void UpdateHit();

	void SetPosition(int x, int y);
	void SetDirection(VECTOR _direction) { direction_ = _direction; }
	void SetSpeed(float _speed) { speed_ = _speed; }
	bool ColliderCircle(float x, float y, float r);

	void SetMagicStateHit() { Magic_s = S_Hit; }
	void SetMagicStateMove() { Magic_s = S_Move; }
	void SetIsDraw(bool _IsDraw) { isDraw_ = _IsDraw; }
	bool GetIsDraw() { return isDraw_; }

	void Release() override;
private:
	int timer_;//�o������
	VECTOR direction_;//����
    float speed_;//�e�ۂ̑��x

	int hMagic_Move1;
	int hMagic_Move2;
	int hMagic_Move3;
	int hMagic_Move4;

	int hMagic_Hit1;
	int hMagic_Hit2;
	int hMagic_Hit3;
	int hMagic_Hit4;
	int hMagic_Hit5;
	int hMagic_Hit6;
	int hMagic_Hit7;

	enum MagicState
	{
		S_Move,
		S_Hit,
		S_Max,
	};
	MagicState Magic_s;
	std::array<int, 4> animeArray_;//�A�j���[�V�����̌Œ蒷�z��
	std::array<int, 7> animeHitArray_;//�A�j���[�V�����̌Œ蒷�z��
	int animeNum;//�A�j���[�V�����̂������Ԗڂ�
	int frameCounter;//�A�j���[�V�����̐؂�ւ��J�E���g
	bool isDraw_;//isDraw��true�Ȃ�`��+�X�V
};
