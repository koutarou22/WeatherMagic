#pragma once
#include "Engine/GameObject.h"
#include<array>
#include<vector>

using std::array;

class ChooseLevelScene :
    public GameObject
{
private:
	int hBack_;//�w�i
	int	hLevelFont_;//�w��Փx��I�����Ă��������x�̃t�H���g
	int hDecideB_;   //����UI
	int hDecideByellow_;//����UI�i���F�j

	int padAnalogInput_;//xbox�̓��͂��󂯎��
	XINPUT_STATE input_;//xbox�̓��͂��󂯎��

	int keyTimer_; //�L�[��������Ă���J�ڂ܂ł̃^�C�}�[
	bool keyPushed_; //�L�[�������ꂽ��(�Ó]OK��)�̃t���O

	const char* LevelText1_ = "";
	const char* LevelText2_ = "";
	const char* LevelText3_ = "";

	enum StageLevelChoose //�e��Փx
	{
		EASY = 0,
		NORMAL = 1,
		HARD = 2,
	};
	//StageLevelChoose chooselevel_;
	std::vector<StageLevelChoose> level_arr_;//��Փx�̔z��

	int currentlevel_;//�I�𒆂̓�Փx(SceneManager�ɒl��n�����A�l�ɂ���ăJ�[�\���̈ʒu���ς��)
	bool prevUp_;//������������
	bool prevDown_;//������������

	int Previous(int level);// �O�̗v�f�ɃA�N�Z�X�i�z�I�j
	int Next(int currentIndex);// ���̗v�f�ɃA�N�Z�X�i�z�I�j

	int whitecolor_ = GetColor(255, 255, 255);
	int yellowcolor_ = GetColor(255, 255, 0);


	int SelectSEHandle_;//�I��pSE
	int DecisionHandle_;//����pSE

	bool CheckDecision_;//���肪�����ꂽ���m�F����p

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
};

