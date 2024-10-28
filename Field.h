#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// 
/// 
/// /// </summary>
class Field : public GameObject
{
public:
	Field(GameObject* scene);
	~Field();
	void Reset();
	void Update() override;
	void Draw() override;

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

	/// <summary>
	///
	/// </summary>
	/// <param name="StageNumber"></param>
	void LoadStage(int StageNumber);

	void NextLoadStage();
	int GetCsvWidth() { return width; }
private:
	int hImage_;
	int hBackGround_;
	int scroll;
	int* Map;
	int width;
	int height;
  
	int NowStage_;//今のステージの番号
	int hBackGroundDark_;

	int padAnalogInput;//xboxの入力を受け取る
	XINPUT_STATE input;//xboxの入力を受け取る
};
