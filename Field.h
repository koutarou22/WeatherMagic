#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// �n�ʁi�v���C�t�B�[���h�j
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
	/// �E���̓_���������Ă��邩���ׂ�
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <returns>�߂荞�񂾗�(�h�b�g)</returns>
	int CollisionRight(int x, int y);
	/// <summary>
	/// ���̓_���������Ă��邩���ׂ�
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	/// <returns>�߂荞�񂾗ʁi�h�b�g�j</returns>
	int CollisionDown(int x, int y);
	/// <summary>
	/// ���̓_���������Ă��邩���ׂ�
	/// </summary>
	/// <param name="x">x���W</param>
	/// <param name="y">y���W</param>
	/// <returns>�߂荞�񂾗�</returns>
	int CollisionLeft(int x, int y);

	/// <summary>
	/// ��̓_���������Ă��邩���ׂ�
	/// </summary>
	/// <param name="x">x���W</param>
	/// <param name="y">y���W</param>
	/// <returns>�߂荞�񂾗�</returns>
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
