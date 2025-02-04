#include "Rock.h"
#include "Player.h"
#include "Camera.h"
#include "Field.h"

namespace
{
	const float MOVE_SPEED = 1.2f;
	const float GROUND = 595.0f;
	const float JUMP_HEIGHT = 64.0f * 1.0f;
	const float GRAVITY = 9.8f / 60.0f;


	int hitX = 0;
	int hitY = 0;
	static const int SCREEN_WIDTH = 1280;
};

Rock::Rock(GameObject* scene)
{
	hRock_ = LoadGraph("Assets/Chara/Rockmin.png");
	assert(hRock_ > 0);

	//���������Ƃ��������鉹
	DustHandle = LoadSoundMem("Assets/Music/SE/Rock/Dust.mp3");
	assert(DustHandle != -1);

	hitX = transform_.position_.x + 32;
	hitY = transform_.position_.y + 32;


	CanMoveRight = true;
	CanMoveLeft = true;

	isMove = false;
	isPlayingDust = false;


}

Rock::~Rock()
{
	Release();
}

void Rock::Update()
{
	Weather* pWeather = GetParent()->FindGameObject<Weather>();
	Camera* cam = GetParent()->FindGameObject<Camera>();


	if (pWeather != nullptr)
	{
		WeatherEffects(pWeather); // �V��֐����Ăяo��
	}
   
	HitStage();

	//�d�͂̏���
	JumpPower_ += GRAVITY; 
	transform_.position_.y += JumpPower_; 

	if (transform_.position_.y > 635)
	{
		transform_.position_.y = 635;
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

	DrawExtendGraph(x, y, x + 64 * transform_.scale_.x, y + 64 * transform_.scale_.y, hRock_, TRUE);
}

void Rock::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

void Rock::Release()
{
	if (hRock_ > 0)
	{
		DeleteGraph(hRock_);
	}
	if (DustHandle > 0)
	{
		DeleteSoundMem(DustHandle);
	}
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
				isMove = false;
				Player* pPlayer = GetParent()->FindGameObject<Player>();
				int MpVanish = pPlayer->GetMp();
				if (MpVanish >= 4)
				{
					if (input.ThumbRX <= -10000 || CheckHitKey(KEY_INPUT_K))
					{
						if (CanMoveLeft)
						{
							transform_.position_.x -= MOVE_SPEED;
							isMove = true;
						}
					}
					else if (input.ThumbRX >= 10000 || CheckHitKey(KEY_INPUT_L))
					{
						if (CanMoveRight)
						{
							transform_.position_.x += MOVE_SPEED;
							isMove = true;
						}
					}

				}

				if (isMove)
				{ 
				   if (!isPlayingDust) 
				   { 
					   PlaySoundMem(DustHandle, DX_PLAYTYPE_LOOP); 
					   isPlayingDust = true; 
				   } 
				}
				else
				{ 
					if (isPlayingDust) 
					{ 
						StopSoundMem(DustHandle); 
					    isPlayingDust = false;
					}
				}
			}
		}
	}
}

bool Rock::ColliderRect(float x, float y, float w, float h)
{
	float myX = transform_.position_.x;
	float myY = transform_.position_.y;
	float myW = 64.0f;
	float myH = 64.0f;

	if (myX < x + w && myX + myW > x && myY < y + h && myY + myH > y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Rock::HitStage()
{
	Field* pField = GetParent()->FindGameObject<Field>();


	//�Փ˔���(��)
	hitX = transform_.position_.x;
	hitY = transform_.position_.y + 5;
	if (pField != nullptr)
	{
		int push = pField->CollisionLeft(hitX, hitY);
		if (push > 0)
		{
			CanMoveLeft = false;
		}
		else
		{
			CanMoveLeft = true;
		}
	}

    //�Փ˔���(�E)
	hitX = transform_.position_.x + 60;
	hitY = transform_.position_.y + 60;

	if (pField != nullptr)
	{
		int push = pField->CollisionRight(hitX, hitY);
		if (push > 0)
		{
			CanMoveRight = false;
		}
		else
		{
			CanMoveRight = true;
		}
	}

	//�Փ˔���(��)
	if (!onGround && pField != nullptr)
	{
		hitX = transform_.position_.x + 32;
		hitY = transform_.position_.y;

		int push = pField->CollisionUp(hitX, hitY);
		if (push > 0)
		{
			JumpPower_ = 0.0f;
			transform_.position_.y += push;
		}
	}

	//�Փ˔���(��)
	if (pField != nullptr)
	{
		int pushR = pField->CollisionDown(transform_.position_.x + 50 * transform_.scale_.x, transform_.position_.y + 60 * transform_.scale_.y);
		int pushL = pField->CollisionDown(transform_.position_.x + 14 * transform_.scale_.x, transform_.position_.y + 60 * transform_.scale_.y);
		int push = max(pushR, pushL);
		if (push >= 1)
		{
			transform_.position_.y -= push - 1;
			JumpPower_ = 0.0f;
			onGround = true;
		}
		else
		{
			onGround = false;
		}
	}
}


