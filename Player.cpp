#include <DxLib.h>
#include <assert.h>
#include"Weather.h"
#include "Player.h"
#include "Stone.h"
#include "Camera.h"
#include "Bird.h"
#include "Field.h"
#include "Time.h"

namespace
{
	const float MOVE_SPEED = 4.5f;
	const float GROUND = 600.0f;
	const float JUMP_HEIGHT = 64.0f * 3.0f;
	const float GRAVITY = 9.8f / 60.0f;

	int hitX;
	int hitY;
};
Player::Player(GameObject* parent) : GameObject(sceneTop),WeatherSpeed_(MOVE_SPEED)
{
	hImage = LoadGraph("Assets/aoi.png");
	assert(hImage > 0);
	transform_.position_.x = 100.0f;
	transform_.position_.y = GROUND;
	onGround = true;
	flameCounter = 0;
	animType = 0;
	animFrame = 0;
}

Player::~Player()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Player::Update()
{
	Field* pField = GetParent()->FindGameObject<Field>();
	Weather* pWeather = GetParent()->FindGameObject<Weather>();

	if (pWeather != nullptr)
	{
		WeatherEffects(pWeather); // 天候関数を呼び出す
	}

		if (state == S_Cry)
		{
			flameCounter++;
			if (flameCounter);
		}

		if (CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_RIGHT))
		{
			transform_.position_.x += WeatherSpeed_;
			if (++flameCounter >= 8)
			{
				animFrame = (animFrame + 1) % 4;//if文を使わない最適解
				flameCounter = 0;
			}

			//---------------衝突判定(右)--------------------------------
			hitX = transform_.position_.x + 50;
			hitY = transform_.position_.y + 63;

			if (pField != nullptr)
			{
				int push = pField->CollisionRight(hitX, hitY);
				transform_.position_.x -= push;
			}
			//----------------------------------------------------------
		}
		else if (CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_LEFT))
		{
			
			transform_.position_.x -= WeatherSpeed_;
			if (++flameCounter >= 8)
			{
				animFrame = (animFrame + 1) % 4;//if文を使わない最適解
				flameCounter = 0;
			}

			//---------------衝突判定(左)--------------------------------
			hitX = transform_.position_.x;
			hitY = transform_.position_.y + 63; // プレイヤーの足元のY座標
			if (pField != nullptr)
			{
				int push = pField->CollisionLeft(hitX, hitY);
				transform_.position_.x += push;
			}
			//-----------------------------------------------------------
		}
		else
		{
			animFrame = 0;
			flameCounter = 0;
		}


		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			PictFlame = 80;

			animFrame = (animFrame + 1) % 4;
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
			int pushR = pField->CollisionDown(transform_.position_.x + 50, transform_.position_.y + 63);
			int pushL = pField->CollisionDown(transform_.position_.x + 14, transform_.position_.y + 63);
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

		if (CheckHitKey(KEY_INPUT_N)) 
		{
			if (pWeather != nullptr) 
			{
				printf("Nキーが押されました。\n");
				// 現在の天候状態を取得
				WeatherState WeatherState = pWeather->GetWeatherState();
				// 天候を切り替える
				if (WeatherState == Sunny) {
					printf("雨が降ってきた..\n");
					pWeather->SetWeather(Rainy);
				}
				else {
					printf("晴れた！\n");
					pWeather->SetWeather(Sunny);
				}
			}
		}
		//拡張性はない
		//if (transform_.position_.y >= GROUND)//地面についたら速度を元に戻す、戻さないと貫通する恐れあり
		//{
		//	transform_.position_.y = GROUND;
		//	Jump_P = 0.0f;
		//	onGround = true;
		//}
		//------------------------------------------------------------------------------------------

		if (CheckHitKey(KEY_INPUT_M))
		{
			Stone* st = Instantiate<Stone>(GetParent());
			st->SetPosition(transform_.position_);
		}


		Camera* cam = GetParent()->FindGameObject<Camera>();

		if (cam != nullptr) {
			cam->GetPlayerPos(this);
		}

}

void Player::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue(); 
	}

	DrawRectGraph(x, y, animFrame * 64, animType * 64, 64, 64, hImage, TRUE);
	// プレイヤーの座標を画面に表示
	DrawFormatString(0, 0, GetColor(255, 255, 255), "プレイヤー(カメラ)の位置: (%d, %d)", x, y);
}

void Player::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

void Player::WeatherEffects(Weather* weather)
{
	WeatherState WeatherState = weather->GetWeatherState();
	float WeatherEffect = weather->GetWeatherChange();

	if (WeatherState == Rainy)
	{
		WeatherSpeed_ = MOVE_SPEED * (1.0f - WeatherEffect); // 雨の日は速度を減少させる
	}
	else
	{
		WeatherSpeed_ = MOVE_SPEED; // 通常の速度
	}
}
