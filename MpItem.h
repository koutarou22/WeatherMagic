#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// Mp�񕜃A�C�e���̏��
/// </summary>
class MpItem :public GameObject
{
private:
	int hMpItem_;
	int hMpIEffect_;
	int animeType_;//��
	int animeFrame_;//��
	//int PictFlame_;
	int FrameCounter_;
public:

	MpItem(GameObject* parent);
	~MpItem();
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
	bool Judgement_ = false;
};

