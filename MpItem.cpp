#include "MpItem.h"
#include "Camera.h"
#include "Player.h"
#include "Field.h"


MpItem::MpItem(GameObject* parent) :GameObject(parent, "MpItem"), hImage_(-1)
{
	hImage_ = LoadGraph("Assets/Item/Mp.png");
	assert(hImage_ > 0);

	transform_.position_.x = 200;
	transform_.position_.y = 560;
	flameCounter_ = 0;
	animeType_ = 0;
	animeFrame_ = 0;
}

MpItem::~MpItem()
{
	if (hImage_ > 0)
	{
		DeleteGraph(hImage_);
	}
}

void MpItem::Initialize()
{
}

void MpItem::Update()
{
	if (++flameCounter_ >= 24)
	{
		animeFrame_ = (animeFrame_ + 1) % 4;
		flameCounter_ = 0;
	}


	//std::list<Player*> pPlayers = GetParent()->FindGameObjects<Player>();
	//for (Player* pPlayer : pPlayers)
	//{
	//	//����@����΂킩��Ǝv��������́wPlayer�x�ƁwMpItem�x�̋��������߂Ă���
	//	float dx = pPlayer->GetPosition().x - (transform_.position_.x/* + 16.0f*/);//Mg�̍��WX - Gh�̍��WX
	//	float dy = pPlayer->GetPosition().y - (transform_.position_.y/* + 16.0f*/);//Mg�̍��WY - Gh�̍��WY
	//	float distance = sqrt(dx * dx + dy * dy);//�����Ŗ��m�ȋ������v�Z

	//	if (distance <= 30.0f)
	//	{
	//		KillMe();
	//		break;
	//	}
	//}

	//Field* pField = GetParent()->FindGameObject<Field>();
	////---------------�Փ˔���(��)--------------------------------
	//if (pField != nullptr)
	//{
	//	int pushR = pField->CollisionDown(transform_.position_.x + 50, transform_.position_.y + 63);
	//	int pushL = pField->CollisionDown(transform_.position_.x + 14, transform_.position_.y + 63);
	//	int push = max(pushR, pushL);//�Q�̑����̂߂肱�݂̑傫���ق�
	//	if (push >= 1)
	//	{
	//		transform_.position_.y -= push - 1;
	//	}

	//}
	////Instantiate<Heallten>(this);
	//if (Timer_ <= 0)
	//{
	//	KillMe();
	//	Timer_ = 180;
	//}

	//if (Timer_ > 0)
	//{
	//	Timer_--;
	//}
}

void MpItem::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	int SWidth = 512 / 4;
	int SHeight = 120;

	int frameX = animeFrame_ % 4;

	// �X�v���C�g��`��
	DrawRectGraph(x, y, frameX * SWidth, 0, SWidth, SHeight, hImage_, TRUE);
}

void MpItem::Release()
{

}

void MpItem::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

void MpItem::SetPosition(XMFLOAT3 pos)
{
	transform_.position_ = pos;
}

bool MpItem::ColliderCircle(float x, float y, float r)
{
	//x,y,r������̉~�̏��
	//�����̉~�̏��
	float myCenterX = transform_.position_.x + 64.0f;
	float myCenterY = transform_.position_.y + 64.0f;
	float myR = 20.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if (sqrt(dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}
