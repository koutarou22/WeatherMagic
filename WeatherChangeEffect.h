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
	bool isDraw_;//isDraw��true�Ȃ�`��+�X�V

public:
	WeatherChangeEffect(GameObject* parent);

	~WeatherChangeEffect() ;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;
	//�J��
	void Release() override;
	void SetIsDraw(bool _IsDraw) { isDraw_ = _IsDraw; }
	bool GetIsDraw() { return isDraw_; }
};

