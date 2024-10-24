#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// Mp�̒l��]�����������ĕ\������(������)
/// </summary>
class Score : public GameObject
{
private:
	int hImage_;

	int NumStars = 0;
	//int animeType_;//��
	//int animeFrame_;//��
	//int PictFlame_;
	//int flameCounter_;
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
};

