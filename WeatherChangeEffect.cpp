#include "WeatherChangeEffect.h"
#include"Camera.h"

namespace
{
	const int IMAGE_SIZE = 64; //�؂蔲����̉摜1�̃T�C�Y
	const int MIN_FRAME_NUM = 3; //�`�悷��t���[����
	const int MAX_FRAME_NUM = 21; //�`�������摜�̔ԍ�(���Ԗڂ�)�̍ő�
}

WeatherChangeEffect::WeatherChangeEffect(GameObject* parent)
	:GameObject(parent, "WeatherChangeEffect")
{
	effImage_ = -1;
	frameCounter_ = -1;
	eraseCounter_ = -1;
	animeFrame_ = -1;
	isDraw_ = false;
}

WeatherChangeEffect::~WeatherChangeEffect()
{
	Release();
}

void WeatherChangeEffect::Initialize()
{

	effImage_ = LoadGraph("Assets/Effect/WeatherChangeMagic.png");
	assert(effImage_ > 0);

	Init();
}

void WeatherChangeEffect::Update()
{
	if (isDraw_)
	{
		//�`��(���Ԃ�	�t���[�����ŊǗ�)
		if (++frameCounter_ >= MIN_FRAME_NUM)
		{
			animeFrame_ = (animeFrame_ + 1) % (MAX_FRAME_NUM);
			frameCounter_ = 0;
			eraseCounter_++;
		}

		//�`��I������E������
		if (eraseCounter_ >MAX_FRAME_NUM)
		{
			Init();
		}
	}
}

void WeatherChangeEffect::Draw()
{
	//�J�������W���Ƃ��Ă��ĕ`��
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}
	if (isDraw_)
	{
		DrawRectGraph(x, y, animeFrame_ * IMAGE_SIZE, 0, IMAGE_SIZE, IMAGE_SIZE, effImage_, TRUE);
	}
}

void WeatherChangeEffect::Release()
{
	if (effImage_ > 0)
	{
		DeleteGraph(effImage_);
	}
}

void WeatherChangeEffect::Init()
{
	frameCounter_ = 0;
	eraseCounter_ = 0;
	animeFrame_ = 0;
	isDraw_ = false;
}
