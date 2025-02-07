#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
#include "Weather.h"
/// <summary>
/// �X���C���̏��
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
	/// <param name="WeatherSpeed_"></param>
	/// <param name="MOVE_SPEED"></param>
	/// <param name="WeatherEffect"></param>
	/// <param name="ScaleEffect_"></param>
	void RainScale(WeatherState state, Transform& transform,
	float& WeatherSpeed_, float MOVE_SPEED, float WeatherEffect, float& ScaleEffect_);


	
private:
	int hSlime_;
	bool onGround;//�n�ʂɂ���̂��H

	bool HitLanding;//���n�������ǂ������m�F����

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
	int JumpHandle; 
	//�C�₵������SE
	int StunHandle; 

	FreezeEffect* pFreeze;

	/// <summary>
	/// �X�e�[�W�Ƃ̐ڐG������
	/// </summary>
	void HitStage();

	/// <summary>
	/// �v���C���[�̒e�Ƃ̐ڐG���
	/// </summary>
	void HitPlayerMagic();

	/// <summary>
	/// ��Ƃ̐ڐG����
	/// </summary>
	void HitRock();

	/// <summary>
	/// �X�e�[�W�̕ǂɐڐG����Ɣ��]���鏈��
	/// </summary>
	void HitStageHitTurn();

	/// <summary>
	/// �X���C���̃W�����v�A��ԂȂǊ�b�I�ȏ��
	/// </summary>
	void SlimeBound();
};

