#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// 地面（ステージ）
/// ※ステージ２を作る予定だったが、うまくいかなかったので修正
/// </summary>
class Field : public GameObject
{
public:
	Field(GameObject* scene);
	~Field();
	void Reset();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// 右側の点が当たっているか調べる
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <returns>めり込んだ量(ドット)</returns>
	int CollisionRight(int x, int y);
	/// <summary>
	/// 下の点が当たっているか調べる
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	/// <returns>めり込んだ量（ドット）</returns>
	int CollisionDown(int x, int y);
	/// <summary>
	/// 左の点が当たっているか調べる
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	/// <returns>めり込んだ量</returns>
	int CollisionLeft(int x, int y);

	/// <summary>
	/// 上の点があたっているか調べる
	/// </summary>
	/// <param name="x">x座標</param>
	/// <param name="y">y座標</param>
	/// <returns>めり込んだ量</returns>
	int CollisionUp(int x, int y);
	bool IsWallBlock(int x, int y);
	bool IsHitClear(int x, int y);

	/// <summary>
	/// ステージロード用
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
  
  int NowStage_ = 0;//現在のステージ番号を保管する用
	int NowStage_;//現在のステージ番号を保管する用
	int hBackGroundDark_;

	int padAnalogInput;//xbox�̓��͂��󂯎��
	XINPUT_STATE input;//xbox�̓��͂��󂯎��
};
