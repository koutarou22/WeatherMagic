#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// 
/// 
/// /// </summary> 

class CsvReader;

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
	/// <param name="x">�E/param>
	/// <param name="y">�E/param>
	/// <returns>�E</returns>
	int CollisionRight(int x, int y);
	/// <summary>
	///
	/// </summary>
	/// <param name="x">X�E/param>
	/// <param name="y">Y�E/param>
	/// <returns>�E�E/returns>
	int CollisionDown(int x, int y);
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x">x�E/param>
	/// <param name="y">y�E/param>
	/// <returns>�E/returns>
	int CollisionLeft(int x, int y);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="x">x�E/param>
	/// <param name="y">y�E/param>
	/// <returns>�E/returns>
	int CollisionUp(int x, int y);
	bool IsWallBlock(int x, int y);
	bool IsHitClear(int x, int y);

	/// <summary>
	///
	/// </summary>
	/// <param name="StageNumber"></param>
	void LoadStage(int StageNumber);

	void NextLoadStage();
	void WhereIsGoal(int w,int h,CsvReader c); //�S�[����width���Ƃ��Ă���
	int GetGoalWidth() { return goalWid_; } 
private:
	int hImage_;
	int hBackGround_;
	int scroll;
	int* Map;
	int width;
	int height;
	int goalWid_; //�S�[����width
  
	int NowStage_;//���̃X�e�[�W�̔ԍ�
	int hBackGroundDark_;

	int padAnalogInput;//xbox�̓��͂��󂯎��
	XINPUT_STATE input;//xbox�̓��͂��󂯎��

	
};
