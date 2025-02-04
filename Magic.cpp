#include "Magic.h"
#include <assert.h>
#include "Camera.h"
#include "Ghost.h"
#include"Field.h"
#include "Debug.h"

namespace
{
	const int BlockHalf = 32;//ブロック半個分
	const int InitializeTimer = 90;//タイマー初期化時の値
	const int FrameUpdateMove = 8;//アニメーションの切り替えフレーム この値を超えたらスプライト切り替え(移動時)
	const int FrameUpdateHit = 2;//アニメーションの切り替えフレーム この値を超えたらスプライト切り替え(ヒット時)
	const int SpriteNumMove = 4;//アニメーションのスプライトの総数(移動時)
	const int SpriteNumHit = 7;//アニメーションのスプライトの総数(ヒット時)
	const int MagicSetValue = 30;//魔法の射出位置(プレイヤーの位置に加算して調整する)
}

Magic::Magic(GameObject* scene) : GameObject(scene), Magic_s(S_Max), animeNum(0),
direction_({ 0,0 }), frameCounter(0), speed_(0.0f), timer_(0), isDraw_(false)
{
	Debug::OutPrint(L"魔法を撃った(プレイヤー)", true);

	hMagic_Move1 = LoadGraph("Assets/Bullet/bolt/bolt1.png");
	assert(hMagic_Move1 > 0);
	hMagic_Move2 = LoadGraph("Assets/Bullet/bolt/bolt2.png");
	assert(hMagic_Move2 > 0);
	hMagic_Move3 = LoadGraph("Assets/Bullet/bolt/bolt3.png");
	assert(hMagic_Move3 > 0);
	hMagic_Move4 = LoadGraph("Assets/Bullet/bolt/bolt4.png");
	assert(hMagic_Move4 > 0);

	hMagic_Hit1 = LoadGraph("Assets/Bullet/bolt/hit1.png");
	assert(hMagic_Hit1 > 0);
	hMagic_Hit2 = LoadGraph("Assets/Bullet/bolt/hit2.png");
	assert(hMagic_Hit2 > 0);
	hMagic_Hit3 = LoadGraph("Assets/Bullet/bolt/hit3.png");
	assert(hMagic_Hit3 > 0);
	hMagic_Hit4 = LoadGraph("Assets/Bullet/bolt/hit4.png");
	assert(hMagic_Hit4 > 0);
	hMagic_Hit5 = LoadGraph("Assets/Bullet/bolt/hit5.png");
	assert(hMagic_Hit5 > 0);
	hMagic_Hit6 = LoadGraph("Assets/Bullet/bolt/hit6.png");
	assert(hMagic_Hit6 > 0);
	hMagic_Hit7 = LoadGraph("Assets/Bullet/bolt/hit7.png");
	assert(hMagic_Hit7 > 0);

	animeArray_ = { hMagic_Move1, hMagic_Move2,  hMagic_Move3,  hMagic_Move4 };
	animeHitArray_ = { hMagic_Hit1,hMagic_Hit2, hMagic_Hit3, hMagic_Hit4, hMagic_Hit5, hMagic_Hit6, hMagic_Hit7 };
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

			if (++frameCounter >= FrameUpdateMove)
			{
				animeNum = (animeNum + 1) % SpriteNumMove;
				frameCounter = 0;
			}
			if (--timer_ <= 0)
			{
				timer_ = 0;
				isDraw_ = false;
				transform_.position_.x = -1;//位置を画面外に置く
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
				if (pField->IsWallBlock(transform_.position_.x + BlockHalf, transform_.position_.y) ||
					pField->IsHitRock(transform_.position_.x + BlockHalf, transform_.position_.y))
				{
					Magic_s = S_Hit;
				}
			}
			else
			{
				if (pField->IsWallBlock(transform_.position_.x, transform_.position_.y) ||
					pField->IsHitRock(transform_.position_.x - BlockHalf, transform_.position_.y))
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
		if (++frameCounter >= FrameUpdateHit)
		{
			animeNum = (animeNum + 1) % SpriteNumHit;
			frameCounter = 0;
		}

		if (animeNum >= SpriteNumHit - 1)//ヒット時のアニメーションの総数を超えたら(配列確認のため-1)
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
	transform_.position_.x = x + MagicSetValue;
	transform_.position_.y = y + MagicSetValue;
	timer_ = InitializeTimer;
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

	if (hMagic_Move1 > 0)
	{
		DeleteGraph(hMagic_Move1);
	}
	if (hMagic_Move2 > 0)
	{
		DeleteGraph(hMagic_Move2);
	}
	if (hMagic_Move3 > 0)
	{
		DeleteGraph(hMagic_Move3);
	}
	if (hMagic_Move4 > 0)
	{
		DeleteGraph(hMagic_Move4);
	}

	if (hMagic_Hit1 > 0)
	{
		DeleteGraph(hMagic_Hit1);
	}
	if (hMagic_Hit2 > 0)
	{
		DeleteGraph(hMagic_Hit2);
	}
	if (hMagic_Hit3 > 0)
	{
		DeleteGraph(hMagic_Hit3);
	}
	if (hMagic_Hit4 > 0)
	{
		DeleteGraph(hMagic_Hit4);
	}
	if (hMagic_Hit5 > 0)
	{
		DeleteGraph(hMagic_Hit5);
	}
	if (hMagic_Hit6 > 0)
	{
		DeleteGraph(hMagic_Hit6);
	}
	if (hMagic_Hit7 > 0)
	{
		DeleteGraph(hMagic_Hit7);
	}
}
