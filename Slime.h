#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
#include "Weather.h"
/// <summary>
/// スライムの動作・状態を管理
/// </summary>
class FreezeEffect;
class Slime : public GameObject
{
public:

	Slime(GameObject* scene);
	~Slime();
	void Update() override;
	void Draw() override;
	void Release() override;

	/// <summary>
	/// 天候の情報
	/// </summary>
	/// <param name="weather"></param>
	void WeatherEffects(Weather* weather);

	bool ColliderRect(float x, float y, float w, float h);
	void SetPosition(int x, int y);

	/// <summary>
	/// 天候が雨の時のスライムの状態を管理
	/// </summary>
	/// <param name="state">天候の状態</param>
	/// <param name="transform">座標</param>
	/// <param name="WeatherSpeed_">天候時の移動速度</param>
	/// <param name="MOVE_SPEED">移動速度</param>
	/// <param name="WeatherEffect">天候クラスからの速度の情報</param>
	/// <param name="ScaleEffect_">サイズ</param>
	void RainScale(WeatherState state, Transform& transform,
	float& WeatherSpeed_, float MOVE_SPEED, float WeatherEffect, float& ScaleEffect_);

private:
	int hSlime_;
	bool OnGround_;//地面にいるのか？

	bool HitLanding_;//着地したかどうかを確認する

	//アニメーションのフレーム情報
	int flameCounter_;
	int animeFrame_;

	//スライムが攻撃を受けた時の停止時間
	int StunTimer_;

	//スライムが再度ジャンプするまでの待機時間
	int CoolStayTime_;

	//ジャンプ力
	float JumpPower_ = 0.0f;
	//天候時の移動速度
	float WeatherSpeed_ = 0.0f;

	//スライムのサイズの情報
	float ScaleEffect_ = 0.0f;

	//スライムが壁にぶつかったら、反転する処理
	bool Reverse_ = false;
	int direction = 1;
	
	//スライムを踏んだ時のSE
	int JumpHandle_; 
	//気絶した時のSE
	int StunHandle_; 

	FreezeEffect* pFreeze;

	/// <summary>
	/// ステージとの接触判定情報
	/// </summary>
	void CheckHitStage();

	/// <summary>
	/// プレイヤーの弾との接触情報
	/// </summary>
	void CheckHitPlayerMagic();

	/// <summary>
	/// 岩との接触判定
	/// </summary>
	void CheckHitRock();

	/// <summary>
	/// ステージの壁に接触すると反転する処理
	/// </summary>
	void CheckHitStageHitTurn();

	/// <summary>
	/// スライムのジャンプ、状態など基礎的な情報
	/// </summary>
	void SlimeAbility();
};

