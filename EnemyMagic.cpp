#include "EnemyMagic.h"
#include <assert.h>
#include "Camera.h"
#include "Player.h"

EnemyMagic::EnemyMagic(GameObject* scene) : GameObject(scene)
{
	hImage_ = LoadGraph("Assets/EnemyMagic_F.png");
	assert(hImage_ > 0);
	transform_.scale_.x = -2.0f;
	transform_.scale_.y = -2.0f;
}

EnemyMagic::~EnemyMagic()
{

	if (hImage_ > 0)
	{
		DeleteGraph(hImage_);
	}
}

void EnemyMagic::Update()
{
	if (++flameCounter_ >= 24)
	{
		animeFrame_ = (animeFrame_ + 1) % 4;//if•¶‚ğg‚í‚È‚¢Å“K‰ğ
		flameCounter_ = 0;
	}

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

void EnemyMagic::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}
	int spriteWidth = 64;
	int spriteHeight = 70;

	int frameX = animeFrame_ % 3; // ‰¡‚É3‚Â‚Ì‰æ‘œ‚ª‚ ‚é‚½‚ß

	DrawRectGraph(x, y, frameX * spriteWidth, 0, spriteWidth, spriteHeight, hImage_, TRUE);

	//DrawCircle(x + spriteWidth / 2, y + spriteHeight / 2, 16.0f, GetColor(255, 0, 0), 0);
	DrawGraph(x, y, hImage_, TRUE);
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
}

bool EnemyMagic::ColliderCircle(float x, float y, float r)
{
	//x,y,r‚ª‘Šè‚Ì‰~‚Ìî•ñ
	//©•ª‚Ì‰~‚Ìî•ñ
	float myCenterX = transform_.position_.x + 32.0f;
	float myCenterY = transform_.position_.y + 32.0f;
	float myR = 24.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if (sqrt(dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}
