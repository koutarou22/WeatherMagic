#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// ���n�����Ƃ��ɋN���鍻���I�ȃA��
/// </summary>
class LandingEffect :public GameObject
{
	int hImage_;
	int animeFrame;
	int FrameCounter;
	int eraseCounter;
public:

	LandingEffect(GameObject* parent);
	~LandingEffect();

	//�X�V
	void Update() override;
	//�`��
	void Draw() override;
	//�J��
	void Release() override;

	void SetPosition(int x, int y);
};