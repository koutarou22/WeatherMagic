#include "Magic.h"
#include <assert.h>
#include "Camera.h"
#include "Ghost.h"
#include"Field.h"
#include "Debug.h"

Magic::Magic(GameObject* scene) : GameObject(scene),Magic_s(S_Move),animeNum(0),
direction_({0,0}),frameCounter(0),speed_(0.0f),timer_(0)
{
	Debug::OutPrint(L"魔法を撃った(プレイヤー)", true);

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

	Magic_s = S_Max;
	isDraw_ = false;
}

Magic::~Magic()
{
	//Release();
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
		if (direction_.x == -1.0f)//左向きなら反転描画
		{
			if (isDraw_) {
			DrawTurnGraph(x, y, animeArray_[animeNum], TRUE);
			}
		}
		else
		{
			if (isDraw_) {
				DrawGraph(x, y, animeArray_[animeNum], TRUE);
			}
		}
		break;
	}
	case Magic::S_Hit:
	{
		if (isDraw_) {
			DrawGraph(x, y, animeHitArray_[animeNum], TRUE);
		}
		break;
	}
	default:
		break;
	}

	//DrawCircle(x + 16, y + 16, 16, GetColor(255, 0, 0), FALSE);
}

void Magic::UpdateIdle()
{
}

void Magic::UpdateMove()
{
	Field* pField = GetParent()->FindGameObject<Field>();
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		if (isDraw_) {
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
				isDraw_ = false;
				transform_.position_.x = -1;
				transform_.position_.y = -1;
			}
		}
	}

	//---------------衝突判定--------------------------------
	if (pField != nullptr)
	{
		if (isDraw_) {
			if (direction_.x == 1.0)
			{
				if (pField->IsWallBlock(transform_.position_.x + 32, transform_.position_.y) ||
					pField->IsHitRock(transform_.position_.x + 32, transform_.position_.y))
				{
					Magic_s = S_Hit;
				}
			}
			else
			{
				if (pField->IsWallBlock(transform_.position_.x, transform_.position_.y) ||
					pField->IsHitRock(transform_.position_.x - 32, transform_.position_.y))
				{
					Magic_s = S_Hit;
				}
			}
		}
	}
}

void Magic::UpdateHit()
{
	if (isDraw_) 
	{
		if (++frameCounter >= 2)
		{
			animeNum = (animeNum + 1) % 7;
			frameCounter = 0;
		}

		if (animeNum >= 6)
		{
			isDraw_ = false;
			animeNum = 0;
			transform_.position_.x = -1;
			transform_.position_.y = -1;
		}
	}
}

void Magic::SetPosition(int x, int y)
{
	transform_.position_.x = x + 20;
	transform_.position_.y = y + 30;
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
	//x,y,rが相手の円の情報
		//自分の円の情報
	float myCenterX = transform_.position_.x + 16.0f;
	float myCenterY = transform_.position_.y + 16.0f;
	float myR = 16.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if (sqrt(dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}

void Magic::Release()
{
	Debug::OutPrint(L"魔法を解放(プレイヤー)", true);

	if (hImage_move1 > 0)
	{
		DeleteGraph(hImage_move1);
	}
	if (hImage_move2 > 0)
	{
		DeleteGraph(hImage_move2);
	}
	if (hImage_move3 > 0)
	{
		DeleteGraph(hImage_move3);
	}
	if (hImage_move4 > 0)
	{
		DeleteGraph(hImage_move4);
	}

	if (hImage_hit1 > 0)
	{
		DeleteGraph(hImage_hit1);
	}
	if (hImage_hit2 > 0)
	{
		DeleteGraph(hImage_hit2);
	}
	if (hImage_hit3 > 0)
	{
		DeleteGraph(hImage_hit3);
	}
	if (hImage_hit4 > 0)
	{
		DeleteGraph(hImage_hit4);
	}
	if (hImage_hit5 > 0)
	{
		DeleteGraph(hImage_hit5);
	}
	if (hImage_hit6 > 0)
	{
		DeleteGraph(hImage_hit6);
	}
	if (hImage_hit7 > 0)
	{
		DeleteGraph(hImage_hit7);
	}
}
