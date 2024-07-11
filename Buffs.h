#pragma once
#include "Engine/GameObject.h"
class Buffs :public GameObject
{
private:
	int hImage_;

	int animeType_;//��
	int animeFrame_;//��
	int PictFlame_;
	int flameCounter_;

public:

	Buffs(GameObject* parent);
	~Buffs();
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

