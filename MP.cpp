#include "MP.h"
#include"Player.h"
MP::MP(GameObject* parent)
{
	MPgaugeCrrVal_ = 100;
	MPgaugeMaxVal_ = 100;
	trs.position_.x = -270;
	trs.position_.y = 60;
}

void MP::Initialize()
{
	hMPBar_ = LoadGraph("Assets/UI/MP.png");
	assert(hMPBar_);

	hMPFrame_ = LoadGraph("Assets/UI/MPFrame.png");
	assert(hMPFrame_);
}

void MP::Update()
{
	
	trs.scale_.x =(float)MPgaugeCrrVal_/(float)MPgaugeMaxVal_ ;
	//MPŒ¸‚é‚Ì‚ª‚í‚©‚è‚â‚·‚­Œ©‚¦‚éŒã‚ÅÁ‚·
	/*if (CheckHitKey(KEY_INPUT_P))
	{
		MPgaugeCrrVal_--;
	}*/
}

void MP::Draw()
{
	Player* player = GetParent()->FindGameObject<Player>();
	//DrawGraph(-265, 50, hMPBar_, TRUE);
	if (player != nullptr && player->GetMp() > 0)
	{
		
		DrawExtendGraph(trs.position_.x, trs.position_.y,
		240*trs.scale_.x,trs.position_.y+60*trs.scale_.y, hMPBar_, TRUE);
	}
	DrawGraph(-265, 60, hMPFrame_, TRUE);
}

void MP::Release()
{
	DeleteGraph(hMPFrame_);
	DeleteGraph(hMPBar_);
}
