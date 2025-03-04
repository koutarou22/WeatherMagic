#include "HealItem.h"
#include "Camera.h"
#include "Player.h"
#include "Field.h"


HealItem::HealItem(GameObject* parent) :GameObject(parent, "HpItem"), hHealItem_(-1)
{
	hHealItem_ = LoadGraph("Assets/Item/PotionRed1.png");//回復アイテムのImage
	assert(hHealItem_ >= 0);

	hHealIEffect_ = LoadGraph("Assets/Item/right.png");
	assert(hHealIEffect_ > 0);

	FrameCounter_ = 0;
	animeType_ = 0;
	animeFrame_ = 0;
}

HealItem::~HealItem()
{
	Release();
}

void HealItem::Initialize()
{
}

void HealItem::Update()
{
	if (++FrameCounter_ >= 24)
	{
		animeFrame_ = (animeFrame_ + 1) % 4;
		FrameCounter_ = 0;
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
	DrawRectGraph(x, y, frameX * SWidth, 0, SWidth, SHeight, hHealIEffect_, TRUE);
	DrawGraph(x, y, hHealItem_, TRUE);
}

void HealItem::Release()
{
	if (hHealItem_ > 0)
	{
		DeleteGraph(hHealItem_);
	}
	if (hHealIEffect_ > 0)
	{
		DeleteGraph(hHealIEffect_);
	}
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