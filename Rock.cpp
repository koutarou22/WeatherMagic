#include "Rock.h"
#include "Player.h"
#include "Camera.h"
#include "Field.h"

namespace
{
	const float MOVE_SPEED = 2.5f;
	const float GROUND = 595.0f;
	const float JUMP_HEIGHT = 64.0f * 1.0f;
	const float GRAVITY = 9.8f / 60.0f;

	int hitX = 0;
	int hitY = 0;

};

Rock::Rock(GameObject* scene)
{
	hImage_ = LoadGraph("Assets/Rock.png");
	assert(hImage_ > 0);
	transform_.position_.x = 30.0f;
	transform_.position_.y = 300.0f;
	transform_.scale_.x += 2.0;
	transform_.scale_.y += 2.0;

}

Rock::~Rock()
{
	if (hImage_ > 0)
	{
		DeleteGraph(hImage_);
	}
}

void Rock::Update()
{
	Field* pField = GetParent()->FindGameObject<Field>();
	Weather* pWeather = GetParent()->FindGameObject<Weather>();
	Player* pPlayer = GetParent()->FindGameObject<Player>();

	if (pPlayer != nullptr)
	{
		
		if (IsHitPlayer(pPlayer))
		{
			PushOutPlayer(pPlayer);
		}
	}
	if (pWeather != nullptr)
	{
		
			//// プレイヤーがRockの上にいるかどうかを判定
			//if (pPlayer->GetPosition().y + pPlayer->GetHeight() <= transform_.position_.y)
			//{
			//	// プレイヤーがRockの上にいる場合、プレイヤーをRockの上に移動
			//	pPlayer->SetPosition(pPlayer->GetPosition().x, transform_.position_.y - pPlayer->GetHeight());
			//}
			//else
			//{
			//	// プレイヤーがRockの下にいる場合、プレイヤーを「つぶす」
			//	pPlayer->Kill();
			//}
		WeatherEffects(pWeather); // 天候関数を呼び出す
	}

	//---------------衝突判定(左)--------------------------------
	hitX = transform_.position_.x + 18;
	hitY = transform_.position_.y + 54;
	if (pField != nullptr)
	{
		int push = pField->CollisionLeft(hitX, hitY);
		transform_.position_.x += push;
	}
	//-----------------------------------------------------------

//---------------衝突判定(右)--------------------------------
	hitX = transform_.position_.x + 50;
	hitY = transform_.position_.y + 54;

	if (pField != nullptr)
	{
		int push = pField->CollisionRight(hitX, hitY);
		transform_.position_.x -= push;
	}

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
		int pushR = pField->CollisionDown(transform_.position_.x + 50 * transform_.scale_.x, transform_.position_.y + 60 * transform_.scale_.y);
		int pushL = pField->CollisionDown(transform_.position_.x + 14 * transform_.scale_.x, transform_.position_.y + 60 * transform_.scale_.y);
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

void Rock::Draw()
{
	Field* pField = GetParent()->FindGameObject<Field>();
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		x -= cam->GetValue();
	}

	DrawExtendGraph(x, y, x + 64 * transform_.scale_.x, y + 64 * transform_.scale_.y, hImage_, TRUE);

	
	//DrawBox(rectX, rectY, rectX + rectW, rectY + rectH, GetColor(255, 0, 0), FALSE);
}

void Rock::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

void Rock::WeatherEffects(Weather* weather)
{
	WeatherState WeatherState = weather->GetWeatherState();
	float WeatherEffect = weather->GetWeatherChange();

	if (WeatherState == Gale)
	{
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			transform_.position_.x += 0.5f;

		}
		else if (CheckHitKey(KEY_INPUT_LEFT))
		{
			transform_.position_.x -= 0.5f;
			
		}
	}
	
}

bool Rock::IsHitPlayer(Player*player)
{

	// Playerの矩形の情報
	float PX = player->GetPosition().x;
	float PY = player->GetPosition().y;
	float PW = player->GetWidth();
	float PH = player->GetHeight();

	// Rockの矩形の情報
	float rockX = transform_.position_.x;
	float rockY = transform_.position_.y;
	float rockW = 64.0f * transform_.scale_.x; // スケールを適用
	float rockH = 64.0f * transform_.scale_.y; // スケールを適用

	// 矩形の衝突判定
	if (rockX < PX + PW && rockX + rockW > PX && rockY < PY + PH && rockY + rockH > PY)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Rock::PushOutPlayer(Player* player)
{
	// Rockの中心位置
	float rockCenterX = transform_.position_.x + (64.0f * transform_.scale_.x) / 2;
	float rockCenterY = transform_.position_.y + (64.0f * transform_.scale_.y) / 2;

	// Playerの中心位置
	float playerCenterX = player->GetPosition().x + player->GetWidth() / 2;
	float playerCenterY = player->GetPosition().y + player->GetHeight() / 2;

	// RockとPlayerの中心間の距離
	float dx = playerCenterX - rockCenterX;
	float dy = playerCenterY - rockCenterY;

	// 押し出す方向（単位ベクトル）
	float length = sqrt(dx * dx + dy * dy);
	float dirX = dx / length;
	float dirY = dy / length;

	// 押し出す力（ここでは一定値を使用）
	float pushPower = 10.0f;

	// Playerの位置を調整
	player->SetPosition(player->GetPosition().x + dirX * pushPower, player->GetPosition().y + dirY * pushPower);
}
