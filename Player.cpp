#include "Player.h"
#include <DxLib.h>
#include <assert.h>
#include"Stone.h"
#include "Bird.h"
#include "Field.h"

namespace
{
	const float MOVE_SPEED = 2.5f;
	const float GROUND = 500.0f;
	const float JUMP_HEIGHT = 64.0f * 2.0f;
	const float GRAVITY = 9.8f / 60.0f;

};
Player::Player(GameObject* parent) : GameObject(sceneTop)
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

	if (state == S_Cry)
	{
		flameCounter++;
		if (flameCounter);
	}

	if (CheckHitKey(KEY_INPUT_D)|| CheckHitKey(KEY_INPUT_RIGHT))
	{
		transform_.position_.x += MOVE_SPEED;
		if (++flameCounter >= 8)
		{
			animFrame = (animFrame + 1) % 4;//if�����g��Ȃ��œK��
			flameCounter = 0;
		}
	}
	else if (CheckHitKey(KEY_INPUT_A)|| CheckHitKey(KEY_INPUT_LEFT))
	{
		transform_.position_.x -= MOVE_SPEED;
		if (++flameCounter >= 8)
		{
			animFrame = (animFrame + 1) % 4;//if�����g��Ȃ��œK��
			flameCounter = 0;
		}

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

	//-------------------+++�����̃v���O�����͊�b�̊�b+++-------------------

	Jump_P += GRAVITY; //���x += �����x
	transform_.position_.y += Jump_P; //���W += ���x

	if (transform_.position_.y >= GROUND)//�n�ʂɂ����瑬�x�����ɖ߂��A�߂��Ȃ��Ɗђʂ��鋰�ꂠ��
	{
		transform_.position_.y = GROUND;
		Jump_P = 0.0f;
		onGround = true;
	}

	//------------------------------------------------------------------------------------------

	if (CheckHitKey(KEY_INPUT_M))
	{
		Stone* st = Instantiate<Stone>(GetParent());
		st->SetPosition(transform_.position_);
	}

}

void Player::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	
	DrawRectGraph(x, y, animFrame * 64, animType * 64, 64, 64, hImage, TRUE);
}
