#pragma once
#include "Engine/GameObject.h"
#include "Weather.h"
class WeatherBackGround :
    public GameObject
{
private:
	int hImage_Sun;
	int hImage_Rain;
	int hImage_Gale;
	int hImage_Snow;

	int animeFrame;//スプライトのどのコマを描画するか
	int FrameCounter;//スプライトが次のコマに行くまでのカウンター
	int eraseCounter;///スプライトが次のコマに行ったら増やし、アニメーション終了後消す判定
public:
	WeatherBackGround(GameObject* parent);

	~WeatherBackGround();
	//更新
	void Update() override;

	//描画
	void Draw() override;
	//開放
	void Release() override;
};

