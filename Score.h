#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// Mpの値を評価し可視化して表示する(未実装)
/// </summary>
class Score : public GameObject
{
private:
	int hImage_;

	int NumStars = 0;
	//int animeType_;//状況
	//int animeFrame_;//駒
	//int PictFlame_;
	//int flameCounter_;
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
};

