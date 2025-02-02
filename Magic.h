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
	void SetPosition(XMFLOAT3 pos);
	void SetDirection(VECTOR _direction) { direction_ = _direction; }
	void SetSpeed(float _speed) { speed_ = _speed; }
	bool ColliderCircle(float x, float y, float r);

	void SetMagicStateHit() { Magic_s = S_Hit; }
	void SetMagicStateMove() { Magic_s = S_Move; }
	void SetIsDraw(bool _IsDraw) { isDraw_ = _IsDraw; }
	bool GetIsDraw() { return isDraw_; }

	void Release() override;
private:
	int hImage_;
	int timer_;
	VECTOR direction_;//����
    float speed_;//�e�ۂ̑��x

	int hImage_move1;
	int hImage_move2;
	int hImage_move3;
	int hImage_move4;

	int hImage_hit1;
	int hImage_hit2;
	int hImage_hit3;
	int hImage_hit4;
	int hImage_hit5;
	int hImage_hit6;
	int hImage_hit7;

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

	bool isDraw_;

};
