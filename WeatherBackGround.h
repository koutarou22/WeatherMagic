#pragma once
#include "Engine/GameObject.h"
#include "Weather.h"

/// <summary>
///�@���ꂼ��̓V�󎞂̔w�iAnimation
/// </summary>
class WeatherBackGround :
    public GameObject
{
private:
	int hImage_Sun;
	int hImage_Rain;
	int hImage_Rain2;
	int hImage_Gale;
	int hImage_Snow;

	int animeFrame;//�X�v���C�g�̂ǂ̃R�}��`�悷�邩
	int FrameCounter;//�X�v���C�g�����̃R�}�ɍs���܂ł̃J�E���^�[
	int eraseCounter;///�X�v���C�g�����̃R�}�ɍs�����瑝�₵�A�A�j���[�V�����I�����������

	bool SunNow;//���ꂩ����p
	bool RainNow;//�J������p
	bool GaleNow;//��������p
	bool SnowNow;//�Ⴉ����p


	int padAnalogInput;//xbox�̓��͂��󂯎��
	XINPUT_STATE input;//xbox�̓��͂��󂯎��
public:
	WeatherBackGround(GameObject* parent);

	~WeatherBackGround();
	//�X�V
	void Update() override;

	//�`��
	void Draw() override;
	//�J��
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
	/// �������َ��Ȃ̂ŕ��p��Animation�֐��@�g�����͊F��
	/// </summary>
	/// <param name="flag">�V���Ԃ̃t���O</param>
	/// <param name="alpha">�����x</param>
	/// <param name="hImage">�摜Handle</param>
	/// <param name="Size">�X�v���C�g�̃T�C�YX</param>
	/// <param name="Size">�X�v���C�g�̃T�C�YY</param>
	void GaleAnimation(bool& flag, int alpha, int hImage, int SizeX , int SizeY);
};

