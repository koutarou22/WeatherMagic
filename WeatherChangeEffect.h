#pragma once
#include "Engine/GameObject.h"

class WeatherChangeEffect :
    public GameObject
{
private:
    int effImage_;
	int frameCounter_; //何フレーム分描画するか
	int eraseCounter_; //画像の何番目を表示しているか
	int animeFrame_; //画像の何番目を描画するか
	bool isDraw_; //描画・更新してよいか

public:
	WeatherChangeEffect(GameObject* parent);
	~WeatherChangeEffect();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void Init(); //初期状態にセットする
	//アクセス関数
	void SetIsDraw(bool _IsDraw) { isDraw_ = _IsDraw; }
	bool GetIsDraw() { return isDraw_; }
};

