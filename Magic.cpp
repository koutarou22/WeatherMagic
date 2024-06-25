#include "Magic.h"
#include <assert.h>

Magic::Magic(GameObject* scene) : GameObject(scene)
{
	hImage = LoadGraph("Assets/Magic.png");
	assert(hImage > 0);
}

Magic::~Magic()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Magic::Update()
{
	transform_.position_.x += 1.0;
	if (--timer <= 0)
	{
		KillMe();
	}
}

void Magic::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	DrawGraph(x, y, hImage, TRUE);
}

void Magic::SetPosition(XMFLOAT3 pos)
{
	transform_.position_ = pos;
	timer = 90;
}
