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

	//動かしたとき引きずる音
	DustHandle = LoadSoundMem("Assets/Music/SE/Rock/Dust.mp3");
	assert(DustHandle != -1);

	hitX = transform_.position_.x + 32;
	hitY = transform_.position_.y + 32;


	CanMoveRight_ = true;
	CanMoveLeft_ = true;

	IsMove_ = false;
	IsPlayingDust_ = false;
}

Rock::~Rock()
{
}

void Rock::Update()
{
	Weather* pWeather = GetParent()->FindGameObject<Weather>();
	Camera* cam = GetParent()->FindGameObject<Camera>();


	if (pWeather != nullptr)
	{
		// 天候関数を呼び出す
		WeatherEffects(pWeather);
	}
   
	CheckHitStage();

	//重力の処理
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

	//xboxコントローラーの入力情報を取得
	PadAnalogInput_ = GetJoypadXInputState(DX_INPUT_PAD1, &Input_);

	if (cam != nullptr)
	{
		int camX = cam->GetValue();
		if (transform_.position_.x >= camX && transform_.position_.x <= camX + SCREEN_WIDTH)
		{
			if (state == Gale)
			{
				IsMove_ = false;
				Player* pPlayer = GetParent()->FindGameObject<Player>();
				int MpVanish = pPlayer->GetMp();
				if (MpVanish >= 4)
				{
					if (Input_.ThumbRX <= -10000 || CheckHitKey(KEY_INPUT_K))
					{
						if (CanMoveLeft_)
						{
							transform_.position_.x -= MOVE_SPEED;
							IsMove_ = true;
						}
					}
					else if (Input_.ThumbRX >= 10000 || CheckHitKey(KEY_INPUT_L))
					{
						if (CanMoveRight_)
						{
							transform_.position_.x += MOVE_SPEED;
							IsMove_ = true;
						}
					}

				}

				if (IsMove_)
				{ 
				   if (!IsPlayingDust_) 
				   { 
					   PlaySoundMem(DustHandle, DX_PLAYTYPE_LOOP); 
					   IsPlayingDust_ = true; 
				   } 
				}
				else
				{ 
					if (IsPlayingDust_) 
					{ 
						StopSoundMem(DustHandle); 
					    IsPlayingDust_ = false;
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

void Rock::CheckHitStage()
{
	Field* pField = GetParent()->FindGameObject<Field>();


	//衝突判定(左)
	hitX = transform_.position_.x;
	hitY = transform_.position_.y + 5;
	if (pField != nullptr)
	{
		int push = pField->CollisionLeft(hitX, hitY);
		if (push > 0)
		{
			CanMoveLeft_ = false;
		}
		else
		{
			CanMoveLeft_ = true;
		}
	}

    //衝突判定(右)
	hitX = transform_.position_.x + 60;
	hitY = transform_.position_.y + 60;

	if (pField != nullptr)
	{
		int push = pField->CollisionRight(hitX, hitY);
		if (push > 0)
		{
			CanMoveRight_ = false;
		}
		else
		{
			CanMoveRight_ = true;
		}
	}

	//衝突判定(上)
	if (!OnGround_ && pField != nullptr)
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

	//衝突判定(下)
	if (pField != nullptr)
	{
		int pushR = pField->CollisionDown(transform_.position_.x + 50 * transform_.scale_.x, transform_.position_.y + 60 * transform_.scale_.y);
		int pushL = pField->CollisionDown(transform_.position_.x + 14 * transform_.scale_.x, transform_.position_.y + 60 * transform_.scale_.y);
		int push = max(pushR, pushL);
		if (push >= 1)
		{
			transform_.position_.y -= push - 1;
			JumpPower_ = 0.0f;
			OnGround_ = true;
		}
		else
		{
			OnGround_ = false;
		}
	}
}


