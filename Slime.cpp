#include "Slime.h"
#include "Camera.h"
#include "Field.h"

namespace
{
	const float MOVE_SPEED = 2.5f;
	const float GROUND = 590.0f;
	const float JUMP_HEIGHT = 64.0f * 1.0f;
	const float GRAVITY = 9.8f / 60.0f;
	float horizontalSpeed;
};
Slime::Slime(GameObject* scene)
{
	hImage = LoadGraph("Assets/slime.png");
	assert(hImage > 0);
	transform_.position_.x = 800.0f;
	transform_.position_.y = 590.0f;
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
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		if (prevSpaceKey == false)
		{
			if (onGround)
			{
				// 水平方向の初速度を設定
				horizontalSpeed = MOVE_SPEED;
				// ジャンプ開始時の角度を0にリセット
				sinAngle = 0.0f;
				onGround = false;
			}
		}
		prevSpaceKey = true;
	}
	else
	{
		prevSpaceKey = false;
	}

	// ジャンプ中の場合、サイン関数を使用してY座標を更新
	if (!onGround)
	{
		// サイン関数によるY座標の計算
		float sinValue = sinf(sinAngle * DX_PI_F / -180.0f);
		transform_.position_.y = 500.0f + sinValue * 50.0f;
		// 角度を増加させることで、サイン関数の値を変化させる
		sinAngle += 3.0f;
		// 水平方向の座標の更新
		transform_.position_.x += horizontalSpeed;
	}

	// 地面との衝突判定
	if (pField != nullptr)
	{
		int pushR = pField->CollisionDown(transform_.position_.x + 50, transform_.position_.y + 63);
		int pushL = pField->CollisionDown(transform_.position_.x + 14, transform_.position_.y + 63);
		int push = max(pushR, pushL);
		if (push >= 1) {
			transform_.position_.y -= push - 1;
			onGround = true;
			// 地面に着地したら水平方向の速度をリセット
			horizontalSpeed = 0.0f;
		}
		else {
			onGround = false;
		}
	}

	Jump_P += GRAVITY; //速度 += 加速度
	transform_.position_.y += Jump_P; //座標 += 速度


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
}
