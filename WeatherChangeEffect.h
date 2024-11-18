#pragma once
#include "Engine/GameObject.h"
class WeatherChangeEffect :
    public GameObject
{
private:
    int hImage_;
	int animeFrame;
	int FrameCounter;
	int eraseCounter;


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

