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

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;
	//ŠJ•ú
	void Release() override;

};

