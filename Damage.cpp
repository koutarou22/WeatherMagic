#include "Damage.h"
#include "Camera.h"

Damage::Damage(GameObject* parent) :GameObject(parent, "Damage")
{
	dmgImage_ = -1;
	timer_ = -1;
}

Damage::~Damage()
{
	Release();
}

void Damage::Initialize()
{
	dmgImage_ = LoadGraph("Assets/Chara/Confusion2.png");
	assert(dmgImage_ >0);
	timer_ = TIME;
}

void Damage::Update()
{
	if (timer_ > 0)
	{
		timer_--;
	}
	else
	{
		KillMe();
		timer_ = TIME;
	}
}

void Damage::Draw()
{
	//ƒJƒƒ‰À•W‚ð‚Æ‚Á‚Ä‚«‚Ä•`‰æ
	int x = (int)transform_.position_.x+POS_MARGE.x;
	int y = (int)transform_.position_.y-POS_MARGE.y;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) 
	{
		x -= cam->GetValue();
	}
	DrawGraph(x, y, dmgImage_, TRUE);
}

void Damage::Release()
{
	if (dmgImage_ > 0)
	{
		DeleteGraph(dmgImage_);
		dmgImage_ = -1;
	}
}