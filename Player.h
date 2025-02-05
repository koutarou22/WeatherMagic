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
	/// MPの値を他クラスでも使う用のGet関数
	/// </summary>
	/// <returns></returns>
	int GetMp() { return MagicPoint_; }

	/// <summary>
	/// HPの値を他クラスでも使う用のGet関数
	/// </summary>
	/// <returns></returns>
	int GetHp() { return Hp_; }
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

private:

	/// <summary>
	/// ゴールまでの距離情報
	/// </summary>
	void WhereIs();

	/// <summary>
	/// スティックが倒された時に関する情報
	/// </summary>
	void StickTiltCheck();

	/// <summary>
	/// 風の時のプレイヤーの状態
	/// </summary>
	/// <param name="state"></param>
	void GaleEffect(WeatherState state);

  //各アニメーションごとの処理
  void UpdateWalk();//移動の処理
  void UpdateDamage();//ダメージを受けたときの処理
  void UpdateDead();//死亡時の処理
  void UpdateErase();//ゲームオーバーに移行する処理
  void UpdateClear();//クリア画面に移行する処理


  //音が重なるバグを止める用変数(死亡)
  bool MultiDeadSE_;
 
  /// <summary>
  /// ダメージを受けた時のSE
  /// </summary>
  void DamageSE();

  /// <summary>
  /// 天候音を止める関数
  /// </summary>
  void StopWeatherSE();

	LandingEffect* pLanding;

	std::vector<Magic *> Magics_;
	Magic* pMagic_;
	WeatherChangeEffect* pWCE_;

	//打てる魔法の回数
	int MagicPoint_;

	//プレイヤーの画像を保存する変数
	int hPlayer_;

	//ゴールまでの目印UI画像を保存する変数
	int hGoal_;
	
	int PadAnalogInput_;//xboxの入力を受け取る
	XINPUT_STATE Input_;//xboxの入力を受け取る
	bool CanChangeWeather_;//天気を変更できるか確認用変数
	int ChangeWeatherCoolTime_;//天気を再変更するためのタイマー　0になったらできる
	
	GameObject* sceneTop;
	bool isDead_ = false;
	bool prevSpaceKey_;

	//プレイヤーが地面の上に載ってるか確認用変数
	bool OnGround_;
	//プレイヤーが岩の上に載ってるか確認用変数
	bool OnRock_;

	//着地したかどうかを確認する
	bool HitLanding_;

	//ジャンプ力
	float JumpPower_ = 0.0f;

	//ダメージを受けたときのプレイヤーの点滅用変数
	int FlashCount_;

	//アニメーションに関する変数
	int AnimType_;//状況
	int AnimeFrame_;//駒
	int PictFlame_;
	int FlameCounter_;

	int	CoolDownMagic_ = 0;

	//プレイヤーのHP
	int Hp_;
	float InvincibleTime_;//無敵時間

	float WeatherSpeed_;//MOVE_SPEEDとWeatherの値を合わせ格納する用の変数
	
	//アイテムを取得時の時間取得用変数
	int ItemGetTimer_;

	//アイテムを一度に複数取得するのを防ぐ変数
	bool GetItemFlag_;
	//Hp回復アイテムを取得したか確認用変数
	bool HpGetFlag_;
	//Mp回復アイテムを取得したか確認用変数
	bool MpGetFlag_;

	//アイテム取得時の文字を少し上昇させる変数
	int CharUp_;

	//一定周期でMPを回復するタイマー追加
	int MpHealTimer_;
  
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


	//風の時、時間経過でMPを消費させる変数
	float GaleFlameDownMp_;
	//雨の時、時間経過でMPを消費させる変数
	float RainFlameDownMp_;

	//雪の時、時間経過でMPを消費させる変数
	float SnowFlameDownMp_; //snowflame

    //SE
	//天候関連
	int RainSound_;//雨の環境音
	int WindSound_;//風の環境音
	int SnowSound_;//雪の環境音

	//天候で起きるSE
	int FreezeSound_;//敵が凍ってる時のSE
	int SpeedUpSound_;//スピードアップSE

	//動作SE
	int GetMPItemSound_;//MP回復アイテム取得SE
	int GetHPItemSound_;//HP回復アイテム取得SE
	int MagicSound_;//魔法を打つSE
	int JumpSound_;//ジャンプ音SE
	int LandingSound_;//着地音SE

	int DamageSound_;//敵との接触時SE
	int DieSound_;//死亡時SE
	int WarningSound_; //HPが１になった時　警告音が鳴るSE

	//特殊敵接触時
	int HighBoundSound_;//雨の時にスライムを踏んだ時のSE
	int BoundSound_;//スライムを踏んだ時のSE

	int ClearSound_;//ClearFlagに触れた時


	bool IsTurnLeft;//左向きかどうか 左右反転処理用
	//スティックを倒したかどうか
	struct Stick_Tilt{
		bool IsLeftStickTilt_left;//左スティックを左に
		bool IsLeftStickTilt_right;//左スティックを右に
		bool IsRightStickTilt_left;//右スティックを左に
		bool IsRightStickTilt_right;//右スティックを右に
	};
	Stick_Tilt stickTilt;

	/// <summary>
	/// //現在いる場所が壁の中か調べる
	/// </summary>
	void CheckWall(Field* pf); 


	/// <summary>
	/// プレイヤーの操作入力情報
	/// </summary>
	void PlayerController();

	/// <summary>
	/// 天候の操作入力・効果情報
	/// </summary>
	void WeatherController();

	void HitClear();

	/// <summary>
	/// ゴーストと弾に関する接触情報
	/// </summary>
	void HitGhost();

	/// <summary>
	/// スライムの接触判定
	/// </summary>
	void HitSlime();
	/// <summary>
	/// HP・MPアイテムとの接触情報
	/// </summary>
	void HitItem();

	/// <summary>
	/// 岩との接触判定
	/// </summary>
	void HitRock();


	void HitStageRight();
	void HitStageLeft();
	void HitStageUp();
	void HitStageDown();
};