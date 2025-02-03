#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// ��̎��G�������Ă�̂�\������p�̃A��
/// </summary>
class FreezeEffect :
    public GameObject
{
	int hImage_;
	int animeFrame;
	int FrameCounter;
	int eraseCounter;

	bool ReverseFrame;//�t���[���𔻒肳����p�̃t���O

	enum FreezeState {
		S_Freeze,//�����Ă���
		S_MELT,//�����Ă���
		S_NONE//�����Ȃ�
	};
	FreezeState freeze_s;

public:

	FreezeEffect(GameObject* parent);
	~FreezeEffect();

	//�X�V
	void Update() override;
	void UpdateFreeze();
	void UpdateMelt();

	//�`��
	void Draw() override;
	//�J��
	void Release() override;

	void SetPosition(int x, int y);
};

