#include "EnemyMagic.h"
#include <assert.h>
#include "Camera.h"
#include "Player.h"
#include "Debug.h"
#include "Ghost.h"

namespace
{
	const int BlockHalf = 32;//�u���b�N����
	const int InitializeTimer = 90;//�^�C�}�[���������̒l
	const int MagicSetValue = -2; //���@�̎ˏo�ʒu(�v���C���[�̈ʒu�ɉ��Z���Ē�������)
}

EnemyMagic::EnemyMagic(GameObject* scene) 
	: GameObject(scene), hEnemyMagic_(-1),timer_(0),direction_({0.0f,0.0f}),speed_(0.0f),
	prevPlPosX(-1),isDraw(false)
{
	Debug::OutPrint(L"���@��������", true);
	transform_.scale_.x = -2.0f;
	transform_.scale_.y = -2.0f;
	Ghost*  gh_ = GetParent()->FindGameObject<Ghost>();
	GhostPos_ = gh_->GetPosition();
}

EnemyMagic::~EnemyMagic()
{
	/*Release();*/
}

void EnemyMagic::Update()
{
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		if (isDraw)
		{
			transform_.position_.x += direction_.x * speed_;
			transform_.position_.y += direction_.y * speed_;
		}
		if (--timer_ <= 0)
		{
			//�^�C�}�[��0��菬�����Ƃ��`�悵�Ȃ��A�����W���S�[�X�g��
			isDraw = false;
			transform_.position_ = GhostPos_;
		}
	}
}

void EnemyMagic::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	if (isDraw)
	{
		DrawGraph(x, y, hEnemyMagic_, TRUE);
	}
}

void EnemyMagic::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
	timer_ = InitializeTimer;
	isDraw = true;
}

void EnemyMagic::SetPosition(XMFLOAT3 pos)
{
	transform_.position_ = pos;
	timer_ = InitializeTimer;
	isDraw = true;
}

bool EnemyMagic::ColliderCircle(float x, float y, float r)
{
	//x,y,r������̉~�̏��
	//�����̉~�̏��
	float myCenterX = transform_.position_.x + 32.0f;
	float myCenterY = transform_.position_.y + 32.0f;
	float myR = 24.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if (sqrt(dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}

void EnemyMagic::LoadMagicImage()
{
	hEnemyMagic_ = LoadGraph("Assets/Chara/EnemyMagic_F.png");
	assert(hEnemyMagic_ > 0);
}

void EnemyMagic::Release()
{
	if (hEnemyMagic_ > 0)
	{
		DeleteGraph(hEnemyMagic_);
		Debug::OutPrint(L"���@�̉���͐������Ă΂ꂽEnemyMagic.cpp", true);
		hEnemyMagic_ = 0;
	}
}
