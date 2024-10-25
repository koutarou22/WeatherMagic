#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// �n�ʁi�X�e�[�W�j
/// ���X�e�[�W�Q�����\�肾�������A���܂������Ȃ������̂ŏC��
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
	bool IsHitClear(int x, int y);

	/// <summary>
	/// �X�e�[�W���[�h�p
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

	int NowStage_;//���݂̃X�e�[�W�ԍ���ۊǂ���p
	int hBackGroundDark_;

	int padAnalogInput;//xbox�̓��͂��󂯎��
	XINPUT_STATE input;//xbox�̓��͂��󂯎��
};
