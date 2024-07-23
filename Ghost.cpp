#include "Ghost.h"
#include <assert.h>
#include "Camera.h"
#include "EnemyMagic.h"
#include "Magic.h"
#include "Damage.h"

namespace
{
	static const int SCREEN_WIDTH = 1280;
}

Ghost::Ghost(GameObject* scene)
{
	hImage_ = LoadGraph("Assets/Ghost.png");
	assert(hImage_ > 0);
	transform_.position_.x = 900.0f;
	transform_.position_.y = 780.0f;
	transform_.scale_.x = 2.0f;
	transform_.scale_.y = 2.0f;

	flameCounter_ = 0;
	animeType_ = 0;
	animeFrame_ = 0;
}

Ghost::~Ghost()
{
	if (hImage_ > 0)
	{
		DeleteGraph(hImage_);
	}
}

void Ghost::Update()
{
	Camera* cam = GetParent()->FindGameObject<Camera>();

	if (++flameCounter_ >= 24)
	{
		animeFrame_ = (animeFrame_ + 1) % 4;//if�����g��Ȃ��œK��
		flameCounter_ = 0;
	}

	if (cam != nullptr)
	{
		// �J�����̈ʒu���擾
		int camX = cam->GetValue();
		if (transform_.position_.x >= camX && transform_.position_.x <= camX + SCREEN_WIDTH)
		{
			if (CoolDownAttack_ <= 0)
			{
				EnemyMagic* emg = Instantiate<EnemyMagic>(GetParent());
				emg->SetPosition(transform_.position_);
				VECTOR dir = { -1.0f,0.0f };
				emg->SetDirection(dir);
				emg->SetSpeed(3.5f);


				CoolDownAttack_ = 300;
			}

			transform_.position_.y -= 1.0f;
			sinAngle += 3.0f;
			float sinValue = sinf(sinAngle * DX_PI_F / 180.0f);
			transform_.position_.y = 500.0f + sinValue * 50.0f;
		}
		
	}

	if (CoolDownAttack_ > 0)
	{
		CoolDownAttack_--;
	}

	int x = (int)transform_.position_.x;

	
	//if (cam != nullptr)
	//{
	//	x -= cam->GetValue();
	//}
	//if (x > SCREEN_WIDTH)//���l�A�}�W�b�N�i���o�[
	//	return;
	//else if (x < -64)
	//{
	//	KillMe();
	//	return;
	//}
	


	std::list<Magic*> pMagics = GetParent()->FindGameObjects<Magic>();
	for(Magic* pMagic : pMagics)
	{
		//����@����΂킩��Ǝv��������́wMagic�x�ƁwGhost�x�̋��������߂Ă���
		float dx = pMagic->GetPosition().x - (transform_.position_.x + 16.0f);//Mg�̍��WX - Gh�̍��WX
		float dy = pMagic->GetPosition().y - (transform_.position_.y + 16.0f);//Mg�̍��WY - Gh�̍��WY
		float distance = sqrt(dx * dx + dy * dy);//�����Ŗ��m�ȋ������v�Z

		if(distance <= 20.0f)
		{
		   KillMe();	
		   break;
		}
		
	}
}

void Ghost::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		x -= cam->GetValue();
	}
	//����͐��ʂ������Ă��炤�����ł�����ŁA��ԏ�̎O��̂݉�
	// �X�v���C�g�̃T�C�Y���v�Z
	int spriteWidth = 256 / 3;
	int spriteHeight = 344 / 4;

	int frameX = animeFrame_ % 3;

	// �X�v���C�g��`��
	DrawRectGraph(x, y, frameX * spriteWidth, 0, spriteWidth, spriteHeight, hImage_, TRUE);

	DrawCircle(x + spriteWidth / 2, y + spriteHeight / 2, 32.0f, GetColor(255, 0, 0), 0);
}

void Ghost::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

bool Ghost::ColliderCircle(float x, float y, float r)
{
	//x,y,r������̉~�̏��
	//�����̉~�̏��
	float myCenterX = transform_.position_.x + 32.0f;
	float myCenterY = transform_.position_.y + 32.0f;
	float myR = 30.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if (sqrt(dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}

//bool Ghost::ColliderRect(float x, float y, float w, float h)
//{
//	// x,y,w,h������̋�`�̏��
//	// �����̋�`�̏��
//	float myX = transform_.position_.x;
//	float myY = transform_.position_.y;
//	float myW = 64.0f * transform_.scale_.x;
//	float myH = 64.0f * transform_.scale_.y;
//
//	// ��`�̏Փ˔���
//	if (myX < x + w && myX + myW > x && myY < y + h && myY + myH > y)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
