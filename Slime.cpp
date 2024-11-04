#include "Slime.h"
#include "Player.h"
#include "Camera.h"
#include "Field.h"
#include "Magic.h"
#include "Damage.h"
#include "Rock.h"
#include <iostream>
#include "Weather.h"

namespace
{
	const float MOVE_SPEED = 2.5f;
	const float GROUND = 595.0f;
	const float JUMP_HEIGHT = 64.0f * 1.0f;
	const float GRAVITY = 9.8f / 60.0f;
	static const int SCREEN_WIDTH = 1280;
	int hitX = 0;
	int hitY = 0;

	int SWidth = 512 / 6;
	int SHeight = 86;
};

Slime::Slime(GameObject* scene)
{
	hImage = LoadGraph("Assets/Chara/slime_run2.png");
	assert(hImage > 0);
	StunTimer_ = 0;

}

Slime::~Slime()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}
bool HitWeather = true;

void Slime::Update()
{
	Field* pField = GetParent()->FindGameObject<Field>();
	Weather* pWeather = GetParent()->FindGameObject<Weather>();

	if (WindTimer_ > 0)
	{
		WindTimer_--;
	}

	if (pWeather != nullptr)
	{
		WeatherEffects(pWeather); // �V��֐����Ăяo��
		HitWeather = false;
	}

	// �Փ˔���Ɣ��]�t���O�̐ݒ�
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
		animeFrame_ = (animeFrame_ + 1) % 4;//if�����g��Ȃ��œK��
		flameCounter_ = 0;
	}

	//---------------�Փ˔���(��)--------------------------------
	hitX = transform_.position_.x + 9;
	hitY = transform_.position_.y /*+ 19*/; 
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
				if (pWeather->GetWeatherState() != WeatherState::Snow)
				{
					Jump_P = -sqrtf(2 * GRAVITY * JUMP_HEIGHT);
				}
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


	if (cam != nullptr)//��ʊO�Ȃ�s���͂Ƃ�Ȃ���I
	{
		// �J�����̈ʒu���擾
		int camX = cam->GetValue();

		if (transform_.position_.x >= camX && transform_.position_.x <= camX + SCREEN_WIDTH)
		{
			if (!onGround)
			{

				//�V��擾�A��Ȃ�X�s�[�h��0��
				if (pWeather->GetWeatherState() != WeatherState::Snow)
				{
					transform_.position_.x += WeatherSpeed_ * direction;
				}
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
		int pushR = pField->CollisionDown(transform_.position_.x + 25 * transform_.scale_.x, transform_.position_.y + 64 * transform_.scale_.y);
		int pushL = pField->CollisionDown(transform_.position_.x + 10 * transform_.scale_.x, transform_.position_.y + 54 * transform_.scale_.y);
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


	if (transform_.position_.y > GROUND + 20)
	{
		KillMe();
	}

	std::list<Magic*> pMagics = GetParent()->FindGameObjects<Magic>();
	for (Magic* pMagic : pMagics)
	{
		//����wMagic�x�ƁwSlime�x�̋��������߂Ă���
		float dx = pMagic->GetPosition().x+32 - (transform_.position_.x + 42.0f);//Mg�̍��WX - Sl�̍��WX
		float dy = pMagic->GetPosition().y+32 - (transform_.position_.y + 42.0f);//Mg�̍��WY - Sl�̍��WY
		float distance = sqrt(dx * dx + dy * dy);//�����Ŗ��m�ȋ������v�Z

		if (distance <= 30.0f)
		{
			Damage* dam = Instantiate<Damage>(GetParent());
			dam->SetPosition(transform_.position_);
			StunTimer_ = 300;
			break;
		}
	}

	std::list<Rock*> pRocks = GetParent()->FindGameObjects<Rock>();
	for (Rock* pRock : pRocks)
	{
		float dx = pRock->GetPosition().x + 32 - (transform_.position_.x + SWidth / 2.0f);
		float dy = pRock->GetPosition().y + 32 - (transform_.position_.y + SHeight / 2.0f);

		
		float distance = sqrt(dx * dx + dy * dy);
		int push;

		if (distance <= 60.0f)
		{
			if (dy < 0 && abs(dx) <= 32) //��̏�ɏ��
			{
				transform_.position_.y = pRock->GetPosition().y - SHeight; // �X���C������Ɉړ�
				WeatherSpeed_ = 0;
				onGround = true; // �X���C���͊�̏�ɂ���̂ŁA�n�ʂɂ���Ƃ݂Ȃ�
			}
			else if (dy > 0 && abs(dx) <= 32) //��̉��ɂԂ���
			{
				push = 3;
				transform_.position_.y = pRock->GetPosition().y + push; // �X���C�������Ɉړ�
				WeatherSpeed_ = MOVE_SPEED;
			}
			else if (dx < 0 && direction == -1) // ��̉E���̏Փ˔���
			{
				push = 1;
				transform_.position_.x += push; 
				Reverse_ = true; 
			}
			else if (dx > 0 && direction == 1) // ��̍����̏Փ˔���
			{
				push = 1;
				transform_.position_.x -= push;
				Reverse_ = true; 
			}
			
		}
	}
}

void Slime::Draw()
{
	Field* pField = GetParent()->FindGameObject<Field>();
	Player* pPlayer = GetParent()->FindGameObject<Player>();
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		x -= cam->GetValue();
	}

	
	int frameX = animeFrame_ % 6; 
	int hFrame = DerivationGraph(frameX, 0, SWidth, SHeight, hImage);


	if (direction == 1)
	{
		DrawRectExtendGraph(x, y, x + SWidth * transform_.scale_.x, y + SHeight * transform_.scale_.y, frameX, 0, SWidth, SHeight, hImage, TRUE);
	}
	else if (direction == -1)
	{
		// DrawModiGraph���g�p���ĉ摜�𔽓]
		DrawModiGraph(x + SWidth * transform_.scale_.x, y, x, y, x, y + SHeight * transform_.scale_.y, x + SWidth * transform_.scale_.x, y + SHeight * transform_.scale_.y, hFrame, TRUE);
	}
}

void Slime::WeatherEffects(Weather* weather)
{
	WeatherState WeatherState = weather->GetWeatherState();
	float WeatherEffect = weather->GetWeatherChange();

	HitWeather = true;
	RainScale(WeatherState, transform_, WeatherSpeed_, MOVE_SPEED, WeatherEffect, ScaleEffect_);
	
	//GaleEffect(WeatherState);
}


bool Slime::ColliderRect(float x, float y, float w, float h)
{
	// x,y,w,h������̋�`�̏��
	// �����̋�`�̏��
	float myX = transform_.position_.x;
	float myY = transform_.position_.y;
	float myW = 85.0f; 
	float myH = 85.0f; 

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

void Slime::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

void Slime::RainScale(WeatherState state, Transform& transform, float& WeatherSpeed_, float MOVE_SPEED, float WeatherEffect, float& ScaleEffect_)
{
	Player* pPlayer = GetParent()->FindGameObject<Player>();
	if (pPlayer == nullptr) {
		return;
	}

	int MpVanish = pPlayer->GetMp();

	if (state == Rain && MpVanish > 0)
	{
		//WeatherSpeed_ = MOVE_SPEED * (1.0f - WeatherEffect); // �J�̓��͑��x������������

		
		if (transform_.scale_.x < 1.5f)//�傫����1.5�Ŏ~�܂�悤��
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
	
}

bool wasKeyPressed_R = false;
bool wasKeyPressed_L = false;

void Slime::GaleEffect(WeatherState state)
{
	if (state == Gale)
	{
		Player* pPlayer = GetParent()->FindGameObject<Player>();
		if (pPlayer == nullptr) {
			return;
		}
		int MpVanish = pPlayer->GetMp(); 
		if (WindTimer_ <= 0 && MpVanish >= 4)
		{
			if (CheckHitKey(KEY_INPUT_RIGHT))
			{
				WindTimer_ = 300;
				PressKey_R = true;
			}
			else if (CheckHitKey(KEY_INPUT_LEFT))
			{
				WindTimer_ = 300;
				PressKey_L = true;
			}
		}

		if (WindTimer_ > 0)
		{
			if (PressKey_R)
			{
				transform_.position_.x += 1.5f;
			}
			else if (PressKey_L)
			{
				transform_.position_.x -= 1.5f;
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
