#pragma once
#include "Engine/GameObject.h"
#include "Weather.h"

/// <summary>
///�@���ꂼ��̓V�󎞂̔w�iAnimation
/// </summary>

namespace
{
	const int STATE_NUM = 4; //�V��̏��
}
class WeatherBackGround :
    public GameObject
{
	enum WEATHER_STATE
	{
		RAINBACK,RAINFRONT,GALE,SNOW,MAX
	};

	int images_[STATE_NUM];
	bool nowWeather_[STATE_NUM]; //���݂̓V�C����������p

	int animeFrame_;//�X�v���C�g�̂ǂ̃R�}��`�悷�邩
	int frameCounter_;//�X�v���C�g�����̃R�}�ɍs���܂ł̃J�E���^�[
	int eraseCounter_;///�X�v���C�g�����̃R�}�ɍs�����瑝�₵�A�A�j���[�V�����I�����������

	int padAnalogInput;//xbox�̓��͂��󂯎��
	XINPUT_STATE input;//xbox�̓��͂��󂯎��
public:
	WeatherBackGround(GameObject* parent);

	~WeatherBackGround();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	/// <summary>
	/// �V��̏�Ԃ��m�F����p�֐�
	/// </summary>
	/// <param name="state">�V��</param>
	/// <param name="flag">�V���Ԃ̃t���O</param>
	/// <param name="FrameCount">�t���[���̃J�E���g</param>
	/// <param name="Frame">�ő�t���[����</param>
	void WeatherStateConfirm(WeatherState state, bool& flag, int FrameCount, int Frame);


	/// <summary>
	/// �V��̃A�j���[�V������`�悷��֐�
	/// </summary>
	/// <param name="flag">�V���Ԃ̃t���O</param>
	/// <param name="alpha">�����x</param>
	/// <param name="hImage">�摜Handle</param>
	/// <param name="Size">�X�v���C�g�̃T�C�Y</param>
	void WeatherAnimation(bool& flag, int alpha, int hImage , int Size);

	/// <summary>
	/// ���p��Animation�֐�
	/// </summary>
	/// <param name="flag">�V���Ԃ̃t���O</param>
	/// <param name="alpha">�����x</param>
	/// <param name="hImage">�摜Handle</param>
	/// <param name="Size">�X�v���C�g�̃T�C�YX</param>
	/// <param name="Size">�X�v���C�g�̃T�C�YY</param>
	void GaleAnimation(bool& flag, int alpha, int hImage, int SizeX , int SizeY);
};

