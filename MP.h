#pragma once
#include "Engine/GameObject.h"
#include"Engine/Transform.h"
/// <summary>
/// MP��UI
/// </summary>
class MP :
    public GameObject
{
	int hMPBar_;//�Q�[�W�̉摜�n���h��
	int hMPFrame_;//�t���[���̉摜�n���h��
	int MPgaugeMaxVal_;//�Q�[�W�̍ő�l
	int MPgaugeCrrVal_;//�J�����g�̒l�i���݂̒l�j crrunt value
	Transform trs;
public:
	MP(GameObject* parent);
	~MP();
	
	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetGaugeVal(int _crr, int _max)
	{
		MPgaugeCrrVal_ = _crr;
		MPgaugeMaxVal_ = _max;
	}
};

