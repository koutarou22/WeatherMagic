#include "MpItem.h"
#include "Camera.h"
#include "Player.h"
#include "Field.h"


MpItem::MpItem(GameObject* parent) :GameObject(parent, "MpItem"), hImage_(-1)
{
	hImage_ = LoadGraph("Assets/Item/PotionBlue1.png");
	assert(hImage_ > 0);

	hEffect_ = LoadGraph("Assets/Item/right.png");
	assert(hEffect_ > 0);

	transform_.position_.x = 200;
	transform_.position_.y = 560;
	flameCounter_ = 0;
	animeType_ = 0;
	animeFrame_ = 0;
}

MpItem::~MpItem()
{
	Release();
}

void MpItem::Initialize()
{
}

void MpItem::Update()
{
	if (++flameCounter_ >= 24)
	{
		animeFrame_ = (animeFrame_ + 1) % 4;
		flameCounter_ = 0;
	}
}

void MpItem::Draw()
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

	// ƒXƒvƒ‰ƒCƒg‚ğ•`‰æ
	DrawRectGraph(x, y, frameX * SWidth, 0, SWidth, SHeight,hEffect_, TRUE);
	DrawGraph(x, y, hImage_, TRUE);
}

void MpItem::Release()
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

void MpItem::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

void MpItem::SetPosition(XMFLOAT3 pos)
{
	transform_.position_ = pos;
}

bool MpItem::ColliderCircle(float x, float y, float r)
{
	//x,y,r‚ª‘Šè‚Ì‰~‚Ìî•ñ
	//©•ª‚Ì‰~‚Ìî•ñ
	float myCenterX = transform_.position_.x + 64.0f;
	float myCenterY = transform_.position_.y + 64.0f;
	float myR = 32.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if (sqrt(dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}
