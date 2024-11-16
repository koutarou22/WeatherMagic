#include "Logo.h"

Logo::Logo(GameObject* parent)
	:GameObject(parent,"Logo"),hImage_(-1)
{
	transform_.position_.x = 390;
	transform_.position_.y = 360;
}

Logo::~Logo()
{
	if (hImage_ > 0)
	{
		DeleteGraph(hImage_);
	}
}

void Logo::Initialize()
{
	hImage_ = LoadGraph("Assets/UI/gameclear.png");
	assert(hImage_ > 0);

}

void Logo::Update()
{
	//transform_.position_.x -= 1.0f;
	
}

void Logo::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	DrawGraph(x, y, hImage_, TRUE);
}

void Logo::Release()
{
}
