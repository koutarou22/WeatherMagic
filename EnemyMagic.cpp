#include "EnemyMagic.h"
#include <assert.h>
#include "Camera.h"
#include "Player.h"
#include "Debug.h"
#include "Ghost.h"

EnemyMagic::EnemyMagic(GameObject* scene) : GameObject(scene), hImage_(-1)
{
	timer_ = 0;
	speed_ = 0;
	animeType_ = 0;
	animeFrame_ = 0;
	PictFlame_ = 0;
	flameCounter_ = 0;

	Debug::OutPrint(L"魔法を撃った", true);
	transform_.scale_.x = -2.0f;
	transform_.scale_.y = -2.0f;
	prevPlPosX = -1;
	isDraw = false;
	Ghost*  gh_ = GetParent()->FindGameObject<Ghost>();
	GhostPos_ = gh_->GetPosition();
}

EnemyMagic::~EnemyMagic()
{
	/*Release();*/
}

void EnemyMagic::Update()
{
	if (++flameCounter_ >= 24)
	{
		animeFrame_ = (animeFrame_ + 1) % 4;//if文を使わない最適解
		flameCounter_ = 0;
	}

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		//球が、打った時のプレイヤーの位置より左にいたら、描画しない、座標を戻しておく?

		if (isDraw)
		{
			transform_.position_.x += direction_.x * speed_;
			transform_.position_.y += direction_.y * speed_;
		}
		if (--timer_ <= 0)
		{
			//タイマーが0より小さいとき描画しない、かつ座標をゴーストに
			isDraw = false;
			transform_.position_ = GhostPos_;
			//KillMe();
		}
	}
}

void EnemyMagic::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	int frameX = animeFrame_ % 3; // 横に3つの画像があるため

	//DrawRectGraph(x, y, frameX * spriteWidth, 0, spriteWidth, spriteHeight, hImage_, TRUE);

	//DrawCircle(x + spriteWidth / 2, y + spriteHeight / 2, 16.0f, GetColor(255, 0, 0), 0);
	if (isDraw)
	{
		DrawGraph(x, y, hImage_, TRUE);
	}
}

void EnemyMagic::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
	timer_ = 90;
}

void EnemyMagic::SetPosition(XMFLOAT3 pos)
{
	transform_.position_ = pos;
	timer_ = 90;
	isDraw = true;
}

bool EnemyMagic::ColliderCircle(float x, float y, float r)
{
	//x,y,rが相手の円の情報
	//自分の円の情報
	float myCenterX = transform_.position_.x + 32.0f;
	float myCenterY = transform_.position_.y + 32.0f;
	float myR = 24.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if (sqrt(dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}

void EnemyMagic::LoadMagicImage()
{
	hImage_ = LoadGraph("Assets/Chara/EnemyMagic_F.png");
	assert(hImage_ > 0);
}

void EnemyMagic::Release()
{
	if (hImage_ > 0)
	{
		DeleteGraph(hImage_);
		Debug::OutPrint(L"魔法の解放は正しく呼ばれたEnemyMagic.cpp", true);
		hImage_ = 0;
	}
}
