#include "Magic.h"
#include <assert.h>
#include "Camera.h"
#include "Player.h"

Magic::Magic(GameObject* scene) : GameObject(scene)
{
	hImage_ = LoadGraph("Assets/Magic_F.png");
	assert(hImage_ > 0);
}

Magic::~Magic()
{

	if (hImage_ > 0)
	{
		DeleteGraph(hImage_);
	}
}

void Magic::Update()
{
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		transform_.position_.x += direction_.x * speed_;
		transform_.position_.y += direction_.y * speed_;

		if (--timer_ <= 0)
		{
			KillMe();
		}
	}
	
}

void Magic::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	DrawGraph(x, y, hImage_, TRUE);
}

void Magic::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
	timer_ = 90;
}

void Magic::SetPosition(XMFLOAT3 pos)
{
	transform_.position_ = pos;
	timer_ = 90;
}
