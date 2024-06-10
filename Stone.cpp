#include "Stone.h"
#include <assert.h>

Stone::Stone(GameObject* scene) : GameObject(scene)
{
	hImage = LoadGraph("Assets/stone.png");
	assert(hImage > 0);
}

Stone::~Stone()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Stone::Update()
{
	if (--timer <= 0)
	{
		KillMe();
	}
}

void Stone::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	DrawGraph(x, y, hImage, TRUE);
}

void Stone::SetPosition(XMFLOAT3 pos)
{
	transform_.position_ = pos;
	timer = 90;
}
