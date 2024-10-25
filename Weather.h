#pragma once
#include"Engine/GameObject.h"

/// <summary>
/// �V��𑀍삷��N���X
/// </summary>

enum WeatherState
{
	Sun,//����̓�
	Rain,//�J�̓�
	Gale,//�����̓�(�V�󂩂���...?)
	Snow,//��̓�
};

class Weather:public GameObject
{
public:
	
	Weather(GameObject* parent) : GameObject(parent), weather_(Sun) {}

	void Initialize() override;
	void Update() override;
    void Draw() override;

	void SetPosition(int x, int y);
	void SetWeather(WeatherState _state) { weather_ = _state ; }
	void SetNextWeather(WeatherState _state) { NextWeather_ = _state; }
    float GetWeather() { return WeatherChange_; }

	WeatherState GetNextWeather() const { return NextWeather_; } 
	WeatherState GetWeatherState() const { return weather_; }

	float GetWeatherChange();
	WeatherState weather_;

    
private:
	
	//���������������Ȃ�
	WeatherState NextWeather_;
    int hImage_Sun;//����̃G�t�F�N�g(�w�i)
	int hImage_Rain;//�J�̃G�t�F�N�g(�w�i)
	int hImage_Wind;//���̃G�t�F�N�g(�w�i)
	int hImage_Snow;//��̃G�t�F�N�g(�w�i)


	int Sun_Icon;//����̃A�C�R��
	int Rain_Icon;//�J�̃A�C�R��
	int Gale_Icon;//���̃A�C�R��
	int Snow_Icon;//��̃A�C�R��

	int hImage_RainNoMp;//Mp���g���Ȃ����̍����ւ��p(�J)
	int hImage_WindNoMp;//Mp���g���Ȃ����̍����ւ��p(��)
    int hImage_SnowNoMp;//Mp���g���Ȃ����̍����ւ��p(��)

	int hImage_StateSun;
	int hImage_StateWind;
	int hImage_StateRain;
    int hImage_StateSnow;

	int Weather_ChangeMagic;//�V��ς����Ƃ��̃A�j���[�V����(�܂���`���ĂȂ�)

	bool RainOnChecker;
	bool WindOnChecker;
    bool  SnowOnChecker; 

	int hImage_Book;
    float WeatherChange_; // �V��ɉ������ړ����x�p���l

	int flameCounter_;
	int animeFrame_;

	bool DebugLog_;
		
};

