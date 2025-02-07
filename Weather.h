#pragma once
#include"Engine/GameObject.h"

/// <summary>
/// �V����̉摜�A���ʂ��Ǘ�����N���X
/// </summary>
enum WeatherState
{
	Sun,//����̓�
	Rain,//�J�̓�
	Gale,//�����̓�
	Snow,//��̓�
};

class Weather:public GameObject
{
public:
	
	Weather(GameObject* parent) : GameObject(parent), weather_(Sun) {};
	~Weather();
	void Initialize() override;
	void Update() override;
    void Draw() override;
	void Release() override;

	void SetPosition(int x, int y);
	void SetWeather(WeatherState _state) { weather_ = _state ; }
	void SetNextWeather(WeatherState _state) { NextWeather_ = _state; }

    /// <summary>
    /// �v���C���[�̈ړ����x�����擾����
    /// </summary>
    /// <returns></returns>
    float GetWeather() { return WeatherChange_; }

	WeatherState GetNextWeather() const { return NextWeather_; } 
	WeatherState GetWeatherState() const { return weather_; }

	/// <summary>
	/// �V���؂�ւ������̃v���C���[�̈ړ����x��ݒ肷��N���X
	/// </summary>
	/// <returns></returns>
	float GetWeatherChange();
	WeatherState weather_;

	int padAnalogInput;//xbox�̓��͂��󂯎��
	XINPUT_STATE input;//xbox�̓��͂��󂯎��
    
private:
	
	WeatherState NextWeather_;

	//�V�󎞂̃G�t�F�N�g��ۑ�����ϐ�
	//0:����
	//1:�J
	//2:��
	//3:��
	int hWeatherEffect_[4];

	//�V�󎞂̃A�C�R���摜��ۑ�����ϐ�
    //0:����
	//1:�J
	//2:��
	//3:��
	int hWeatherIcon_[4];

	//�V�󎞂̓V��̌��ʂ�����p�摜��ۑ�����ϐ�
	//0:����
	//1:�J
	//2:��
	//3:��
	//4:�V��؂�ւ��̊��蓖��
	int hWeatherExplanation_[5];

	
	//�ǂ̓V��ɂȂ��Ă��邩�m�F�p�ϐ�
	bool RainOnChecker, WindOnChecker, SnowOnChecker;

    float WeatherChange_; // �V��ɉ������ړ����x�p���l

	//���ݑ���������o�Ă��邩����p�ϐ�
	bool IsExplanationDisplay_;


	/// <summary>
	/// �����̉�ʂ��o��������ׂ̃L�[�̓��͏������
	/// </summary>
	void ExplanationController();

	/// <summary>
	/// �V�󂪂킩��A�C�R������ʂ̐����A�G�t�F�N�g�̏��
	/// </summary>
	void DrawWeatherUI();
		
};

