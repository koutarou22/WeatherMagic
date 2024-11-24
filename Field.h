#pragma once
#include "Engine/GameObject.h"
#include <vector>

/// <summary>
/// stage、敵の出現など重要なクラス
/// </summary>

class CsvReader;

using std::vector;

class Field : public GameObject
{
public:
	Field(GameObject* scene);
	~Field();
	void Reset();
	void Update() override;
	void Draw() override;

	void Release() override;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="x">・/param>
	/// <param name="y">・/param>
	/// <returns>・</returns>
	int CollisionRight(int x, int y);
	/// <summary>
	///
	/// </summary>
	/// <param name="x">X・/param>
	/// <param name="y">Y・/param>
	/// <returns>・・/returns>
	int CollisionDown(int x, int y);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x">x・/param>
	/// <param name="y">y・/param>
	/// <returns>・/returns>
	int CollisionLeft(int x, int y);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="x">x・/param>
	/// <param name="y">y・/param>
	/// <returns>・/returns>
	int CollisionUp(int x, int y);
	bool IsWallBlock(int x, int y);
	bool IsHitClear(int x, int y);
	bool IsHitRock(int x, int y);

	/// <summary>
	///
	/// </summary>
	/// <param name="StageNumber"></param>
	//void LoadStage(int StageNumber);
	//void Reset(int StageNumber);

	void Reset(int num);

	void WhereIsGoal(int w,int h,CsvReader c); //ゴールのwidthをとってくる
	int GetGoalWidth() { return goalWid_; } 

	void StopPlayBGM();
private:
	int hImage_;
	int hBackGround_;
	int scroll;
	int* Map;
	int width;
	int height;
	int goalWid_; //ゴールのwidth
  
	int NowStage_;//今のステージの番号
	int hBackGroundDark_;

	int padAnalogInput;//xboxの入力を受け取る
	XINPUT_STATE input;//xboxの入力を受け取る
	
	bool* isSnow;//雪フラグ


	int Stage_BgmHandle;
};
