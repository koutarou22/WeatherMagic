#pragma once
#include "Engine/GameObject.h"
#include "Weather.h"

/// <summary>
/// �v���C���[�L����
/// </summary>

class Player : public GameObject
{
public:


	Player(GameObject* scene);
	~Player();
	void Update() override;
	void Draw() override;
	void SetPosition(int x, int y);

	void WeatherEffects(Weather* weather);

	void DamageHp();
	void Jump();
	int GetHp();
	
private:
	int hImage;
	GameObject* sceneTop;

	bool prevSpaceKey;
	bool onGround;//�n�ʂɂ���̂��H
	bool damaged = false;
	float Jump_P = 0.0f;
	int Flash_Count;

	int animType;//��
	int animFrame;//��
	int PictFlame;
	int flameCounter;

	float NDTIME_; //���G����
	int	  CoolDownMagic_ = 0;
	int Hp_ = 3;
	int hitCount;

	float WeatherSpeed_;//MOVE_SPEED��Weather�̒l�����킹�i�[����p�̕ϐ�
	bool  WeatherSwitch;//�����œV�󂪐؂�ւ��Ȃ��悤�ɂ���΍�
	
	int MagicPoint_;//�łĂ閂�@�̉�

	bool IsHitOneCount_;
	bool DebugLog_;

	//int MAGIC_COUNT = 0;
	enum State
	{
		S_WaIk = 0,
		S_Cry,
	};
	State state;
	int timer_ = 90;
	int WeatherTime_ = 90;
	int hitX;
	int hitY;
	Player* player_;
};