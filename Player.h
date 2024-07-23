#pragma once
#include "Engine/GameObject.h"
#include "Weather.h"

/// <summary>
/// �v���C���[�L����
/// </summary>
//
class Player : public GameObject
{
public:


	Player(GameObject* scene);
	~Player();
	void Update() override;
	void Draw() override;
	void SetPosition(int x, int y);

	void WeatherEffects(Weather* weather);

	int GetMp() { return MagicPoint_; }
	void SetMagicMP(int _Mp) { MagicPoint_ = _Mp; }//�ق��̃N���X�ł����L���邽�ߗp
	void DamageHp();
	void Jump();
	int GetHp();
	// MagicPoint_�𑝂₷���\�b�h
	void MagicUp(int _PMp);
	void MagicDown(int _MMp);
	void HpUp(int _PHp);
	void HpDown(int _MHp);

	

private:
	int MagicPoint_;//�łĂ閂�@�̉�
	int hImage;
	GameObject* sceneTop;

	bool prevSpaceKey;
	bool onGround;
	bool onRock;
	bool onFiled;
	bool damaged = false;
	float Jump_P = 0.0f;
	int Flash_Count;

	int animType;//��
	int animFrame;//��
	int PictFlame;
	int flameCounter;

	float NDTIME_; //���G����
	int	 CoolDownMagic_ = 0;
	int Hp_;
	int hitCount;

	float WeatherSpeed_;//MOVE_SPEED��Weather�̒l�����킹�i�[����p�̕ϐ�
	bool  WeatherSwitch;//�����œV�󂪐؂�ւ��Ȃ��悤�ɂ���΍�
	
	int UIGetTimer;
	bool Hp_GetFlag;
	bool Mp_GetFlag;
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
	int GaleTime_ = 0;
	int RainTime_ = 0;
	int hitX;
	int hitY;

	int StringUi_Up;
};