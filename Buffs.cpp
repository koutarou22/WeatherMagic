#include "Buffs.h"
#include "Camera.h"

Buffs::Buffs(GameObject* parent) :GameObject(parent, "Buffs"), hImage_(-1)
{
	hImage_ = LoadGraph("Assets/Buffs.png");
	assert(hImage_ >= 0);
}

Buffs::~Buffs()
{
	if (hImage_ > 0)
	{
		DeleteGraph(hImage_);
	}
}

void Buffs::Initialize()
{
}

void Buffs::Update()
{
	if (++flameCounter_ >= 24)
	{
		animeFrame_ = (animeFrame_ + 1) % 10;
		flameCounter_ = 0;
	}

	////Instantiate<Buffs>(this);
	//if (Timer_ <= 0)
	//{
	//	KillMe();
	//	Timer_ = 180;
	//}

	//if (Timer_ > 0)
	//{
	//	Timer_--;
	//}

}

void Buffs::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	int SWidth = 512 / 10;
	int SHeight = 51;

	int frameX = animeFrame_ % 10;

	// スプライトを描画
	DrawRectGraph(x, y, frameX * SWidth, 0, SWidth, SHeight, hImage_, TRUE);
}

void Buffs::Release()
{
}

void Buffs::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

void Buffs::SetPosition(XMFLOAT3 pos)
{
	transform_.position_ = pos;
}