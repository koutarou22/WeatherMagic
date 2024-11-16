#include "WeatherBackGround.h"
#include "Camera.h"

WeatherBackGround::WeatherBackGround(GameObject* parent)
	:GameObject(parent, "WeatherBackGround"), hImage_Sun(-1), hImage_Rain(-1), hImage_Gale(-1),hImage_Snow(-1),animeFrame(0), FrameCounter(0), eraseCounter(0)
{
	/*hImage_Sun = LoadGraph("");
	assert(hImage_Sun > 0);*/
	hImage_Rain = LoadGraph("Assets/UI/Rainanimation.png");
	assert(hImage_Rain > 0);
	//hImage_Gale = LoadGraph("");
	//assert(hImage_Gale > 0);
	//hImage_Snow = LoadGraph("");
	//assert(hImage_Snow);
}

WeatherBackGround::~WeatherBackGround()
{
	if (hImage_Sun > 0)
	{
		DeleteGraph(hImage_Sun);
	}
	if (hImage_Rain > 0)
	{
		DeleteGraph(hImage_Rain);
	}
	if (hImage_Gale > 0)
	{
		DeleteGraph(hImage_Gale);
	}
	if (hImage_Snow > 0)
	{
		DeleteGraph(hImage_Snow);
	}
}

void WeatherBackGround::Update()
{
	if (++FrameCounter >= 2)
	{
		animeFrame = (animeFrame + 1) % 2;
		FrameCounter = 0;
	}
}

void WeatherBackGround::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) 
	{
		x -= cam->GetValue();
	}

	DrawRectGraph(x, y, animeFrame * 64, 0, 64, 64, hImage_Rain, TRUE);
}

void WeatherBackGround::Release()
{
}
