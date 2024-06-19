#include <DxLib.h>
#include <assert.h>
#include "Player.h"
#include "Stone.h"
#include "Camera.h"
#include "Bird.h"
#include "Field.h"

namespace
{
	const float MOVE_SPEED = 4.5f;
	const float GROUND = 600.0f;
	const float JUMP_HEIGHT = 64.0f * 3.0f;
	const float GRAVITY = 9.8f / 60.0f;

	int hitX;
	int hitY;

	

	int DebugPush;
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
	    hitX = transform_.position_.x + 50;
	    hitY = transform_.position_.y + 63;

		if (pField != nullptr)
		{
			int push = pField->CollisionRight(hitX, hitY);

			DebugPush = push;
			transform_.position_.x -= push;
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

		hitX = transform_.position_.x;
	    hitY = transform_.position_.y + 63; // �v���C���[�̑�����Y���W
		if (pField != nullptr)
		{
			int push = pField->CollisionLeft(hitX, hitY);
			transform_.position_.x += push; 
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

	if (pField != nullptr)
	{
		int pushR = pField->CollisionDown(transform_.position_.x + 50, transform_.position_.y + 63);
		int pushL = pField->CollisionDown(transform_.position_.x + 14, transform_.position_.y + 63);
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
	//�g�����͂Ȃ�
	//if (transform_.position_.y >= GROUND)//�n�ʂɂ����瑬�x�����ɖ߂��A�߂��Ȃ��Ɗђʂ��鋰�ꂠ��
	//{
	//	transform_.position_.y = GROUND;
	//	Jump_P = 0.0f;
	//	onGround = true;
	//}

	//------------------------------------------------------------------------------------------

	if (CheckHitKey(KEY_INPUT_M))
	{
		Stone* st = Instantiate<Stone>(GetParent());
		st->SetPosition(transform_.position_);
	}
	Camera* cam = GetParent()->FindGameObject<Camera>();
	
	if (cam != nullptr) {
		cam->GetPlayerPos(this);
	}
}

void Player::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue(); 
	}

	DrawRectGraph(x, y, animFrame * 64, animType * 64, 64, 64, hImage, TRUE);
	// �v���C���[�̍��W����ʂɕ\��
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�v���C���[(�J����)�̈ʒu: (%d, %d)", x, y);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "Push���ꂽ�l: %d", DebugPush);
	
}

void Player::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}
