#pragma once
#include "Engine/GameObject.h"
#include <vector>
using std::vector;

/// <summary>
/// �X�e�[�W���A�G�̏o���ꏊ�̎w����Ǘ�����N���X
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
	/// BGM���~�߂�֐�
	/// </summary>
	void StopPlayBGM();

	/// <summary>
	/// �E�̓����蔻��
	/// </summary>
	/// <param name="x">�E/param>
	/// <param name="y">�E/param>
	/// <returns>�E</returns>
	int CollisionRight(int x, int y);
	/// <summary>
	///���̓����蔻��
	/// </summary>
	/// <param name="x">X�E/param>
	/// <param name="y">Y�E/param>
	/// <returns>�E�E/returns>
	int CollisionDown(int x, int y);
	/// <summary>
	/// ���̓����蔻��
	/// </summary>
	/// <param name="x">x�E/param>
	/// <param name="y">y�E/param>
	/// <returns>�E/returns>
	int CollisionLeft(int x, int y);

	/// <summary>
	/// ��̓����蔻��
	/// </summary>
	/// <param name="x">x�E/param>
	/// <param name="y">y�E/param>
	/// <returns>�E/returns>
	int CollisionUp(int x, int y);

	/// <summary>
	/// �u���b�N�Ƃ̐ڐG����
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	bool IsWallBlock(int x, int y);

	/// <summary>
	/// �N���A����Ƃ̐ڐG����
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	bool IsHitClear(int x, int y);
	bool IsHitRock(int x, int y);


	/// <summary>
	/// �G�̏���I�u�W�F�N�g�̓o�^�Acsv�̐؂�ւ��Ȃǂ̏��
	/// </summary>
	/// <param name="num"></param>
	void Reset(int num);


	/// <summary>
	/// �S�[���܂ł̋������擾����
	/// </summary>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="c"></param>
	void WhereIsGoal(int w, int h, CsvReader c); //�S�[����width���Ƃ��Ă���


private:

	//�X�e�[�W�̃u���b�N�̉摜���i�[����ϐ�
	int hStageChipImage_;

	//��ʂ������Â�����摜���i�[����ϐ�
	int hBackGroundDark_;

	//�w�i�̉摜�����i�[����ϐ�
	int hBackGround_;

	//�X�e�[�W�̏��
	int* Map;
	int scroll;

	//�X�e�[�W�S�̂̕�
	int width;
	//�X�e�[�W�S�̂̍���
	int height;
	int goalWid_; //�S�[���܂ł̕�
  
	//���݂̃X�e�[�W�̔ԍ�
	int NowStage_;


	int padAnalogInput;//xbox�̓��͂��󂯎��
	XINPUT_STATE input;//xbox�̓��͂��󂯎��
	
	//�V�󂪐Ⴉ�m�F����p�ϐ�
	bool* isSnow;

	//�X�e�[�W��BGM���i�[����ϐ�
	int Stage_BgmHandle;
};
