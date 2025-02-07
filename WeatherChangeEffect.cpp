#include "WeatherChangeEffect.h"
#include"Camera.h"

namespace
{
	const int IMAGE_SIZE = 64; //切り抜き後の画像1個のサイズ
	const int MIN_FRAME_NUM = 3; //描画するフレーム数
	const int MAX_FRAME_NUM = 21; //描画をする画像の番号(何番目か)の最大
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
		//描画(時間は	フレーム数で管理)
		if (++frameCounter_ >= MIN_FRAME_NUM)
		{
			animeFrame_ = (animeFrame_ + 1) % (MAX_FRAME_NUM);
			frameCounter_ = 0;
			eraseCounter_++;
		}

		//描画終了判定・初期化
		if (eraseCounter_ >MAX_FRAME_NUM)
		{
			Init();
		}
	}
}

void WeatherChangeEffect::Draw()
{
	//カメラ座標をとってきて描画
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
