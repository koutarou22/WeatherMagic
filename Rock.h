#pragma once
#include"Engine/GameObject.h"
#include"Player.h"
#include "Weather.h"

/// <summary>
///石の操作・動作・状態を管理
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
	/// 天候の状況を管理
	/// </summary>
	/// <param name="weather"></param>
	void WeatherEffects(Weather* weather);

	/// <summary>
	/// 天候が風の時の岩の状態
	/// </summary>
	/// <param name="state"></param>
	void GaleEffect(WeatherState state);

	bool ColliderRect(float x, float y, float w, float h);
	
	/// <summary>
	/// 他のクラスで値を取得する用のGet関数
	/// </summary>
	/// <returns></returns>
	bool GetNotMoveRight() { return CanMoveRight_ == false; }
	bool GetNotMoveLeft() { return CanMoveLeft_ == false; }

	//動かしたときの引きずるような音
	int DustHandle;
	
private:
	bool PressKeyR_ = false;
	bool PressKeyL_ = false;

	//挙動がおかしくならないように接触を判断する処理
	bool CanMoveRight_;
	bool CanMoveLeft_;

	//岩の画像を取得する変数
	int hRock_;
	float JumpPower_ = 0.0f;
	bool OnGround_;//地面にいるのか？

	int PadAnalogInput_;//xboxの入力を受け取る
	XINPUT_STATE Input_;//xboxの入力を受け取る

	//音が再生中か確認するFlag
	bool IsPlayingDust_;

	//動いているか確認する用のフラグ
	bool IsMove_;

	/// <summary>
    /// ステージとの接触判定情報
    /// </summary>
	void CheckHitStage();
};

