#pragma once
#include "Engine/GameObject.h"
#include"EnemyMagic.h"

class FreezeEffect;
class EnemyMagic;

/// <summary>
/// �e�ۂ��΂��Ă��邨�����̏��
/// </summary>
class Ghost : public GameObject
{
public:
	Ghost(GameObject* parent);
	~Ghost();
	void Update() override;
	void Draw() override;
	void SetPosition(int x, int y);
	bool ColliderCircle(float x, float y, float r);
	
	void Release() override;
private:
	EnemyMagic* emg;
	FreezeEffect* pFreeze;
	float SinAngle_;
	int hGhost_;
	
	//�A�j���[�V�����p�̕ϐ�
	int AnimeType_;//��
	int AnimeFrame_;//��
	int PictFlame_;
	int FlameCounter_;

	int EnemyHandle_;

	//�����ēx�łĂ�悤�ɂȂ�܂ł̃N�[���^�C���i�[�p�ϐ�
	int CoolDownAttack_;

	int GhostDamageHandle;//�_���[�W��
	int GhostAttackHandle;//�U����

	/// <summary>
	/// �U���̏��E����
	/// </summary>
	void GhostAttack();

	/// <summary>
	/// �S�[�X�g�̓����̏��E����
	/// </summary>
	void GhostMove();

	void HitMagic();

};
