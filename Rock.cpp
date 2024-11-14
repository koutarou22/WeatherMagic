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
	static const int SCREEN_WIDTH = 1280;
};

Rock::Rock(GameObject* scene)
{
	hImage_ = LoadGraph("Assets/Chara/Rockmin.png");
	assert(hImage_ > 0);
	transform_.position_.x = 200.0f;
	transform_.position_.y = 600.0f;
	//transform_.scale_.x += 2.0;
	//transform_.scale_.y += 2.0;

	hitX = transform_.position_.x + 32;
	hitY = transform_.position_.y + 32;

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

	if (pWeather != nullptr)
	{
		WeatherEffects(pWeather); // �V��֐����Ăяo��
	}


	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		x -= cam->GetValue();
	}


	//---------------�Փ˔���(��)--------------------------------
	hitX = transform_.position_.x + 18;
	hitY = transform_.position_.y + 54;
	if (pField != nullptr)
	{
		int push = pField->CollisionLeft(hitX, hitY);
		transform_.position_.x += push;
	}
	//-----------------------------------------------------------

//---------------�Փ˔���(�E)--------------------------------
	hitX = transform_.position_.x + 32;
	hitY = transform_.position_.y + 32;

	if (pField != nullptr)
	{
		int push = pField->CollisionRight(hitX, hitY);
		transform_.position_.x -= push;
	}

	Jump_P += GRAVITY; //���x += �����x
	transform_.position_.y += Jump_P; //���W += ���x

	if (transform_.position_.y > 635)
	{
		transform_.position_.y = 635;
	}

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
		int pushR = pField->CollisionDown(transform_.position_.x + 50 * transform_.scale_.x, transform_.position_.y + 60 * transform_.scale_.y);
		int pushL = pField->CollisionDown(transform_.position_.x + 14 * transform_.scale_.x, transform_.position_.y + 60 * transform_.scale_.y);
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
}

void Rock::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

void Rock::WeatherEffects(Weather* weather)
{
	Field* pField = GetParent()->FindGameObject<Field>();
	WeatherState WeatherState = weather->GetWeatherState();
	float WeatherEffect = weather->GetWeatherChange();

	GaleEffect(WeatherState);
}

void Rock::GaleEffect(WeatherState state)
{
	Camera* cam = GetParent()->FindGameObject<Camera>();

	//xbox�R���g���[���[�̓��͏����擾
	padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);

	if (cam != nullptr)
	{
		int camX = cam->GetValue();
		if (transform_.position_.x >= camX && transform_.position_.x <= camX + SCREEN_WIDTH)
		{
			if (state == Gale)
			{
				Player* pPlayer = GetParent()->FindGameObject<Player>();
				int MpVanish = pPlayer->GetMp();
				if (MpVanish >= 4)
				{
					if (input.ThumbRX <= -10000 || CheckHitKey(KEY_INPUT_K))
					{
						//WindTimer_ = 300;
						//PressKey_R = true;
						transform_.position_.x -= 1.2f;
					}
					else if (input.ThumbRX >= 10000 || CheckHitKey(KEY_INPUT_L))
					{
						//WindTimer_ = 300;
						//PressKey_L = true;
						transform_.position_.x += 1.2f;
					}
				}
			}
		}
	}
}

bool Rock::ColliderRect(float x, float y, float w, float h)
{
	// x,y,w,h������̋�`�̏��
	// �����̋�`�̏��
	float myX = transform_.position_.x;
	float myY = transform_.position_.y;
	float myW = 64.0f;
	float myH = 64.0f;

	// ��`�̏Փ˔���
	if (myX < x + w && myX + myW > x && myY < y + h && myY + myH > y)
	{
		return true;
	}
	else
	{
		return false;
	}
}


