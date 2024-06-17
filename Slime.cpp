#include "Slime.h"
#include "Camera.h"

namespace
{
	const float MOVE_SPEED = 2.5f;
	const float GROUND = 590.0f;
	const float JUMP_HEIGHT = 64.0f * 1.0f;
	const float GRAVITY = 9.8f / 60.0f;
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
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		//PictFlame = 80;

		//animFrame = (animFrame + 1) % 4;
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

	Jump_P += GRAVITY; //���x += �����x
	transform_.position_.y -= Jump_P; //���W += ���x
	transform_.position_.x -= Jump_P;
	if (transform_.position_.y >= GROUND)//�n�ʂɂ����瑬�x�����ɖ߂��A�߂��Ȃ��Ɗђʂ��鋰�ꂠ��
	{
		transform_.position_.y = GROUND;
		Jump_P = 0.0f;
		onGround = true;
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
