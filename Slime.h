#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
#include "Weather.h"
/// <summary>
/// �X���C���̓���E��Ԃ��Ǘ�
/// </summary>
class FreezeEffect;
class Slime : public GameObject
{
public:

	Slime(GameObject* scene);
	~Slime();
	void Update() override;
	void Draw() override;
	void Release() override;

	/// <summary>
	/// �V��̏��
	/// </summary>
	/// <param name="weather"></param>
	void WeatherEffects(Weather* weather);

	bool ColliderRect(float x, float y, float w, float h);
	void SetPosition(int x, int y);

	/// <summary>
	/// �V�󂪉J�̎��̃X���C���̏�Ԃ��Ǘ�
	/// </summary>
	/// <param name="state">�V��̏��</param>
	/// <param name="transform">���W</param>
	/// <param name="WeatherSpeed_">�V�󎞂̈ړ����x</param>
	/// <param name="MOVE_SPEED">�ړ����x</param>
	/// <param name="WeatherEffect">�V��N���X����̑��x�̏��</param>
	/// <param name="ScaleEffect_">�T�C�Y</param>
	void RainScale(WeatherState state, Transform& transform,
	float& WeatherSpeed_, float MOVE_SPEED, float WeatherEffect, float& ScaleEffect_);

private:
	int hSlime_;
	bool OnGround_;//�n�ʂɂ���̂��H

	bool HitLanding_;//���n�������ǂ������m�F����

	//�A�j���[�V�����̃t���[�����
	int flameCounter_;
	int animeFrame_;

	//�X���C�����U�����󂯂����̒�~����
	int StunTimer_;

	//�X���C�����ēx�W�����v����܂ł̑ҋ@����
	int CoolStayTime_;

	//�W�����v��
	float JumpPower_ = 0.0f;
	//�V�󎞂̈ړ����x
	float WeatherSpeed_ = 0.0f;

	//�X���C���̃T�C�Y�̏��
	float ScaleEffect_ = 0.0f;

	//�X���C�����ǂɂԂ�������A���]���鏈��
	bool Reverse_ = false;
	int direction = 1;
	
	//�X���C���𓥂񂾎���SE
	int JumpHandle_; 
	//�C�₵������SE
	int StunHandle_; 

	FreezeEffect* pFreeze;

	/// <summary>
	/// �X�e�[�W�Ƃ̐ڐG������
	/// </summary>
	void CheckHitStage();

	/// <summary>
	/// �v���C���[�̒e�Ƃ̐ڐG���
	/// </summary>
	void CheckHitPlayerMagic();

	/// <summary>
	/// ��Ƃ̐ڐG����
	/// </summary>
	void CheckHitRock();

	/// <summary>
	/// �X�e�[�W�̕ǂɐڐG����Ɣ��]���鏈��
	/// </summary>
	void CheckHitStageHitTurn();

	/// <summary>
	/// �X���C���̃W�����v�A��ԂȂǊ�b�I�ȏ��
	/// </summary>
	void SlimeAbility();
};

