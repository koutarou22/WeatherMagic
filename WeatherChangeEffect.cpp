#include "WeatherChangeEffect.h"
#include"Camera.h"
WeatherChangeEffect::WeatherChangeEffect(GameObject* parent)
	:GameObject(parent, "WeatherChangeEffect"), hImage_(-1),animeFrame(0),FrameCounter(0),eraseCounter(0)
{
	hImage_ = LoadGraph("Assets/Effect/WeatherChangeMagic.png");
	assert(hImage_ > 0);
}

WeatherChangeEffect::~WeatherChangeEffect()
{
	if (hImage_ > 0)
	{
		DeleteGraph(hImage_);
	}
}

void WeatherChangeEffect::Update()
{
	if (++FrameCounter >= 3)
	{
		animeFrame = (animeFrame + 1) % 21;
		FrameCounter = 0;
		eraseCounter++;
	}

	if (eraseCounter >= 22)
	{
		KillMe();
	}
}

void WeatherChangeEffect::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	DrawRectGraph(x, y, animeFrame * 64,  0, 64, 64, hImage_, TRUE);
	//DrawFormatString(100,500, GetColor(0, 0, 0), "x: %d y:%d", x,y);
}

void WeatherChangeEffect::Release()
{
}
