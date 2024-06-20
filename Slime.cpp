#include "Slime.h"
#include "Camera.h"
#include "Field.h"

namespace
{
	const float MOVE_SPEED = 2.5f;
	const float GROUND = 590.0f;
	const float JUMP_HEIGHT = 64.0f * 1.0f;
	const float GRAVITY = 9.8f / 60.0f;
	float horizontalSpeed;
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
	Field* pField = GetParent()->FindGameObject<Field>();
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		if (prevSpaceKey == false)
		{
			if (onGround)
			{
				// ���������̏����x��ݒ�
				horizontalSpeed = MOVE_SPEED;
				// �W�����v�J�n���̊p�x��0�Ƀ��Z�b�g
				sinAngle = 0.0f;
				onGround = false;
			}
		}
		prevSpaceKey = true;
	}
	else
	{
		prevSpaceKey = false;
	}

	// �W�����v���̏ꍇ�A�T�C���֐����g�p����Y���W���X�V
	if (!onGround)
	{
		// �T�C���֐��ɂ��Y���W�̌v�Z
		float sinValue = sinf(sinAngle * DX_PI_F / -180.0f);
		transform_.position_.y = 500.0f + sinValue * 50.0f;
		// �p�x�𑝉������邱�ƂŁA�T�C���֐��̒l��ω�������
		sinAngle += 3.0f;
		// ���������̍��W�̍X�V
		transform_.position_.x += horizontalSpeed;
	}

	// �n�ʂƂ̏Փ˔���
	if (pField != nullptr)
	{
		int pushR = pField->CollisionDown(transform_.position_.x + 50, transform_.position_.y + 63);
		int pushL = pField->CollisionDown(transform_.position_.x + 14, transform_.position_.y + 63);
		int push = max(pushR, pushL);
		if (push >= 1) {
			transform_.position_.y -= push - 1;
			onGround = true;
			// �n�ʂɒ��n�����琅�������̑��x�����Z�b�g
			horizontalSpeed = 0.0f;
		}
		else {
			onGround = false;
		}
	}

	Jump_P += GRAVITY; //���x += �����x
	transform_.position_.y += Jump_P; //���W += ���x


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
