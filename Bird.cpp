#include "Bird.h"
#include <assert.h>
#include "Camera.h"

namespace
{
	static const int SCREEN_WIDTH = 1280;
}
Bird::Bird(GameObject* scene)
{
	hImage = LoadGraph("Assets/bird.png");
	assert(hImage > 0);
	transform_.position_.x = 800.0f;
	transform_.position_.y = 580.0f;
}

Bird::~Bird()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Bird::Update()
{
	int x = (int)transform_.position_.x;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		x -= cam->GetValue();
	}
	if (x > SCREEN_WIDTH)
	{
		return;
	}
	else if (x < -64)
	{
		KillMe();
		return;
	}
	transform_.position_.x -= 1.0f;
	float sinAngle = 0;
	sinAngle += 3.0;
	float sinValue;
	sinValue = sinf(sinAngle * DX_PI_F / 180.0f);
	transform_.position_.y = sinValue * 50.0f;
}

void Bird::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	DrawRectGraph(x, y, 0, 0, 64, 64, hImage, TRUE);
}

void Bird::SetPosition(int x, int y)
{
}
