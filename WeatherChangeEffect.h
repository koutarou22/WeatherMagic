#pragma once
#include "Engine/GameObject.h"
class WeatherChangeEffect :
    public GameObject
{
private:
    int hImage_;
	int animeFrame;//�X�v���C�g�̂ǂ̃R�}��`�悷�邩
	int FrameCounter;//�X�v���C�g�����̃R�}�ɍs���܂ł̃J�E���^�[
	int eraseCounter;///�X�v���C�g�����̃R�}�ɍs�����瑝�₵�A�A�j���[�V�����I�����������
public:
	WeatherChangeEffect(GameObject* parent);

	~WeatherChangeEffect() ;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;
	//�J��
	void Release() override;
};

