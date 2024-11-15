#pragma once
#include"Engine/GameObject.h"
#include"Player.h"
#include "Weather.h"

/// <summary>
/// �v���C���[������p�̐΂̏��
/// ���v�C������\��
/// </summary>
class Rock :public GameObject
{
public:
	Rock(GameObject* scene);
	~Rock();
	void Update() override;
	void Draw() override;
	void SetPosition(int x, int y);
	void WeatherEffects(Weather* weather);
	void GaleEffect(WeatherState state);
	//int CollisionUp(int x, int y);

	/// <summary>
	///�l�p�̓����蔻��
	/// </summary>
	/// <returns></returns>
	bool ColliderRect(float x, float y, float w, float h);
	void HitCollisionWithRock();

	/// <summary>
	/// �v���C���[����ɏ���Ă�Ƃ��v���C���[���������Ȃ��悤�ɂ���悤
	/// </summary>
	/// <returns></returns>
	bool GetNotMoveRight() { return CanMoveRight == false; }
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool GetNotMoveLeft() { return CanMoveLeft == false; }

	float x;
	float y;
	
private:
	bool PressKey_R = false;
	bool PressKey_L = false;

	//���������������Ȃ�Ȃ��悤�ɂ��鏈��
	bool CanMoveRight;
	bool CanMoveLeft;

	int WindTimer_ = 300;

	int hImage_;
	float Jump_P = 0.0f;
	bool onGround;//�n�ʂɂ���̂��H

	float Width_;  
	float Height_; 

	int padAnalogInput;//xbox�̓��͂��󂯎��
	XINPUT_STATE input;//xbox�̓��͂��󂯎��

};

