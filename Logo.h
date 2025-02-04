#pragma once
#include "Engine/GameObject.h"
class Logo :
    public GameObject
{
private:
	int hClear_;
	float MoveValueX;//�C�[�W���O�֐��p�̒l
	float frame;//�t���[��������
public:
    Logo(GameObject* parent);
	~Logo();
	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;
	//�J��
	void Release() override;

	/// <summary>
	/// �}�������ċ}��������C�[�W���O�֐�(start����end�܂�)
	/// </summary>
	/// <param name="time">1~0�܂Ő؂�ւ��</param>
	/// <param name="start">�����l</param>
	/// <param name="end">�ő�l�@�����܂ŗ�����return </param>
	/// <returns></returns>
	float easeOutExpo(float time, float start, float end);

	/// <summary>
	/// �}�������ċ}��������C�[�W���O�֐��i0����1�܂Łj
	/// </summary>
	/// <param name="time">1~0�܂Ő؂�ւ��</param>
	/// <returns></returns>
	float easeOutExpo(float time);
};

