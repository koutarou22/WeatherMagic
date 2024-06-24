#include "Slime.h"
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
Slime::Slime(GameObject* parent, float x, float y): GameObject(parent, "Slime")
{
	this->x = x;
	this->y = y;
}
Slime::Slime(GameObject* scene)
{
	hImage = LoadGraph("Assets/slime.png");
	assert(hImage > 0);
	transform_.position_.x = 500.0f;
	transform_.position_.y = 600.0f;
	
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

	transform_.position_.x += WeatherSpeed_ * direction;

	// �Փ˔���Ɣ��]�t���O�̐ݒ�
	if (pField->CollisionLeft(hitX, hitY) && direction == -1)
	{
		Reverse_ = true;
	}
	else if (pField->CollisionRight(hitX, hitY) && direction == 1)
	{
		Reverse_ = true;
	}

	// ���]�t���O�������Ă���ꍇ�A�ړ������𔽓]
	if (Reverse_)
	{
		direction *= -1;
		Reverse_ = false;
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

	//if (CheckHitKey(KEY_INPUT_SPACE))
	//{
	//	
	//	if (prevSpaceKey == false)
	//	{
	//		if (onGround)
	//		{
	//			Jump_P = -sqrtf(2 * GRAVITY * JUMP_HEIGHT);
	//			onGround = false;
	//		}
	//	}
	//	prevSpaceKey = true;
	//}
	//else
	//{
	//	prevSpaceKey = false;
	//}

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

    DrawExtendGraph(x, y, x + 64 * transform_.scale_.x, y + 64 * transform_.scale_.y, hImage, TRUE);

	DrawFormatString(0, 90, GetColor(255, 255, 255), "�X���C�����Ԃ�������: %d", direction);
	DrawCircle(x + 32.0f * transform_.scale_.x, y + 32.0f * transform_.scale_.y, 32.0f * transform_.scale_.x, GetColor(255, 0, 0), FALSE);
	//DrawBox(rectX, rectY, rectX + rectW, rectY + rectH, GetColor(255, 0, 0), FALSE);
}

void Slime::WeatherEffects(Weather* weather)
{
	WeatherState WeatherState = weather->GetWeatherState();
	float WeatherEffect = weather->GetWeatherChange();

	if (WeatherState == Rainy)
	{
		WeatherSpeed_ = MOVE_SPEED * (1.0f - WeatherEffect); // �J�̓��͑��x������������

		// �X���C���̃X�P�[����1.5�{�����̏ꍇ�A�X�P�[�������X�ɑ���������
		if (transform_.scale_.x < 1.5f) {
			float prev_scale = transform_.scale_.x;
			transform_.scale_.x += 0.01f; // x�����̃X�P�[�������X�ɑ���������
			transform_.position_.y -= (transform_.scale_.x - prev_scale) * 32; // �ʒu����Ɉړ�
		}
		if (transform_.scale_.y < 1.5f) {
			float prev_scale = transform_.scale_.y;
			transform_.scale_.y += 0.01f; // y�����̃X�P�[�������X�ɑ���������
			transform_.position_.y -= (transform_.scale_.y - prev_scale) * 32; // �ʒu����Ɉړ�
		}
	}
	else
	{
		WeatherSpeed_ = MOVE_SPEED; // �ʏ�̑��x
		// �X���C���̃X�P�[����1.0���傫���ꍇ�A�X�P�[�������X�Ɍ���������
		if (transform_.scale_.x > 1.0f) {
			float prev_scale = transform_.scale_.x;
			transform_.scale_.x -= 0.01f; // x�����̃X�P�[�������X�Ɍ���������
			transform_.position_.y += (prev_scale - transform_.scale_.x) * 32; // �ʒu�����Ɉړ�
		}
		if (transform_.scale_.y > 1.0f) {
			float prev_scale = transform_.scale_.y;
			transform_.scale_.y -= 0.01f; // y�����̃X�P�[�������X�Ɍ���������
			transform_.position_.y += (prev_scale - transform_.scale_.y) * 32; // �ʒu�����Ɉړ�
		}
	}
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
	float myW = 64.0f * transform_.scale_.x; // �X�P�[����K�p
	float myH = 64.0f * transform_.scale_.y; // �X�P�[����K�p

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

