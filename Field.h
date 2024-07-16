#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// 地面（プレイフィールド）
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
	//bool IsRockBlock(int x, int y);
	bool IsHitClear(int x, int y);
	//bool IsColliding(const Rect& a, const Rect& b);
private:
	int hImage_;
	int hBackGround_;
	int scroll;
	int* Map;
	int width;
	int height;

};
