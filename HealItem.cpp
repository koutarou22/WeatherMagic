#include "HealItem.h"
#include "Camera.h"
#include "Player.h"
#include "Field.h"


HealItem::HealItem(GameObject* parent) :GameObject(parent, "HpItem"), hImage_(-1)
{
	hImage_ = LoadGraph("Assets/Item/PotionRed1.png");//回復アイテムのImage
	assert(hImage_ >= 0);

	hEffect_ = LoadGraph("Assets/Item/right.png");
	assert(hEffect_ > 0);

	flameCounter_ = 0;
	animeType_ = 0;
	animeFrame_ = 0;
}

HealItem::~HealItem()
{
	if (hImage_ > 0)
	{
		DeleteGraph(hImage_);
	}
	if (hEffect_ > 0)
	{
		DeleteGraph(hEffect_);
	}
}

void HealItem::Initialize()
{
}

void HealItem::Update()
{
	if (++flameCounter_ >= 24)
	{
		animeFrame_ = (animeFrame_ + 1) % 4;
		flameCounter_ = 0;
	}
}

void HealItem::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	int SWidth = 192 / 3;
	int SHeight = 64;

	int frameX = animeFrame_ % 3;

	// スプライトを描画
	DrawRectGraph(x, y, frameX * SWidth, 0, SWidth, SHeight, hEffect_, TRUE);
	DrawGraph(x, y, hImage_, TRUE);
}

void HealItem::Release()
{

}

void HealItem::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

void HealItem::SetPosition(XMFLOAT3 pos)
{
	transform_.position_ = pos;
}

bool HealItem::ColliderCircle(float x, float y, float r)
{
	//x,y,rが相手の円の情報
	//自分の円の情報
	float myCenterX = transform_.position_.x + 64.0f;
	float myCenterY = transform_.position_.y + 64.0f;
	float myR = 20.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if (sqrt(dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}