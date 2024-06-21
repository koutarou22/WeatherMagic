#include "Slime.h"
#include "Camera.h"
#include "Field.h"

namespace
{
	const float MOVE_SPEED = 2.5f;
	/*const float GROUND = 595.0f;*/
	const float JUMP_HEIGHT = 64.0f * 1.0f;
	const float GRAVITY = 9.8f / 60.0f;

	int hitX = 0;
	int hitY = 0;

	int direction = 1;
};
Slime::Slime(GameObject* scene)
{
	hImage = LoadGraph("Assets/slime.png");
	assert(hImage > 0);
	transform_.position_.x = 800.0f;
	transform_.position_.y = 400.0f;
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

	transform_.position_.x -= WeatherSpeed_ * direction;

	if (pField != nullptr)
	{
		if (pField->CollisionLeft(hitX,hitY) && direction == -1)
		{
			direction = 1;
		}
		else if (pField->CollisionRight(hitX, hitY) && direction == 1)
		{
			direction = -1;
		}
	}

	//---------------衝突判定(左)--------------------------------
	hitX = transform_.position_.x;
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
		int push = pField->CollisionRight(hitX, 0);
		transform_.position_.x -= push;

		if (pField->CollisionRight(hitX, hitY) && direction == 1)
		{
			direction = -1;
		}
	}
	//----------------------------------------------------------

	if (CheckHitKey(KEY_INPUT_SPACE))
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
	}
	else
	{
		prevSpaceKey = false;
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
		int pushR = pField->CollisionDown(transform_.position_.x + 50, transform_.position_.y + 54);
		int pushL = pField->CollisionDown(transform_.position_.x + 14, transform_.position_.y + 54);
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

}

void Slime::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		x -= cam->GetValue();
	}
	DrawRectGraph(x, y, 0, 0, 64, 64, hImage, TRUE);
	DrawFormatString(0, 90, GetColor(255, 255, 255), "スライムがぶつかった時: %d", direction);
	
}

void Slime::WeatherEffects(Weather* weather)
{
	WeatherState WeatherState = weather->GetWeatherState();
	float WeatherEffect = weather->GetWeatherChange();

	if (WeatherState == Rainy)
	{
		WeatherSpeed_ = MOVE_SPEED * (1.0f - WeatherEffect); // 雨の日は速度を減少させる
		/*RainHappening_ = transform_.rotate_.x += 2.0f;
		RainHappening_ = transform_.rotate_.y += 2.0f;*/

		//transform_.scale_.x *= 1.0f + WeatherEffect; // x方向のスケールを増加
		//transform_.scale_.y *= 1.0f + WeatherEffect; // y方向のスケールを増加
	}
	else
	{
		WeatherSpeed_ = MOVE_SPEED; // 通常の速度
	}
}
