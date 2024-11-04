#include "Ghost.h"
#include <assert.h>
#include "Camera.h"
#include "EnemyMagic.h"
#include "Magic.h"
#include "Damage.h"
#include "Weather.h"

namespace
{
	static const int SCREEN_WIDTH = 1280;
}

Ghost::Ghost(GameObject* scene)
{
	hImage_ = LoadGraph("Assets/Chara/Ghost.png");
	assert(hImage_ > 0);
	transform_.position_.x = 900.0f;
	transform_.position_.y = 780.0f;
	transform_.scale_.x = 2.0f;
	transform_.scale_.y = 2.0f;

	flameCounter_ = 0;
	animeType_ = 0;
	animeFrame_ = 0;
}

Ghost::~Ghost()
{
	if (hImage_ > 0)
	{
		DeleteGraph(hImage_);
	}
}

void Ghost::Update()
{
	Camera* cam = GetParent()->FindGameObject<Camera>();


	if (++flameCounter_ >= 24)
	{
		animeFrame_ = (animeFrame_ + 1) % 4;//if文を使わない最適解
		flameCounter_ = 0;
	}




	if (cam != nullptr)
	{
		// カメラの位置を取得
		int camX = cam->GetValue();
		if (transform_.position_.x >= camX && transform_.position_.x <= camX + SCREEN_WIDTH)
		{
			if (CoolDownAttack_ <= 0)
			{
				EnemyMagic* emg = Instantiate<EnemyMagic>(GetParent());
				if (emg == nullptr)
				{
					return;
				}
				emg->SetPosition(transform_.position_);
				VECTOR dir = { -1.0f,0.0f };
				emg->SetDirection(dir);
				emg->SetSpeed(3.5f);

				// 天候によって速度を調整
				Weather* pWeather = GetParent()->FindGameObject<Weather>();
				if (pWeather != nullptr && pWeather->GetWeatherState() == WeatherState::Snow)
				{
					emg->SetSpeed(1.0f);
				}
				else
				{
					emg->SetSpeed(3.5f); 
				}

				CoolDownAttack_ = 300;
			}
			//天候取得、雪なら止める
			Weather* pWeather = GetParent()->FindGameObject<Weather>();
			if (pWeather->GetWeatherState() != WeatherState::Snow)
			{
				transform_.position_.y -= 1.0f;
				sinAngle += 3.0f;
				float sinValue = sinf(sinAngle * DX_PI_F / 180.0f);
				transform_.position_.y = sinValue * 50.0f;

				CoolDownAttack_ = 360;
			}
		}
	}

	if (CoolDownAttack_ > 0)
	{
		CoolDownAttack_--;
	}

	int x = (int)transform_.position_.x;


	//if (cam != nullptr)
	//{
	//	x -= cam->GetValue();
	//}
	//if (x > SCREEN_WIDTH)//即値、マジックナンバー
	//	return;
	//else if (x < -64)
	//{
	//	KillMe();
	//	return;
	//}



	std::list<Magic*> pMagics = GetParent()->FindGameObjects<Magic>();
	for (Magic* pMagic : pMagics)
	{
		//解説　見ればわかると思うがこれは『Magic』と『Ghost』の距離を求めている
		float dx = pMagic->GetPosition().x - (transform_.position_.x + 16.0f);//Mgの座標X - Ghの座標X
		float dy = pMagic->GetPosition().y - (transform_.position_.y + 16.0f);//Mgの座標Y - Ghの座標Y
		float distance = sqrt(dx * dx + dy * dy);//ここで明確な距離を計算

		if (distance <= 20.0f)
		{
			KillMe();
			break;
		}

	}
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
	//今回は正面を向いてもらうだけでいいんで、一番上の三列のみ回す
	// スプライトのサイズを計算
	int spriteWidth = 256 / 3;
	int spriteHeight = 344 / 4;

	int frameX = animeFrame_ % 3;

	// スプライトを描画
	DrawRectGraph(x, y, frameX * spriteWidth, 0, spriteWidth, spriteHeight, hImage_, TRUE);

	DrawCircle(x + 39, y + 34, 32, GetColor(255, 0, 0), FALSE);
}

void Ghost::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

bool Ghost::ColliderCircle(float x, float y, float r)
{
	//x,y,rが相手の円の情報
	//自分の円の情報
	float myCenterX = transform_.position_.x + 32.0f;
	float myCenterY = transform_.position_.y + 32.0f;
	float myR = 30.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if (sqrt(dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}
