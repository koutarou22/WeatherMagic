#include "Ghost.h"
#include <assert.h>
#include "Camera.h"
#include "EnemyMagic.h"
#include "Magic.h"
#include "Damage.h"
#include "Weather.h"
#include "FreezeEffect.h"
#include "Debug.h"
#include "Engine/Global.h"

namespace
{
	static const int SCREEN_WIDTH = 1280;
	const VECTOR dir = { -1.0f,0.0f };//敵の弾の発射方向
}

Ghost::Ghost(GameObject* parent)
	:GameObject(parent),hGhost_(-1),AnimeType_(0),AnimeFrame_(0),PictFlame_(0),FlameCounter_(0)
{
	hGhost_ = LoadGraph("Assets/Chara/obake.png");
	assert(hGhost_ > 0);

	transform_.scale_ = { 2.0f,2.0f,0 };

	//ダメージ音
	GhostDamageHandle = LoadSoundMem("Assets/Music/SE/Ghost/GhostVanishing.mp3");
	assert(GhostDamageHandle != -1);

	//攻撃音
	GhostAttackHandle = LoadSoundMem("Assets/Music/SE/Ghost/GhostAttack.mp3");
	assert(GhostAttackHandle != -1);

	EnemyHandle_ = -1;
	pFreeze = nullptr;

	emg = nullptr;

	CoolDownAttack_ = 0;
}

Ghost::~Ghost()
{
}

void Ghost::Update()
{
	Camera* cam = GetParent()->FindGameObject<Camera>();
	EnemyMagic* pEnemyMagic = GetParent()->FindGameObject<EnemyMagic>();

	//アニメーションの処理
	if (++FlameCounter_ >= 24)
	{
		AnimeFrame_ = (AnimeFrame_ + 1) % 4;
		FlameCounter_ = 0;
	}

	if (cam != nullptr)
	{
		int camX = cam->GetValue();
		//画面外なら動かせない処理
		if (transform_.position_.x >= camX && transform_.position_.x <= camX + SCREEN_WIDTH)
		{
			GhostAttack();
			GhostMove();
		}
	}

	CheckHitMagic();
}

void Ghost::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		x -= cam->GetValue();
	}

	//画像サイズを格納
	int spriteWidth = 256 / 3;
	int spriteHeight = 341 / 4;

	//アニメーションを動かす
	int frameX = AnimeFrame_ % 3;

	DrawRectGraph(x, y, frameX * spriteWidth, 0, spriteWidth, spriteHeight, hGhost_, TRUE);
}

void Ghost::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

bool Ghost::ColliderCircle(float x, float y, float r)
{
	float myCenterX = transform_.position_.x + 32.0f;
	float myCenterY = transform_.position_.y + 32.0f;
	float myR = 30.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if (sqrt(dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}

void Ghost::Release()
{
	emg = nullptr;
	if (hGhost_ > 0)
	{
		DeleteGraph(hGhost_);
	}
}

void Ghost::GhostAttack()
{
	Weather* pWeather = GetParent()->FindGameObject<Weather>();
	if (pWeather != nullptr && pWeather->GetWeatherState() != WeatherState::Snow)
	{
		if (CoolDownAttack_ <= 0)
		{
			PlaySoundMem(GhostAttackHandle, DX_PLAYTYPE_BACK);

			if (emg == nullptr)
			{
				emg = Instantiate<EnemyMagic>(GetParent());
			}
			if (EnemyHandle_ < 0)
			{
				emg->LoadMagicImage();
				EnemyHandle_ = emg->GetImageHandle();
				//Debug::OutPrint(L"イメージロード", true);
			}

			if (emg != nullptr)
			{
				emg->SetPosition(transform_.position_);
				VECTOR dir = { -1.0f,0.0f };
				emg->SetDirection(dir);
				emg->SetSpeed(3.5f);
			}

			CoolDownAttack_ = 300;
		}
	}


	if (CoolDownAttack_ > 0)
	{
		CoolDownAttack_--;
	}

}

void Ghost::GhostMove()
{
	Weather* pWeather = GetParent()->FindGameObject<Weather>();
	if (pWeather != nullptr && pWeather->GetWeatherState() != WeatherState::Snow)
	{
		SinAngle_ += 3.0f;
		float sinValue = sinf(SinAngle_ * DX_PI_F / 180.0f);
		transform_.position_.y += sinValue * 3.0f;

		//	雪以外で、pFreezeのポインタが生きているなら削除
		if (pFreeze != nullptr)
		{
			pFreeze = nullptr;
		}

	}
	if (pWeather != nullptr && pWeather->GetWeatherState() == WeatherState::Snow)
	{
		if (pFreeze == nullptr)
		{
			pFreeze = Instantiate<FreezeEffect>(GetParent());
			pFreeze->SetPosition(transform_.position_.x, transform_.position_.y);
		}
	}
}

void Ghost::CheckHitMagic()
{
	std::list<Magic*> pMagics = GetParent()->FindGameObjects<Magic>();
	for (Magic* pMagic : pMagics)
	{
		float dx = pMagic->GetPosition().x - (transform_.position_.x + 16.0f);
		float dy = pMagic->GetPosition().y - (transform_.position_.y + 16.0f);
		float distance = sqrt(dx * dx + dy * dy);

		if (distance <= 45.0f)
		{
			PlaySoundMem(GhostDamageHandle, DX_PLAYTYPE_BACK);
			pMagic->SetMagicStateHit();
			KillMe();
			break;
		}

	}
}
