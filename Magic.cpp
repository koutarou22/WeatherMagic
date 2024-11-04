#include "Magic.h"
#include <assert.h>
#include "Camera.h"
#include "Player.h"
#include "Ghost.h"

Magic::Magic(GameObject* scene) : GameObject(scene)
{
	hImage_ = LoadGraph("Assets/Bullet/Magic_F.png");
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
	DrawCircle(x + 16, y + 16, 16, GetColor(255, 0, 0), FALSE);
}

void Magic::SetPosition(int x, int y)
{
	transform_.position_.x = x + 20;
	transform_.position_.y = y + 10;
	timer_ = 90;
}

void Magic::SetPosition(XMFLOAT3 pos)
{
	pos.y += 10; 
	transform_.position_ = pos;
	timer_ = 90;
}

bool Magic::ColliderCircle(float x, float y, float r)
{
	//x,y,r‚ª‘Šè‚Ì‰~‚Ìî•ñ
		//©•ª‚Ì‰~‚Ìî•ñ
	float myCenterX = transform_.position_.x + 16.0f;
	float myCenterY = transform_.position_.y + 16.0f;
	float myR = 16.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if (sqrt(dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}
