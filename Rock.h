#pragma once
#include"Engine/GameObject.h"
#include"Player.h"
#include "Weather.h"

/// <summary>
/// 動かしたり乗ったりできる石の情報
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
	bool GetNotMoveRight() { return CanMoveRight == false; }
	bool GetNotMoveLeft() { return CanMoveLeft == false; }

	//動かしたときの引きずるような音
	int DustHandle;
	
private:
	bool PressKey_R = false;
	bool PressKey_L = false;

	//挙動がおかしくならないようにする処理
	bool CanMoveRight;
	bool CanMoveLeft;

	//岩の画像を取得する変数
	int hRock_;
	float JumpPower_ = 0.0f;
	bool onGround;//地面にいるのか？

	int padAnalogInput;//xboxの入力を受け取る
	XINPUT_STATE input;//xboxの入力を受け取る

	//音が再生中か確認するFlag
	bool isPlayingDust;

	//動いているか確認する用のフラグ
	bool isMove;

	/// <summary>
    /// ステージとの接触判定情報
    /// </summary>
	void HitStage();
};

