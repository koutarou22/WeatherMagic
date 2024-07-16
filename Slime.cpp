#include "Slime.h"
#include "Player.h"
#include "Camera.h"
#include "Field.h"
#include "Magic.h"
#include "Damage.h"

namespace
{
	const float MOVE_SPEED = 2.5f;
	const float GROUND = 595.0f;
	const float JUMP_HEIGHT = 64.0f * 1.0f;
	const float GRAVITY = 9.8f / 60.0f;
	static const int SCREEN_WIDTH = 1280;
	int hitX = 0;
	int hitY = 0;

};

Slime::Slime(GameObject* scene)
{
	hImage = LoadGraph("Assets/slime_run2.png");
	assert(hImage > 0);
	/*transform_.position_.x = 1200.0f;
	transform_.position_.y = 600.0f;*/
	StunTimer_ = 0;

}

Slime::~Slime()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Slime::Update()
{
	Field* pField = GetParent()->FindGameObject<Field>();
	Weather* pWeather = GetParent()->FindGameObject<Weather>();

	if (pWeather != nullptr)
	{
		WeatherEffects(pWeather); // 天候関数を呼び出す
	}

	// 衝突判定と反転フラグの設定
	if (pField->CollisionLeft(hitX, hitY) && direction == -1)
	{
		Reverse_ = true;
	}
	else if (pField->CollisionRight(hitX, hitY) && direction == 1)
	{
		Reverse_ = true;
	}

	if (Reverse_)
	{
		direction *= -1;
		Reverse_ = false;
	}

	if (++flameCounter_ >= 24)
	{
		animeFrame_ = (animeFrame_ + 1) % 4;//if文を使わない最適解
		flameCounter_ = 0;
	}

	//---------------衝突判定(左)--------------------------------
	hitX = transform_.position_.x + 18;
	hitY = transform_.position_.y + 54; 
	if (pField != nullptr)
	{
		int push = pField->CollisionLeft(hitX, hitY);
		transform_.position_.x += push;

		if (pField->CollisionLeft(hitX, hitY) && direction == -1)
		{
			direction = 1;
		}
	}
	//-----------------------------------------------------------

//---------------衝突判定(右)--------------------------------
hitX = transform_.position_.x + 50;
hitY = transform_.position_.y + 54;

if (pField != nullptr)
{
	int push = pField->CollisionRight(hitX, hitY);
	transform_.position_.x -= push;

	if (pField->CollisionRight(hitX, hitY) && direction == 1)
	{
		direction = -1;
	}
}
//----------------------------------------------------------

	if(CoolGround_Now <= 0 && StunTimer_ <= 0)
	{
		
		if (prevSpaceKey == false)
		{
			if (onGround)
			{
				Jump_P = -sqrtf(2 * GRAVITY * JUMP_HEIGHT);
				
				onGround = false;
				
			}

		}
		prevSpaceKey = true;
		CoolGround_Now = 240;
	}
	else
	{
		prevSpaceKey = false;
	}

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		x -= cam->GetValue();
	}


	if (cam != nullptr)
	{
		// カメラの位置を取得
		int camX = cam->GetValue();

		if (transform_.position_.x >= camX && transform_.position_.x <= camX + SCREEN_WIDTH)
		{
			if (!onGround)
			{
				transform_.position_.x += WeatherSpeed_ * direction;
			}
		}
	}
	
	if (StunTimer_ > 0)
	{
		StunTimer_--;
	}

	if (CoolGround_Now > 0)
	{
		CoolGround_Now--;
	}
	
	//-------------------+++加速のプログラムは基礎の基礎+++-------------------

	Jump_P += GRAVITY; //速度 += 加速度
	transform_.position_.y += Jump_P; //座標 += 速度

	//---------------衝突判定(上)--------------------------------
	if (!onGround && pField != nullptr)
	{
		hitX = transform_.position_.x + 32;
		hitY = transform_.position_.y;

		int push = pField->CollisionUp(hitX, hitY);
		if (push > 0) {
			Jump_P = 0.0f;
			transform_.position_.y += push;
		}
	}
	//-----------------------------------------------------------

	//---------------衝突判定(下)--------------------------------
	if (pField != nullptr)
	{
		int pushR = pField->CollisionDown(transform_.position_.x + 50 * transform_.scale_.x, transform_.position_.y + 54 * transform_.scale_.y);
		int pushL = pField->CollisionDown(transform_.position_.x + 14 * transform_.scale_.x, transform_.position_.y + 54 * transform_.scale_.y);
		int push = max(pushR, pushL);//２つの足元のめりこみの大きいほう
		if (push >= 1) {
			transform_.position_.y -= push - 1;
			Jump_P = 0.0f;
			onGround = true;
		}
		else {
			onGround = false;
		}

	}
	//-----------------------------------------------------------


	if (transform_.position_.y > GROUND + 20)
	{
		KillMe();
	}

	std::list<Magic*> pMagics = GetParent()->FindGameObjects<Magic>();
	for (Magic* pMagic : pMagics)
	{
		//解説『Magic』と『Slime』の距離を求めている
		float dx = pMagic->GetPosition().x - (transform_.position_.x + 10.0f);//Mgの座標X - Slの座標X
		float dy = pMagic->GetPosition().y - (transform_.position_.y + 10.0f);//Mgの座標Y - Slの座標Y
		float distance = sqrt(dx * dx + dy * dy);//ここで明確な距離を計算

		if (distance <= 20.0f)
		{
			Damage* dam = Instantiate<Damage>(GetParent());
			dam->SetPosition(transform_.position_);
			StunTimer_ = 300;
			break;
		}
	}
}

