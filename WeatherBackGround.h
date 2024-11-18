#pragma once
#include "Engine/GameObject.h"
#include "Weather.h"

/// <summary>
///　それぞれの天候時の背景Animation
/// </summary>
class WeatherBackGround :
    public GameObject
{
private:
	int hImage_Sun;
	int hImage_Rain;
	int hImage_Rain2;
	int hImage_Gale;
	int hImage_Snow;

	int animeFrame;//スプライトのどのコマを描画するか
	int FrameCounter;//スプライトが次のコマに行くまでのカウンター
	int eraseCounter;///スプライトが次のコマに行ったら増やし、アニメーション終了後消す判定

	bool SunNow;//晴れか判定用
	bool RainNow;//雨か判定用
	bool GaleNow;//風か判定用
	bool SnowNow;//雪か判定用


	int padAnalogInput;//xboxの入力を受け取る
	XINPUT_STATE input;//xboxの入力を受け取る
public:
	WeatherBackGround(GameObject* parent);

	~WeatherBackGround();
	//更新
	void Update() override;

	//描画
	void Draw() override;
	//開放
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
	/// 風だけ異質なので風用のAnimation関数　拡張性は皆無
	/// </summary>
	/// <param name="flag">天候状態のフラグ</param>
	/// <param name="alpha">透明度</param>
	/// <param name="hImage">画像Handle</param>
	/// <param name="Size">スプライトのサイズX</param>
	/// <param name="Size">スプライトのサイズY</param>
	void GaleAnimation(bool& flag, int alpha, int hImage, int SizeX , int SizeY);
};

