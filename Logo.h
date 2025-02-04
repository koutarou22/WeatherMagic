#pragma once
#include "Engine/GameObject.h"
class Logo :
    public GameObject
{
private:
	int hClear_;
	float MoveValueX;//イージング関数用の値
	float frame;//フレーム数える
public:
    Logo(GameObject* parent);
	~Logo();
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;
	//開放
	void Release() override;

	/// <summary>
	/// 急加速して急減速するイージング関数(startからendまで)
	/// </summary>
	/// <param name="time">1~0まで切り替わる</param>
	/// <param name="start">初期値</param>
	/// <param name="end">最大値　ここまで来たらreturn </param>
	/// <returns></returns>
	float easeOutExpo(float time, float start, float end);

	/// <summary>
	/// 急加速して急減速するイージング関数（0から1まで）
	/// </summary>
	/// <param name="time">1~0まで切り替わる</param>
	/// <returns></returns>
	float easeOutExpo(float time);
};