void Slime::Draw()
{
	Field* pField = GetParent()->FindGameObject<Field>();
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		x -= cam->GetValue();
	}

	int SWidth = 512 / 6; 
	int SHeight = 86; 

	int frameX = animeFrame_ % 6; 
	int hFrame = DerivationGraph(frameX, 0, SWidth, SHeight, hImage);

	if (direction == 1)
	{
		DrawRectExtendGraph(x, y, x + SWidth * transform_.scale_.x, y + SHeight * transform_.scale_.y, frameX, 0, SWidth, SHeight, hImage, TRUE);
	}
	else if (direction == -1)
	{
		// DrawModiGraphを使用して画像を反転
		DrawModiGraph(x + SWidth * transform_.scale_.x, y, x, y, x, y + SHeight * transform_.scale_.y, x + SWidth * transform_.scale_.x, y + SHeight * transform_.scale_.y, hFrame, TRUE);
	}

	//Debug用
	// 
	DrawFormatString(0, 90, GetColor(255, 255, 255), "スライムがぶつかった時: %d", WindTimer_);
	//DrawCircle(x + 32.0f * transform_.scale_.x, y + 32.0f * transform_.scale_.y, 32.0f * transform_.scale_.x, GetColor(255, 0, 0), FALSE);
	//DrawBox(rectX, rectY, rectX + rectW, rectY + rectH, GetColor(255, 0, 0), FALSE);
}

void Slime::WeatherEffects(Weather* weather)
{
	WeatherState WeatherState = weather->GetWeatherState();
	float WeatherEffect = weather->GetWeatherChange();

	RainScale(WeatherState, transform_, WeatherSpeed_, MOVE_SPEED, WeatherEffect, ScaleEffect_);

}

bool Slime::ColliderRect(float x, float y, float w, float h)
{
	// x,y,w,hが相手の矩形の情報
	// 自分の矩形の情報
	float myX = transform_.position_.x;
	float myY = transform_.position_.y;
	float myW = 64.0f ; 
	float myH = 64.0f ; 

	// 矩形の衝突判定
	if (myX < x + w && myX + myW > x && myY < y + h && myY + myH > y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Slime::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

void Slime::RainScale(WeatherState state, Transform& transform, float& WeatherSpeed_, float MOVE_SPEED, float WeatherEffect, float& ScaleEffect_)
{
	if (state == Rainy)
	{
		WeatherSpeed_ = MOVE_SPEED * (1.0f - WeatherEffect); // 雨の日は速度を減少させる

		
		if (transform_.scale_.x < 1.5f)//大きさが1.5で止まるように
		{
			ScaleEffect_ = transform_.scale_.x;
			transform_.scale_.x += 0.01f;
			transform_.position_.y -= (transform_.scale_.x - ScaleEffect_) * 32;
		}
		if (transform_.scale_.y < 1.5f) {
			ScaleEffect_ = transform_.scale_.y;
			transform_.scale_.y += 0.01f; 
			transform_.position_.y -= (transform_.scale_.y - ScaleEffect_) * 32;
		}
	}
	else 
	{
		WeatherSpeed_ = MOVE_SPEED; 
		
		if (transform_.scale_.x > 1.0f) {
			ScaleEffect_ = transform_.scale_.x;
			transform_.scale_.x -= 0.01f; 
			transform_.position_.y += (ScaleEffect_ - transform_.scale_.x) * 32; 
		}
		if (transform_.scale_.y > 1.0f) {
			ScaleEffect_ = transform_.scale_.y;
			transform_.scale_.y -= 0.01f; 
			transform_.position_.y += (ScaleEffect_ - transform_.scale_.y) * 32; 
		}
	 
	}

	if (state == Gale)
	{
		if (!PressKey_R && !PressKey_L && WindTimer_ <= 0)
		{
			if (CheckHitKey(KEY_INPUT_RIGHT))
			{
				WindTimer_ = 300;
				Reverse_ = true;
				PressKey_R = true;
			}
			else if (CheckHitKey(KEY_INPUT_LEFT))
			{
				WindTimer_ = 300;
				Reverse_ = false;
				PressKey_L = true;
			}
		}

		if (WindTimer_ > 0)
		{
			if (PressKey_R)
			{
				transform_.position_.x += 4.0f;
			}
			else if (PressKey_L)
			{
				transform_.position_.x -= 4.0f;
			}

			WindTimer_--;
			if (WindTimer_ == 0)
			{
				PressKey_R = false;
				PressKey_L = false;
			}
		}
	}

	
}

