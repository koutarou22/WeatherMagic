#pragma once
#include <DxLib.h>
#include <assert.h>
#include "Engine/GameObject.h"
#include "Weather.h"

/// <summary>
/// プレイヤーキャラの情報
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

	int GetMp() { return MagicPoint_; }
	void SetMagicMP(int _Mp) { MagicPoint_ = _Mp; }//ほかのクラスでも共有するため用
	/*void DamageHp();*/
	void Jump();
	int GetHp();
	// MagicPoint_を増やす
	void MagicUp(int _PMp);
	void MagicDown(int _MMp);
	void HpUp(int _PHp);
	void HpDown(int _MHp);

	bool IsDead() const { return isDead_; }

	void WhereIs(); //�B���x ���܂ǂ��H
	void StopWeatherSE();
	void StickTiltCheck();

private:
	int MagicPoint_;//打てる魔法の回数
	int hImage;
	int hImage_cont;
	int hImage_miss;

	
	int padAnalogInput;//xboxの入力を受け取る
	XINPUT_STATE input;//xboxの入力を受け取る
	bool CanChangeWeather;//天気を変更できるか
	int ChangeWeatherCoolTime;//天気を再変更するためのタイマー　0になったらできる
	
	GameObject* sceneTop;
	bool isDead_ = false;
	bool prevSpaceKey;
	bool onGround;
	bool onRock;
	bool onFiled;
	bool damaged = false;
	float Jump_P = 0.0f;
	int Flash_Count;

	int animType;//状況
	int animeFrame;//駒
	int PictFlame;
	int flameCounter;

	float NDTIME_; //無敵時間
	int	 CoolDownMagic_ = 0;
	int Hp_;
	int hitCount;

	float WeatherSpeed_;//MOVE_SPEEDとWeatherの値を合わせ格納する用の変数
	bool  WeatherSwitch;//高速で天候が切り替わらないようにする対策
	
	int UIGetTimer;
	bool Hp_GetFlag;
	bool Mp_GetFlag;
	bool IsHitOneCount_;
	bool DebugLog_;

	int MpHealTimer_;//一定周期でMPを回復するタイマー追加
  
	//int MAGIC_COUNT = 0;
	enum PlayerState
	{
		S_WaIk = 0,
		S_Damage,
		S_Dead,
	};
	PlayerState player_state;

	enum PlayerAnimationState 
	{
		S_Walk_A = 0,
		S_Damage_A,
		S_Dead_A,
	};
	PlayerAnimationState player_animation_state;

	int timer_ = 90;
	int WeatherTime_ = 90;
	int GaleTime_ = 300;
	int RainTime_ = 0;
	int hitX;
	int hitY;

	int StringUi_Up;

	int soundHandle;
	int RainHandle;
	int WindHandle;
	int GetItemSound;
	int MagicSound;

	float CountSnowFlame; //��̃^�C�}�[ ���Z
	//スティックを倒したかどうか
	struct Stick_Tilt {
		bool IsLeftStickTilt_left;//左スティックを左に
		bool IsLeftStickTilt_right;//左スティックを右に
		bool IsRightStickTilt_left;//右スティックを左に
		bool IsRightStickTilt_right;//右スティックを右に
	};
	Stick_Tilt stickTilt;
	
};