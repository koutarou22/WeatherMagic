#pragma once
#include <DxLib.h>
#include <assert.h>
#include<vector>
#include "Engine/GameObject.h"
#include "Weather.h"
#include"Magic.h"
#include"WeatherChangeEffect.h"
#include"LandingEffect.h"

/// <summary>
/// プレイヤーキャラの情報
/// </summary>
class Field;
class Player : public GameObject
{
public:
	Player(GameObject* scene);
	~Player();
	void Update() override;
	void Draw() override;
	void SetPosition(int x, int y);
	void Release() override;
	void WeatherEffects(Weather* weather);
	
	/// <summary>
	/// 他のクラスでも値をSetできる関数
	/// </summary>
	/// <param name="_Mp"></param>
	void SetMagicMP(int _Mp) { MagicPoint_ = _Mp; }

	void Jump();
	/// <summary>
	/// MPの値を他クラスでもつかえるGet関数
	/// </summary>
	/// <returns></returns>
	int GetMp();
	/// <summary>
	/// HPの値を他クラスでもつかえるGet関数
	/// </summary>
	/// <returns></returns>
	int GetHp();
	/// <summary>
	/// MPの値を増やせる関数
	/// </summary>
	/// <param name="_PMp"></param>
	void MagicUp(int _PMp);
	/// <summary>
	/// MPの値を減らす関数
	/// </summary>
	/// <param name="_MMp"></param>
	void MagicDown(int _MMp);

	/// <summary>
	/// HPの値を増やす関数
	/// </summary>
	/// <param name="_PHp"></param>
	void HpUp(int _PHp);
	/// <summary>
	/// HPの値を減らす関数
	/// </summary>
	/// <param name="_MHp"></param>
	void HpDown(int _MHp);

	/// <summary>
	/// 生きてるか死んでるか確認する関数
	/// </summary>
	/// <returns></returns>
	bool IsDead() const { return isDead_; }

	/// <summary>
	/// ゴールまでの距離情報
	/// </summary>
	void WhereIs(); //tassei do

	/// <summary>
	/// スティックが倒された時に関する情報
	/// </summary>
	void StickTiltCheck();

	/// <summary>
	/// 風の時のプレイヤーの状態
	/// </summary>
	/// <param name="state"></param>
	void GaleEffect(WeatherState state);

  void UpdateWalk();
  void UpdateDamage();
  void UpdateDead();
  void UpdateErase();
  void UpdateClear();

  //音関係のSE用関数
  //音が重なるバグを止める用(死亡)

  bool MultiDeadSE;
  //----------------------------
 
  /// <summary>
  /// ダメージを受けた時のSE
  /// </summary>
  void DamageSE();

  /// <summary>
  /// 天候音を止める関数
  /// </summary>
  void StopWeatherSE();

private:

	LandingEffect* pLanding;

	std::vector<Magic *> Magics_;
	Magic* pMagic_;
	WeatherChangeEffect* pWCE_;

	//打てる魔法の回数
	int MagicPoint_;

	int hPlayer_;
	int hImage_cont;
	int hImage_miss;
	int hGoal;
	
	int padAnalogInput;//xboxの入力を受け取る
	XINPUT_STATE input;//xboxの入力を受け取る
	bool CanChangeWeather;//天気を変更できるか
	int ChangeWeatherCoolTime;//天気を再変更するためのタイマー　0になったらできる
	
	GameObject* sceneTop;
	bool isDead_ = false;
	bool prevSpaceKey;
	bool onGround;//Player on the Ground?
	bool onRock;//Player on the Rock?
	bool damaged = false;
	bool HitLanding;//着地したかどうかを確認する
	bool hasLanded;//一回インスタンスを読んだら再度読ませない用

	float Jump_P = 0.0f;
	int Flash_Count;

	int animType;//状況
	int animeFrame;//駒
	int PictFlame;
	int flameCounter;

	float NDTIME_; //無敵時間
	int	 CoolDownMagic_ = 0;
	int Hp_;
	bool DamageFlag;

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
		S_Erase,
		S_Clear
	};
	PlayerState player_state;

	enum PlayerAnimationState 
	{
		S_Walk_A = 0,
		S_Damage_A,
		S_Dead_A,
		S_Erase_A,
	};
	PlayerAnimationState player_animation_state;

	int timer_ = 90;
	int WeatherTime_ = 90;
	int GaleTime_ = 300;
	int RainTime_ = 0;
	int hitX;
	int hitY;

	int StringUi_Up;

    //SE
	//天候関連
	int RainHandle;//晴
	int WindHandle;//風
	int SnowHandle;//雪

	//天候で起きるSE
	int FreezeHandle;//『敵が凍ってる』と思わせるようなSE
	int SpeedUpHandle;//風になったときスピードUpしてると思わせるようなSE

	//動作SE
	int GetMPItemHandle;//MP回復アイテム取得
	int GetHPItemHandle;//HP回復アイテム取得
	int MagicHandle;//魔法打つ
	int JumpHandle;//ジャンプ音
	int LandingHandle;//着地音

	int DamageHandle;//接触時
	int DieHandle;//死亡時
	int WarningHandle; //HPになった時　警告音が鳴る

	//特殊敵接触時
	int HighBoundHandle;//雨の時にスライムを踏んだ時の音
	int BoundHandle;//スライムを踏んだ時のSE

	int ClearHandle;//ClearFlagに触れた時

	int CameraPosX;

	float CountSnowFlame; //snowflame
	bool IsTurnLeft;//左向きかどうか 左右反転処理用
	//スティックを倒したかどうか
	struct Stick_Tilt{
		bool IsLeftStickTilt_left;//左スティックを左に
		bool IsLeftStickTilt_right;//左スティックを右に
		bool IsRightStickTilt_left;//右スティックを左に
		bool IsRightStickTilt_right;//右スティックを右に
	};
	Stick_Tilt stickTilt;

	void CheckWall(Field* pf); //今いるところが壁の中か調べる
	
};