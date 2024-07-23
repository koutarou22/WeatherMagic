#pragma once
#include "Engine/GameObject.h"
#include "Weather.h"

/// <summary>
/// プレイヤーキャラ
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
	void SetMagicMP(int _Mp) { MagicPoint_ = _Mp; }//ほかのクラスでも共有するため用
	void DamageHp();
	void Jump();
	int GetHp();
	// MagicPoint_を増やすメソッド
	void MagicUp(int _PMp);
	void MagicDown(int _MMp);
	void HpUp(int _PHp);
	void HpDown(int _MHp);

	

private:
	int MagicPoint_;//打てる魔法の回数
	int hImage;
	GameObject* sceneTop;

	bool prevSpaceKey;
	bool onGround;
	bool onRock;
	bool onFiled;
	bool damaged = false;
	float Jump_P = 0.0f;
	int Flash_Count;

	int animType;//状況
	int animFrame;//駒
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