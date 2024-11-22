#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// Hp�񕜃A�C�e���̏��
/// </summary>
class HealItem :public GameObject
{
private:
	int hImage_;
	int hEffect_;
	int animeType_;//��
	int animeFrame_;//��
	int PictFlame_;
	int flameCounter_;
public:

	HealItem(GameObject* parent);
	~HealItem();
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
	bool ColliderCircle(float x, float y, float r);
};

