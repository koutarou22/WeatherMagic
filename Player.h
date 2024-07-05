#pragma once
#include "Engine/GameObject.h"
#include "Weather.h"

/// <summary>
/// �v���C���[�L����
/// </summary>
/// 
/// 

class Player : public GameObject
{
public:


	Player(GameObject* scene);
	~Player();
	void Update() override;
	void Draw() override;
	void SetPosition(int x, int y);

	void WeatherEffects(Weather* weather);
	void Jump();
	int GetHp();

private:
	int hImage;
	GameObject* sceneTop;

	bool prevSpaceKey;
	bool onGround;//�n�ʂɂ���̂��H

	float Jump_P = 0.0f;

	int animType;//��
	int animFrame;//��
	int PictFlame;
	int flameCounter;

	float NDTIME_; //���G����
	int Hp_ = 3;
	int hitCount;

	float WeatherSpeed_;//MOVE_SPEED��Weather�̒l�����킹�i�[����p�̕ϐ�
	bool  WeatherSwitch;//�����œV�󂪐؂�ւ��Ȃ��悤�ɂ���΍�
	bool CoolDown;
	int MagicPoint;
	enum State
	{
		S_WaIk = 0,
		S_Cry,
	};
	State state;


	int hitX;
	int hitY;
	Player* player_;
};