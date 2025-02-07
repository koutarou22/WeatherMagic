#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// Mpの値を評価し可視化して表示する
/// </summary>
class Score : public GameObject
{
private:
	int hStar_;

	int NumStars = 0;

	float StarMoveX;//イージング関数用の値
	float MessageMoveX;//イージング関数用の値
	float frame_Star;//フレーム数える(星用)
	float frame_Message;//フレーム数える(メッセージ用)
	bool IsStarMoveEnd;//星の動きが終わったか
	bool isPlaying; //今プレイシーンですか

public:

	Score(GameObject* parent);
	~Score();
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;
	//開放
	void Release() override;
	void SetPosition(int x, int y);
	void SetPosition(XMFLOAT3 pos);

	//急加速して急減速する
	float easeOutQuart(float time);
	//プレイシーンかどうかをセット(プレイシーンでの星の表示用)
	void SetPlaying(bool playing) { isPlaying = playing; }
};

