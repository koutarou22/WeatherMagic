#pragma once
#include "Engine/GameObject.h"

class FreezeEffect;

/// <summary>
/// �e�ۂ��΂��Ă��邨�����̏��
/// </summary>
class Ghost : public GameObject
{
public:
	Ghost(GameObject* scene);
	~Ghost();
	void Update() override;
	void Draw() override;
	//�~�̓����蔻�������
	void SetPosition(int x, int y);
	bool ColliderCircle(float x, float y, float r);
	
	void Release() override;
private:
	float sinAngle;
	int hImage_;
	int animeType_;//��
	int animeFrame_;//��
	int PictFlame_;
	int flameCounter_;

	int CoolDownAttack_ = 0;
	int timer_ = 90;
	enum State//���ǎg���ĂȂ�
	{
		S_WaIk = 0,
		S_Cry,
	};
	State state;

	bool FreezeOne;//�X������񂵂��o���Ȃ��悤�ɂ���@���d���Ȃ����̂�

	int GhostDamageHandle;//�_���[�W��
	int GhostAttackHandle;//�U����
	FreezeEffect* pFreeze;
};
