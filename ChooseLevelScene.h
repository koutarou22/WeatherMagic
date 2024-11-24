#pragma once
#include "Engine/GameObject.h"
#include<array>
#include<vector>

using std::array;

class ChooseLevelScene :
    public GameObject
{
private:
	int hImage_back;//�w�i
	int	hLevelFont;//�w��Փx��I�����Ă��������x�̃t�H���g
	int hDecideB;   //����UI

	int padAnalogInput;//xbox�̓��͂��󂯎��
	XINPUT_STATE input;//xbox�̓��͂��󂯎��

	int keyTimer_; //�L�[��������Ă���J�ڂ܂ł̃^�C�}�[
	bool keyPushed_; //�L�[�������ꂽ��(�Ó]OK��)�̃t���O

	const char* LevelText1 = "";
	const char* LevelText2 = "";
	const char* LevelText3 = "";
	const char* Explanation1 = "";
	const char* Explanation2 = "";
	const char* Explanation3 = "";

	array <const char*, 3> LevelMassage = { LevelText1,LevelText2,LevelText3 };//�g��Ȃ�����
	array <const char*, 3> ExplanationMassage = { Explanation1,Explanation2,Explanation3 };//�g��Ȃ�����

	enum StageLevelChoose
	{
		EASY = 0,
		NORMAL = 1,
		HARD = 2,
	};

	StageLevelChoose chooselevel_;
	std::vector<StageLevelChoose> level_arr;
	int currentlevel = 0;//��Փx�i�I���ɂ���ēǂ݂���csv��ς���j
	bool prevUp;//������������
	bool prevDown;//������������

	int Previous(int level);// �O�̗v�f�ɃA�N�Z�X�i�z�I�j
	int Next(int currentIndex);// ���̗v�f�ɃA�N�Z�X�i�z�I�j

	int whitecolor = GetColor(255, 255, 255);
	int yellowcolor = GetColor(255, 255, 0);


	int SelectSEHandle;//�I��pSE
	int DecisionHandle;//����pSE

	bool CheckDecision;//���肪�����ꂽ���m�F����p

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ChooseLevelScene(GameObject* parent);
	~ChooseLevelScene();

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	/*void SetLevel(int level) { Level_ = level; }
	int GetLevel() { return Level_; }*/
};

