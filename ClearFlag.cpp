#include "ClearFlag.h"
#include "Camera.h"
#include "Player.h"
#include "Field.h"


ClearFlag::ClearFlag(GameObject* parent) :GameObject(parent, "ClearFlag"), hImage_(-1),IsClear_(false)
{
	hImage_ = LoadGraph("Assets/Item/GoalFlag.png");
	assert(hImage_ >= 0);

	hEffect_ = LoadGraph("Assets/Item/right.png");
	assert(hEffect_ > 0);
	flameCounter_ = 0;
	animeType_ = 0;
	animeFrame_ = 0;
}

ClearFlag::~ClearFlag()
{
	Release();
}

void ClearFlag::Initialize()
{
}

void ClearFlag::Update()
{
	if (++flameCounter_ >= 24)
	{
		animeFrame_ = (animeFrame_ + 1) % 3;
		flameCounter_ = 0;
	}
}

void ClearFlag::Draw()
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
	
	if (!IsClear_)
	{
		DrawGraph(x, y, hImage_, TRUE);
		DrawRectGraph(x, y, frameX * SWidth, 0, SWidth, SHeight, hEffect_, TRUE);
	}
	//DrawCircle(x + 63.0f, y + 63.0f, 24.0f, GetColor(255, 0, 0), 0);
}

void ClearFlag::Release()
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

void ClearFlag::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

void ClearFlag::SetPosition(XMFLOAT3 pos)
{
	transform_.position_ = pos;
}

bool ClearFlag::ColliderCircle(float x, float y, float r)
{
	//x,y,r‚ª‘Šè‚Ì‰~‚Ìî•ñ
	//©•ª‚Ì‰~‚Ìî•ñ
	float myCenterX = transform_.position_.x + 32.0f;
	float myCenterY = transform_.position_.y + 32.0f;
	float myR = 20.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if (sqrt(dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}