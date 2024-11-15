#pragma once
#include "Engine/GameObject.h"
class WeatherChangeEffect :
    public GameObject
{
private:
    int hImage_;
	int animeFrame;//スプライトのどのコマを描画するか
	int FrameCounter;//スプライトが次のコマに行くまでのカウンター
	int eraseCounter;///スプライトが次のコマに行ったら増やし、アニメーション終了後消す判定
public:
	WeatherChangeEffect(GameObject* parent);

	~WeatherChangeEffect() ;

	//更新
	void Update() override;

	//描画
	void Draw() override;
	//開放
	void Release() override;
};

