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
		WeatherEffects(pWeather); // �V��֐����Ăяo��
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

	//---------------�Փ˔���(��)--------------------------------
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

	//---------------�Փ˔���(�E)--------------------------------
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

	//-------------------+++�����̃v���O�����͊�b�̊�b+++-------------------

	Jump_P += GRAVITY; //���x += �����x
	transform_.position_.y += Jump_P; //���W += ���x

	//---------------�Փ˔���(��)--------------------------------
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

	//---------------�Փ˔���(��)--------------------------------
	if (pField != nullptr)
	{
		int pushR = pField->CollisionDown(transform_.position_.x + 50, transform_.position_.y + 54);
		int pushL = pField->CollisionDown(transform_.position_.x + 14, transform_.position_.y + 54);
		int push = max(pushR, pushL);//�Q�̑����̂߂肱�݂̑傫���ق�
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
	DrawFormatString(0, 90, GetColor(255, 255, 255), "�X���C�����Ԃ�������: %d", direction);
	
}

void Slime::WeatherEffects(Weather* weather)
{
	WeatherState WeatherState = weather->GetWeatherState();
	float WeatherEffect = weather->GetWeatherChange();

	if (WeatherState == Rainy)
	{
		WeatherSpeed_ = MOVE_SPEED * (1.0f - WeatherEffect); // �J�̓��͑��x������������
		/*RainHappening_ = transform_.rotate_.x += 2.0f;
		RainHappening_ = transform_.rotate_.y += 2.0f;*/

		//transform_.scale_.x *= 1.0f + WeatherEffect; // x�����̃X�P�[���𑝉�
		//transform_.scale_.y *= 1.0f + WeatherEffect; // y�����̃X�P�[���𑝉�
	}
	else
	{
		WeatherSpeed_ = MOVE_SPEED; // �ʏ�̑��x
	}
}
