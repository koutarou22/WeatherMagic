#pragma once
#include "Engine/GameObject.h"
#include <vector>
using std::vector;

/// <summary>
/// ステージ情報、敵の出現場所の指定を管理するクラス
/// </summary>
class CsvReader;
class Field : public GameObject
{
public:
	Field(GameObject* scene);
	~Field();
	void Reset();
	void Update() override;
	void Draw() override;
	void Release() override;
	int GetGoalWidth() { return goalWid_; } 

	/// <summary>
	/// BGMを止める関数
	/// </summary>
	void StopPlayBGM();

	/// <summary>
	/// 右の当たり判定
	/// </summary>
	/// <param name="x">・/param>
	/// <param name="y">・/param>
	/// <returns>・</returns>
	int CollisionRight(int x, int y);
	/// <summary>
	///左の当たり判定
	/// </summary>
	/// <param name="x">X・/param>
	/// <param name="y">Y・/param>
	/// <returns>・・/returns>
	int CollisionDown(int x, int y);
	/// <summary>
	/// 下の当たり判定
	/// </summary>
	/// <param name="x">x・/param>
	/// <param name="y">y・/param>
	/// <returns>・/returns>
	int CollisionLeft(int x, int y);

	/// <summary>
	/// 上の当たり判定
	/// </summary>
	/// <param name="x">x・/param>
	/// <param name="y">y・/param>
	/// <returns>・/returns>
	int CollisionUp(int x, int y);

	/// <summary>
	/// ブロックとの接触判定
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	bool IsWallBlock(int x, int y);

	/// <summary>
	/// クリア判定との接触判定
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	bool IsHitClear(int x, int y);
	bool IsHitRock(int x, int y);


	/// <summary>
	/// 敵の情報やオブジェクトの登録、csvの切り替えなどの情報
	/// </summary>
	/// <param name="num"></param>
	void Reset(int num);


	/// <summary>
	/// ゴールまでの距離を取得する
	/// </summary>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="c"></param>
	void WhereIsGoal(int w, int h, CsvReader c); //ゴールのwidthをとってくる


private:

	//ステージのブロックの画像を格納する変数
	int hStageChipImage_;

	//画面を少し暗くする画像を格納する変数
	int hBackGroundDark_;

	//背景の画像情報を格納する変数
	int hBackGround_;

	//ステージの情報
	int* Map;
	int scroll;

	//ステージ全体の幅
	int width;
	//ステージ全体の高さ
	int height;
	int goalWid_; //ゴールまでの幅
  
	//現在のステージの番号
	int NowStage_;


	int padAnalogInput;//xboxの入力を受け取る
	XINPUT_STATE input;//xboxの入力を受け取る
	
	//天候が雪か確認する用変数
	bool* isSnow;

	//ステージのBGMを格納する変数
	int Stage_BgmHandle;
};
