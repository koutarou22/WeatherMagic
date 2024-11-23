#pragma once
#include "Engine/GameObject.h"
#include"Engine/Transform.h"
/// <summary>
/// MPのUI
/// </summary>
class MP :
    public GameObject
{
	int hMPBar_;//ゲージの画像ハンドル
	int hMPFrame_;//フレームの画像ハンドル
	int MPgaugeMaxVal_;//ゲージの最大値
	int MPgaugeCrrVal_;//カレントの値（現在の値） crrunt value
	Transform trs;
public:
	MP(GameObject* parent);
	~MP();
	
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetGaugeVal(int _crr, int _max)
	{
		MPgaugeCrrVal_ = _crr;
		MPgaugeMaxVal_ = _max;
	}
};

