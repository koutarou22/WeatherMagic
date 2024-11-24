#include "Logo.h"
#include<cmath>

namespace
{
	const float width = 390.0f;
	const float height = 360.0f;
	const float start = 0.0f;
}

Logo::Logo(GameObject* parent)
	:GameObject(parent,"Logo"),hImage_(-1),MoveValueX(0.0f),frame(0.0f)
{
	transform_.position_.x = 0;
	transform_.position_.y = height;
}

Logo::~Logo()
{
	Release();
}

void Logo::Initialize()
{
	hImage_ = LoadGraph("Assets/UI/gameclear.png"); 
	//hImage_ = LoadGraph("Assets/Font/StageClear.png");
	assert(hImage_ > 0);

}

void Logo::Update()
{
	MoveValueX = easeOutExpo(frame, start, width);
	transform_.position_.x = MoveValueX;
	frame += 1.0f / 60.0f;
}

void Logo::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	DrawGraph(x, y, hImage_, TRUE);
	//DrawFormatString(0, 400, GetColor(0, 0, 0), "イージングの数値: %d ", MoveValueX);
}

void Logo::Release()
{
	if (hImage_ > 0)
	{
		DeleteGraph(hImage_);
	}
}

float Logo::easeOutExpo(float time, float start, float end)
{
	if (time >= 1.0f)
	{
		return end;
	}
	return start + (end - start) * (1 - std::pow(2, -10 * time));
}

float Logo::easeOutExpo(float time)
{
	if (time >= 1.0f)
	{
		return 1.0f;
	}
	return 1 - std::pow(2, -10 * time);

}
