#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// �G���ƃN���A�ł���I�u�W�F�N�g�̏��(����Ă邱�Ƃ͉񕜃A�C�e���Ƃقړ���)
/// </summary>
class ClearFlag :public GameObject
{
private:
	int hImage_;
	int hImage_Right;

	int animeType_;//��
	int animeFrame_;//��
	int PictFlame_;
	int flameCounter_;
public:

	ClearFlag(GameObject* parent);
	~ClearFlag();
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

