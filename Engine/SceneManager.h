#pragma once
#include "global.h"
#include "GameObject.h"
#include<string>

enum SCENE_ID
{
	SCENE_ID_TITLE,
	SCENE_ID_LEVEL,
	SCENE_ID_PLAY,
	SCENE_ID_LOAD,
	SCENE_ID_GAMEOVER,
	SCENE_ID_CLEAR
};

//-----------------------------------------------------------
//�V�[���؂�ւ���S������I�u�W�F�N�g
//-----------------------------------------------------------
class SceneManager : public GameObject
{
public:

	//�R���X�g���N�^
	//�����Fparent	�e�I�u�W�F�N�g�i��{�I�ɃQ�[���}�l�[�W���[�j
	SceneManager(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	////�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
	////�����Fnext	���̃V�[����ID
	void ChangeScene(SCENE_ID next);


#if 0
#endif
	//--------------�X�e�[�W�N���A�����[�h���ʂ̃X�e�[�W�Ɉړ�����Ȃ�g����������Ȃ��֐�------------------
	/// <summary>
	/// �N���A�����񐔂𑝂₷�iplayer.cpp�ł����g��Ȃ��j
	/// </summary>
	void ClearCountPlus() { ClearCount_ += 100; }

	/// <summary>
	/// �N���A�����񐔂��Q�b�g
	/// </summary>
	/// <returns></returns>
	int GetClearCount() { return ClearCount_; }

	/// <summary>
	/// �N���A�������ǂ����Q�b�g clearcount��200�ȏ�Ȃ�N���A�͂�Ă�
	/// </summary>
	/// <returns></returns>
	bool GetClear() { return isGameClear_; }
	//--------------�X�e�[�W�N���A�����[�h���ʂ̃X�e�[�W�Ɉړ�����Ȃ�g����������Ȃ��֐�------------------
     
	/// <summary>
	/// MP�̕ϐ����Z�b�g
	/// </summary>
	/// <param name="mp">MP�l</param>
	void SetMagicPoint(int mp) { MpReceive_ = mp; }

	/// <summary>
	/// MP�̒l���擾����
	/// </summary>
	/// <returns></returns>
	int GetMagicPoint()const { return MpReceive_; }

	




private:
	SCENE_ID currentSceneID_;	
	SCENE_ID nextSceneID_;	

	/// <summary>
	/// �N���A������
	/// </summary>
	int ClearCount_;
	bool isGameClear_;

	int MpReceive_;//����Ă���MP��ۑ�(�i�[)����ϐ�
};