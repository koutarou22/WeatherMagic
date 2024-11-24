#include "Damage.h"
#include "Camera.h"

Damage::Damage(GameObject* parent) :GameObject(parent, "Damage"), hImage_(-1), Timer_(90)
{
	hImage_ = LoadGraph("Assets/Chara/Confusion2.png");
	assert(hImage_ >= 0);
}

Damage::~Damage()
{
	Release();
}

void Damage::Initialize()
{
}

void Damage::Update()
{
	//Instantiate<Damage>(this);
	if (Timer_ <= 0)
	{
		KillMe();
		Timer_ = 540;
	}

	if (Timer_ > 0)
	{
		Timer_--;
	}
}

void Damage::Draw()
{
	int x = (int)transform_.position_.x+10;
	int y = (int)transform_.position_.y-20;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	DrawGraph(x, y, hImage_, TRUE);
}

void Damage::Release()
{
	DeleteGraph(hImage_);
}

void Damage::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

void Damage::SetPosition(XMFLOAT3 pos)
{
	transform_.position_ = pos;
}
