#pragma once
#include "Engine/GameObject.h"
#include "Weather.h"

/// <summary>
///　それぞれの天候時の背景Animation
/// </summary>

namespace
{
	const int STATE_NUM = 4; //天候の状態
}
class WeatherBackGround :
    public GameObject
{
	enum WEATHER_STATE
	{
		RAINBACK,RAINFRONT,GALE,SNOW,MAX
	};

	int images_[STATE_NUM];
	bool nowWeather_[STATE_NUM]; //現在の天気が何か判定用

	int animeFrame_;//スプライトのどのコマを描画するか
	int frameCounter_;//スプライトが次のコマに行くまでのカウンター
	int eraseCounter_;///スプライトが次のコマに行ったら増やし、アニメーション終了後消す判定

	int padAnalogInput;//xboxの入力を受け取る
	XINPUT_STATE input;//xboxの入力を受け取る
public:
	WeatherBackGround(GameObject* parent);

	~WeatherBackGround();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	/// <summary>
	/// 天候の状態を確認する用関数
	/// </summary>
	/// <param name="state">天候名</param>
	/// <param name="flag">天候状態のフラグ</param>
	/// <param name="FrameCount">フレームのカウント</param>
	/// <param name="Frame">最大フレーム数</param>
	void WeatherStateConfirm(WeatherState state, bool& flag, int FrameCount, int Frame);


	/// <summary>
	/// 天候のアニメーションを描画する関数
	/// </summary>
	/// <param name="flag">天候状態のフラグ</param>
	/// <param name="alpha">透明度</param>
	/// <param name="hImage">画像Handle</param>
	/// <param name="Size">スプライトのサイズ</param>
	void WeatherAnimation(bool& flag, int alpha, int hImage , int Size);

	/// <summary>
	/// 風用のAnimation関数
	/// </summary>
	/// <param name="flag">天候状態のフラグ</param>
	/// <param name="alpha">透明度</param>
	/// <param name="hImage">画像Handle</param>
	/// <param name="Size">スプライトのサイズX</param>
	/// <param name="Size">スプライトのサイズY</param>
	void GaleAnimation(bool& flag, int alpha, int hImage, int SizeX , int SizeY);
};

