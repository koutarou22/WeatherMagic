#pragma once
#include"Engine/GameObject.h"
#include"Player.h"
#include "Weather.h"

/// <summary>
/// ����������������ł���΂̏��
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
	bool GetNotMoveRight() { return CanMoveRight == false; }
	bool GetNotMoveLeft() { return CanMoveLeft == false; }

	//���������Ƃ��̈�������悤�ȉ�
	int DustHandle;
	
private:
	bool PressKey_R = false;
	bool PressKey_L = false;

	//���������������Ȃ�Ȃ��悤�ɂ��鏈��
	bool CanMoveRight;
	bool CanMoveLeft;

	//��̉摜���擾����ϐ�
	int hRock_;
	float JumpPower_ = 0.0f;
	bool onGround;//�n�ʂɂ���̂��H

	int padAnalogInput;//xbox�̓��͂��󂯎��
	XINPUT_STATE input;//xbox�̓��͂��󂯎��

	//�����Đ������m�F����Flag
	bool isPlayingDust;

	//�����Ă��邩�m�F����p�̃t���O
	bool isMove;

	/// <summary>
    /// �X�e�[�W�Ƃ̐ڐG������
    /// </summary>
	void HitStage();
};

