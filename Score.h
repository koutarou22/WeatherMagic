#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// Mp�̒l��]�����������ĕ\������
/// </summary>
class Score : public GameObject
{
private:
	int hStar_;

	int NumStars = 0;

	float StarMoveX;//�C�[�W���O�֐��p�̒l
	float MessageMoveX;//�C�[�W���O�֐��p�̒l
	float frame_Star;//�t���[��������(���p)
	float frame_Message;//�t���[��������(���b�Z�[�W�p)
	bool IsStarMoveEnd;//���̓������I�������
	bool isPlaying; //���v���C�V�[���ł���

public:

	Score(GameObject* parent);
	~Score();
	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;
	//�J��
	void Release() override;
	void SetPosition(int x, int y);
	void SetPosition(XMFLOAT3 pos);

	//�}�������ċ}��������
	float easeOutQuart(float time);
	//�v���C�V�[�����ǂ������Z�b�g(�v���C�V�[���ł̐��̕\���p)
	void SetPlaying(bool playing) { isPlaying = playing; }
};

