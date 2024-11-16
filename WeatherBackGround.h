#pragma once
#include "Engine/GameObject.h"
#include "Weather.h"
class WeatherBackGround :
    public GameObject
{
private:
	int hImage_Sun;
	int hImage_Rain;
	int hImage_Gale;
	int hImage_Snow;

	int animeFrame;//�X�v���C�g�̂ǂ̃R�}��`�悷�邩
	int FrameCounter;//�X�v���C�g�����̃R�}�ɍs���܂ł̃J�E���^�[
	int eraseCounter;///�X�v���C�g�����̃R�}�ɍs�����瑝�₵�A�A�j���[�V�����I�����������
public:
	WeatherBackGround(GameObject* parent);

	~WeatherBackGround();
	//�X�V
	void Update() override;

	//�`��
	void Draw() override;
	//�J��
	void Release() override;
};

