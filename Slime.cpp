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
	hImage = LoadGraph("Assets/slime.png");
	assert(hImage > 0);
	/*transform_.position_.x = 1200.0f;
	transform_.position_.y = 600.0f;*/
	
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

	if(CoolGround_Now <= 0)
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
		CoolGround_Now = 180;
	}
	else
	{
		prevSpaceKey = false;
	}

	if (!onGround)
	{
		transform_.position_.x += WeatherSpeed_ * direction;
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
		int pushR = pField->CollisionDown(transform_.position_.x + 50 * transform_.scale_.x, transform_.position_.y + 54 * transform_.scale_.y);
		int pushL = pField->CollisionDown(transform_.position_.x + 14 * transform_.scale_.x, transform_.position_.y + 54 * transform_.scale_.y);
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
	//Camera* cam = GetParent()->FindGameObject<Camera>();
	//if (cam != nullptr)
	//{
	//	x -= cam->GetValue();
	//}

	if (transform_.position_.y > GROUND + 20)
	{
		KillMe();
	}

	

	std::list<Magic*> pMagics = GetParent()->FindGameObjects<Magic>();
	for (Magic* pMagic : pMagics)
	{
		//����@����΂킩��Ǝv��������́wMagic�x�ƁwSlime�x�̋��������߂Ă���
		float dx = pMagic->GetPosition().x - (transform_.position_.x + 10.0f);//Mg�̍��WX - Sl�̍��WX
		float dy = pMagic->GetPosition().y - (transform_.position_.y + 10.0f);//Mg�̍��WY - Sl�̍��WY
		float distance = sqrt(dx * dx + dy * dy);//�����Ŗ��m�ȋ������v�Z

		if (distance <= 20.0f)
		{
			Damage* dam = Instantiate<Damage>(GetParent());
			dam->SetPosition(transform_.position_);
			KillMe();
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
	int spriteWidth = 256;
	int spriteHeight = 43;

	int frameX = animeFrame_ % 3; // ����3�̉摜�����邽��

	if (direction == -1)
	{
		DrawExtendGraph(x, y, x +64 * transform_.scale_.x, y + 64 * transform_.scale_.y, hImage, TRUE);
		
	}
	if (direction == 1)
	{
		DrawExtendGraph(x, y, x + 64* transform_.scale_.x, y + 64 * transform_.scale_.y, hImage, TRUE);
	}

	//Debug�p
	// 
	//DrawFormatString(0, 90, GetColor(255, 255, 255), "�X���C�����Ԃ�������: %d", direction);
	//DrawCircle(x + 32.0f * transform_.scale_.x, y + 32.0f * transform_.scale_.y, 32.0f * transform_.scale_.x, GetColor(255, 0, 0), FALSE);
	//DrawBox(rectX, rectY, rectX + rectW, rectY + rectH, GetColor(255, 0, 0), FALSE);
}

void Slime::WeatherEffects(Weather* weather)
{
	WeatherState WeatherState = weather->GetWeatherState();
	float WeatherEffect = weather->GetWeatherChange();

	RainScale(WeatherState, transform_, WeatherSpeed_, MOVE_SPEED, WeatherEffect, ScaleEffect_);

}

//
//bool Slime::ColliderCircle(float x, float y, float r)
//{
//	float CenterX = transform_.position_.x + 32.0f * transform_.scale_.x;
//	float CenterY = transform_.position_.y + 32.0f * transform_.scale_.y;
//	float dx = CenterX - x;
//	float dy = CenterY - y;
//	float dSqrts = dx * dx + dy * dy;
//
//	float myR = (32.0f + r) * transform_.scale_.x; // �X�P�[����K�p
//	float rSqrt = myR * myR;
//	//float rSqrt = sqrt(myR * myR);
//	if (dSqrts <= rSqrt)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

bool Slime::ColliderRect(float x, float y, float w, float h)
{
	// x,y,w,h������̋�`�̏��
	// �����̋�`�̏��
	float myX = transform_.position_.x;
	float myY = transform_.position_.y;
	float myW = 64.0f * transform_.scale_.x; 
	float myH = 64.0f * transform_.scale_.y; 

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
	if (state == Rainy)
	{
		WeatherSpeed_ = MOVE_SPEED * (1.0f - WeatherEffect); // �J�̓��͑��x������������

		
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

	if (state == Gale)
	{
		
			if (CheckHitKey(KEY_INPUT_RIGHT))
			{
				 transform_.position_.x += 4.0f;
				 Reverse_ = true;
				WindTimer_ = 300;
			}
			else if (CheckHitKey(KEY_INPUT_LEFT))
			{
				transform_.position_.x -= 4.0f;
				Reverse_ = false;
			}
			else if (CheckHitKeyAll(KEY_INPUT_UP))
			{
				transform_.position_.y -= 5.0f;
			}

	
		if (WindTimer_ > 0)
		{
			WindTimer_--;
		}

	}
	
}

