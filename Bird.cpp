#include "Bird.h"
#include <assert.h>

Bird::Bird(GameObject* scene)
{
	hImage = LoadGraph("Assets/mob.png");
	assert(hImage > 0);
	transform_.position_.x = 800.0f;
	transform_.position_.y = 500.0f;
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
}

void Bird::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	DrawRectGraph(x, y, 0, 0, 64, 64, hImage, TRUE);
}
