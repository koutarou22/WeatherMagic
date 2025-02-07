#pragma once
#include"Engine/GameObject.h"
#include"Player.h"
#include "Weather.h"

/// <summary>
///�΂̑���E����E��Ԃ��Ǘ�
/// </summary>
class Rock :public GameObject
{
public:
	Rock(GameObject* scene);
	~Rock();
	void Update() override;
	void Draw() override;
	void SetPosition(int x, int y);
	void Release() override;

	/// <summary>
	/// �V��̏󋵂��Ǘ�
	/// </summary>
	/// <param name="weather"></param>
	void WeatherEffects(Weather* weather);

	/// <summary>
	/// �V�󂪕��̎��̊�̏��
	/// </summary>
	/// <param name="state"></param>
	void GaleEffect(WeatherState state);

	bool ColliderRect(float x, float y, float w, float h);
	
	/// <summary>
	/// ���̃N���X�Œl���擾����p��Get�֐�
	/// </summary>
	/// <returns></returns>
	bool GetNotMoveRight() { return CanMoveRight_ == false; }
	bool GetNotMoveLeft() { return CanMoveLeft_ == false; }

	//���������Ƃ��̈�������悤�ȉ�
	int DustHandle;
	
private:
	bool PressKeyR_ = false;
	bool PressKeyL_ = false;

	//���������������Ȃ�Ȃ��悤�ɐڐG�𔻒f���鏈��
	bool CanMoveRight_;
	bool CanMoveLeft_;

	//��̉摜���擾����ϐ�
	int hRock_;
	float JumpPower_ = 0.0f;
	bool OnGround_;//�n�ʂɂ���̂��H

	int PadAnalogInput_;//xbox�̓��͂��󂯎��
	XINPUT_STATE Input_;//xbox�̓��͂��󂯎��

	//�����Đ������m�F����Flag
	bool IsPlayingDust_;

	//�����Ă��邩�m�F����p�̃t���O
	bool IsMove_;

	/// <summary>
    /// �X�e�[�W�Ƃ̐ڐG������
    /// </summary>
	void CheckHitStage();
};

