#include "HealItem.h"
#include "Camera.h"


HealItem::HealItem(GameObject* parent) :GameObject(parent, "HpItem"), hImage_(-1)
{
	hImage_ = LoadGraph("Assets/HpItem.png");
	assert(hImage_ >= 0);
}

HealItem::~HealItem()
{
	if (hImage_ > 0)
	{
		DeleteGraph(hImage_);
	}
}

void HealItem::Initialize()
{
}

void HealItem::Update()
{
	////Instantiate<Heallten>(this);
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

void HealItem::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

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
	//x,y,r‚ª‘Šè‚Ì‰~‚Ìî•ñ
	//©•ª‚Ì‰~‚Ìî•ñ
	float myCenterX = transform_.position_.x + 32.0f;
	float myCenterY = transform_.position_.y + 32.0f;
	float myR = 30.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if (sqrt(dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}