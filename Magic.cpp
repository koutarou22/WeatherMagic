#include "Magic.h"
#include <assert.h>
#include "Camera.h"
#include "Player.h"
#include "Ghost.h"

Magic::Magic(GameObject* scene) : GameObject(scene)
{
	hImage_ = LoadGraph("Assets/Bullet/Magic_F.png");
	assert(hImage_ > 0);

	hImage_move1 = LoadGraph("Assets/Bullet/bolt/bolt1.png");
	assert(hImage_move1 > 0);
	hImage_move2 = LoadGraph("Assets/Bullet/bolt/bolt2.png");
	assert(hImage_move2 > 0);
	hImage_move3 = LoadGraph("Assets/Bullet/bolt/bolt3.png");
	assert(hImage_move3 > 0);
	hImage_move4 = LoadGraph("Assets/Bullet/bolt/bolt4.png");
	assert(hImage_move4 > 0);

	hImage_hit1 = LoadGraph("Assets/Bullet/bolt/hit1.png");
	assert(hImage_hit1 > 0);
	hImage_hit2 = LoadGraph("Assets/Bullet/bolt/hit2.png");
	assert(hImage_hit2 > 0);
	hImage_hit3 = LoadGraph("Assets/Bullet/bolt/hit3.png");
	assert(hImage_hit3 > 0);
	hImage_hit4 = LoadGraph("Assets/Bullet/bolt/hit4.png");
	assert(hImage_hit4 > 0);
	hImage_hit5 = LoadGraph("Assets/Bullet/bolt/hit5.png");
	assert(hImage_hit5 > 0);
	hImage_hit6 = LoadGraph("Assets/Bullet/bolt/hit6.png");
	assert(hImage_hit6 > 0);
	hImage_hit7 = LoadGraph("Assets/Bullet/bolt/hit7.png");
	assert(hImage_hit7 > 0);

	animeArray_ = { hImage_move1,hImage_move2, hImage_move3, hImage_move4 };
	animeHitArray_ = { hImage_hit1,hImage_hit2, hImage_hit3, hImage_hit4, hImage_hit5, hImage_hit6, hImage_hit7 };
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

	switch (Magic_s)
	{
	case Magic::S_Move:
		UpdateMove();
		break;
	case Magic::S_Hit:
		UpdateHit();
		break;
	default:
		break;
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

	switch (Magic_s)
	{
	case Magic::S_Move:
	{
		if (direction_.x == -1.0f)
		{
			DrawTurnGraph(x, y, animeArray_[animeNum], TRUE);
		}
		else
		{
			DrawGraph(x, y, animeArray_[animeNum], TRUE);
		}
		break;
	}
	case Magic::S_Hit:
	{
		DrawGraph(x, y, animeHitArray_[animeNum], TRUE);
		break;
	}
	default:
		break;
	}


	/*if (direction_.x == -1.0f)
	{
		DrawTurnGraph(x, y, hImage_, TRUE);
	}
	else
	{
		DrawGraph(x, y, hImage_, TRUE);
	}*/
	//DrawCircle(x + 16, y + 16, 16, GetColor(255, 0, 0), FALSE);
}

void Magic::UpdateMove()
{
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		transform_.position_.x += direction_.x * speed_;
		transform_.position_.y += direction_.y * speed_;


		if (++frameCounter >= 8)
		{
			animeNum = (animeNum + 1) % 4;
			frameCounter = 0;
		}
		if (--timer_ <= 0)
		{
			timer_ = 0;
			KillMe();
		}
	}
}

void Magic::UpdateHit()
{
	if (++frameCounter >= 2)
	{
		animeNum = (animeNum + 1) % 7;
		frameCounter = 0;
	}

	if (animeNum >= 6)
	{
		KillMe();
	}
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
