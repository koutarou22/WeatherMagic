#pragma once
#include "Engine/GameObject.h"
class WeatherChangeEffect :
    public GameObject
{
private:
    int hImage_;
	int animeFrame;
	int FrameCounter;
	int eraseCounter;
	bool isDraw_;//isDrawがtrueなら描画+更新

public:
	WeatherChangeEffect(GameObject* parent);

	~WeatherChangeEffect() ;

	//更新
	void Update() override;

	//描画
	void Draw() override;
	//開放
	void Release() override;
	void SetIsDraw(bool _IsDraw) { isDraw_ = _IsDraw; }
	bool GetIsDraw() { return isDraw_; }
};

