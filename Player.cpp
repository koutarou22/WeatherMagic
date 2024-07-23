#include <DxLib.h>
#include <assert.h>
#include"Weather.h"
#include "Player.h"
#include "Camera.h"
#include "Field.h"
#include "Slime.h"
#include "HP.h" 
#include "Engine/SceneManager.h"
#include "Magic.h"
#include "Ghost.h"
#include "EnemyMagic.h"
#include "Damage.h"
#include "HealItem.h"
#include "MpItem.h"
#include "Rock.h"
#include <iostream>

namespace
{
	const float MOVE_SPEED = 4.5f;
	const float GROUND = 600.0f;
	const float JUMP_HEIGHT = 64.0f * 1.45f;
    float GRAVITY = 9.8f / 60.0f;
	const int MAX_MAGIC_POINT = 20;
	const int MAX_DAMAGE_HP = 5;
	
 
};
Player::Player(GameObject* parent) : GameObject(sceneTop), WeatherSpeed_(MOVE_SPEED), Hp_(3), NDTIME_(2.0f), Flash_Count(0), IsHitOneCount_(false),DebugLog_(false)
{
	hImage = LoadGraph("Assets/magic.png");
	assert(hImage > 0);
	transform_.position_.x = 100.0f;
	transform_.position_.y = GROUND;
	onGround = true;
	flameCounter = 0;
	animType = 0;
	animFrame = 0;

	Hp_ = 5;

	MagicPoint_ = 10;

	Hp_GetFlag = false;
	Hp_GetFlag = false;
	StringUi_Up = transform_.position_.y;
	
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
	Weather* pWeather = GetParent()->FindGameObject<Weather>();
	std::list<Slime*> pSlimes = GetParent()->FindGameObjects<Slime>();
	Rock* pRock = GetParent()->FindGameObject<Rock>();

	Hp* hp = GetParent()->FindGameObject<Hp>();

	SetFontSize(20);


	if (hp == nullptr) 
	{
		return;
	}

	if (pWeather != nullptr)
	{
		WeatherEffects(pWeather); // �V��֐����Ăяo��
	}

	//��ʊO�ɍs���Ȃ��悤�ɂ��鏈��
	if (transform_.position_.x < 0)
	{
		transform_.position_.x = 0;
	}
	if (Jump_P > 20.0f) {
		Jump_P = 20.0f; // �������x���ő�l�𒴂��Ȃ��悤�ɐ���
	}


	/*if (state == S_Cry)
	{
		flameCounter++;
		if (flameCounter);
	}*/

	if (CheckHitKey(KEY_INPUT_D) /*|| CheckHitKey(KEY_INPUT_RIGHT)*/)
	{
		transform_.position_.x += WeatherSpeed_;
		//if (++flameCounter >= 8)
		//{
		//	animFrame = (animFrame + 1) % 4;//if�����g��Ȃ��œK��
		//	flameCounter = 0;
		//}

		//---------------�Փ˔���(�E)--------------------------------
		hitX = transform_.position_.x + 50;
		hitY = transform_.position_.y + 63;


		if (pField != nullptr)
		{
			int push = pField->CollisionRight(hitX, hitY);
			transform_.position_.x -= push;
			
		}
		//----------------------------------------------------------
	}
	else if (CheckHitKey(KEY_INPUT_A) /*|| CheckHitKey(KEY_INPUT_LEFT)*/)
	{

		transform_.position_.x -= WeatherSpeed_;
		//if (++flameCounter >= 8)
		//{
		//	animFrame = (animFrame + 1) % 4;//if�����g��Ȃ��œK��
		//	flameCounter = 0;

		//}

		//---------------�Փ˔���(��)--------------------------------
		hitX = transform_.position_.x;
		hitY = transform_.position_.y + 63; // �v���C���[�̑�����Y���W
		if (pField != nullptr)
		{
			int push = pField->CollisionLeft(hitX, hitY);
			transform_.position_.x += push;
			
		}
		//-----------------------------------------------------------
	}
	//else
	//{
	//	animFrame = 0;
	//	flameCounter = 0;
	//}


	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		PictFlame = 80;

		/*animFrame = (animFrame + 1) % 4;*/
		if (prevSpaceKey == false)
		{
			if (onGround)
			{
				Jump();
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
		int pushR = pField->CollisionDown(transform_.position_.x + 50, transform_.position_.y + 63);
		int pushL = pField->CollisionDown(transform_.position_.x + 14, transform_.position_.y + 63);
		int push = max(pushR, pushL);//�Q�̑����̂߂肱�݂̑傫���ق�
		if (push >= 1)
		{
			transform_.position_.y -= push - 1;
			Jump_P = 0.0f;
			onGround = true;
		}
		else 
		{
			onGround = false;
		}
	}
	//-----------------------------------------------------------

	if (CheckHitKey(KEY_INPUT_N))
	{
		if (!WeatherSwitch && pWeather != nullptr)
		{
			// ���݂̓V���Ԃ��擾
			WeatherState WeatherState = pWeather->GetWeatherState();
			// ���ɐ؂�ւ���V�������
			if (WeatherState == Sunny)//���ݐ���Ȃ�
			{
				pWeather->SetWeather(Rainy);//���͉J��
			}
			else if (WeatherState == Rainy)
			{
				pWeather->SetWeather(Gale);//���͋�����
			}
			else
			{
				pWeather->SetWeather(Sunny);//���͐����
			}
			WeatherTime_= 60; 
		}
		WeatherSwitch = true;
	}
	else
	{
		WeatherSwitch = false;
	}


	if (pWeather != nullptr && pWeather->GetWeatherState() == Gale)
	{
		if ((CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_LEFT)) && GaleTime_ <= 0)
		{
			if(MagicPoint_ >= 4)
			MagicDown(4); 
			GaleTime_ = 300;
		}
	}

	if (GaleTime_ > 0)
	{
		GaleTime_--;
	}

	if (pWeather != nullptr && pWeather->GetWeatherState() == Rainy)
	{
		if (RainTime_ <= 0)
		{
			if (MagicPoint_ > 0)
			{
				MagicDown(1);
				RainTime_ = 420;
			}
		}
	}

	if (RainTime_ > 0)
	{
		RainTime_--;
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
		if (CoolDownMagic_ <= 0 && MagicPoint_ > 0)
		{
			Magic* mg = Instantiate<Magic>(GetParent());
			//mg->SetPosition(transform_.position_.x,transform_.position_.y);
			mg->SetPosition(transform_.position_);
			VECTOR dir = { 1.0f, 0.0f };
			mg->SetDirection(dir);
			mg->SetSpeed(5.5f);
			CoolDownMagic_ = timer_;
			MagicPoint_--;
		}
	}
	if (CoolDownMagic_ > 0)
	{
		CoolDownMagic_--;
	}

	
	// ���G���Ԃ̍X�V
	if (NDTIME_ > 0.0f)
	{
		NDTIME_ -= 0.016f;
	}

	////-----------------�X���C���Ƃ̐ڐG����-----------------------------
	for (Slime* pSlime : pSlimes)
	{
		if (pSlime->ColliderRect(transform_.position_.x, transform_.position_.y, 64.0f, 64.0f))
		{
			if (transform_.position_.y + 64.0f <= pSlime->GetPosition().y + (64.0f * pSlime->GetScale().y) / 2) // �v���C���[���X���C���̏㕔�ɂ���
			{
				WeatherState WeatherState = pWeather->GetWeatherState();
				float RainBound = 0.5; // �J�̓��ɔ�������X���C���̒e��
				if (WeatherState == Rainy && MagicPoint_ > 0)
				{
					RainBound = 3.5f; // �J�̎��̂݃W�����v�͂�2.5�{
				}
				Jump_P = -sqrtf(2 * GRAVITY * JUMP_HEIGHT * RainBound);
				onGround = false;
			}
			else
			{
				if (NDTIME_ <= 0.0f)
				{
					hp->DamageHp();
					HpDown(1);
					if (Hp_ <= 0)
					{
						KillMe();
					}
					if (Hp_ > 3)
					{
						HpDown(1);
					}

					NDTIME_ = 3.0f;
					break; // �_���[�W��^������Ƀ��[�v�𔲂���
				}
			}
		}
	}


		//Damage* pDamage = GetParent()->FindGameObject<Damage>();
		//�J�����̏���
		Camera* cam = GetParent()->FindGameObject<Camera>();
		int xR = (int)transform_.position_.x - cam->GetValue();
		int xL = (int)transform_.position_.x + cam->GetValue();
		if (xR > 600)
		{
			xR = 600;
			cam->SetValue((int)transform_.position_.x - xR);
		}

		if (xL > 600)
		{
			xL = 600;
			cam->SetValue((int)transform_.position_.x - xL);
		}

		//----------------------------------------------------------------------------------

		//2�_�Ԃ̋����֗̕�����g�ɐ��݂Ď������܂���
		std::list<EnemyMagic*> pEMagics = GetParent()->FindGameObjects<EnemyMagic>();
		for (EnemyMagic* pEnemyMagic : pEMagics)
		{
			//����@����΂킩��Ǝv��������́wEnemyMagic�x�ƁwSlime�x�̋��������߂Ă���
			float dx = pEnemyMagic->GetPosition().x - (transform_.position_.x + 32.0f);//Mg�̍��WX - Sl�̍��WX
			float dy = pEnemyMagic->GetPosition().y - (transform_.position_.y + 32.0f);//Mg�̍��WY - Sl�̍��WY
			float distance = sqrt(dx * dx + dy * dy);//�����Ŗ��m�ȋ������v�Z

			if (distance <= 20.0f)
			{
				if (NDTIME_ <= 0.0f)
				{
					
					hp->DamageHp();
					HpDown(1);

					if (Hp_ <= 0)
					{
						KillMe();
						break;
					}

					NDTIME_ = 2.0f;//�X�̐��l�Ŗ��G���Ԃ����܂�
				}
				break;
			}
		}

		std::list<Ghost*> pGhosts = GetParent()->FindGameObjects<Ghost>();
		for (Ghost* pGhost : pGhosts)
		{
			float dx = pGhost->GetPosition().x - (transform_.position_.x /*+ 32.0f*/);
			float dy = pGhost->GetPosition().y - (transform_.position_.y /*+ 32.0f*/);

			float distance = sqrt(dx * dx + dy * dy);

			if (distance <= 40.0f)
			{
				if (NDTIME_ <= 0.0f)
				{
					hp->DamageHp();
					HpDown(1);
					if (Hp_ <= 0)
					{
						KillMe();
						break;
					}

					NDTIME_ = 3.0f;
				}
				break;
			}
		}

		std::list<HealItem*> pHeals = GetParent()->FindGameObjects<HealItem>();
		for (HealItem* pHeal : pHeals)
		{
			float dx = pHeal->GetPosition().x - (transform_.position_.x /*+ 32.0f*/);
			float dy = pHeal->GetPosition().y - (transform_.position_.y/* + 32.0f*/);

			float distance = sqrt(dx * dx + dy * dy);

			if (distance <= 20.0f)
			{
				Hp_GetFlag = true;
				if (Hp_ < 5) 
				{
					hp->HeelHp();
					Hp_++;
				}
				pHeal->KillMe();
				Hp_GetFlag = true;
				UIGetTimer = 60;
				StringUi_Up = transform_.position_.y;
				break;
			}
			
		}


		std::list<MpItem*> pMps = GetParent()->FindGameObjects<MpItem>();
		for (MpItem* pMp : pMps)
		{
			float dx = pMp->GetPosition().x - (transform_.position_.x /*+ 32.0f*/);
			float dy = pMp->GetPosition().y - (transform_.position_.y /*+ 32.0f*/);

			float distance = sqrt(dx * dx + dy * dy);

			if (distance <= 30.0f)
			{
				if (!IsHitOneCount_) // �A�C�e�����E�����Ƃ��Ɉ�x����MagicPoint_�𑝂₷
				{
					MagicUp(5);
					IsHitOneCount_ = true; // MagicPoint_�𑝂₵�����IsHitOneCount_��true�ɐݒ�
				}
				pMp->KillMe();
				Mp_GetFlag = true;
				UIGetTimer = 60;
				StringUi_Up = transform_.position_.y;
			}
			else
			{
				IsHitOneCount_ = false; // �A�C�e�����͈͊O�ɂȂ�����IsHitOneCount_��false�Ƀ��Z�b�g
			}
		}

		std::list<Rock*> pRocks = GetParent()->FindGameObjects<Rock>();
		for (Rock* pRock : pRocks)
		{
			float dx = pRock->GetPosition().x + 32 - (transform_.position_.x + 32.0f);
			float dy = pRock->GetPosition().y + 32 - (transform_.position_.y + 32.0f);

			float distance = sqrt(dx * dx + dy * dy);

			if (distance <= 60.0f)
			{
				//<= 32.0f�̈Ӗ��͉��Ƃ̐ڐG�̕��𐧌����Ă���
				if (dy < 0 && abs(dx) <= 32.0f) //��̏�ɏ��
				{
					transform_.position_.y = pRock->GetPosition().y - 64; // �v���C���[����Ɉړ�
					WeatherSpeed_ = 0;
					onGround = true;
				}
				else if (dy > 0 && abs(dx) <= 32.0f) //��̉��ɂԂ���
				{
					int push = 3;
					transform_.position_.y = pRock->GetPosition().y + push; // �v���C���[�����Ɉړ�
					WeatherSpeed_ = MOVE_SPEED;
				}
				else if (dx < 0) // ��̉E���̏Փ˔���
				{
					int push = 1;
					transform_.position_.x += push; // �v���C���[���E�Ɉړ�
				}
				else if (dx > 0) // ��̍����̏Փ˔���
				{
					int push = 1;
					transform_.position_.x -= push; // �v���C���[�����Ɉړ�
				}
			}
		}

		//���S������Q�[���I�[�o�[��ʂ�
		if (transform_.position_.y > GROUND || Hp_ == 0)
		{
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
		}
		//����̃^�C���ɐG�ꂽ��N���AScene��
		if (pField != nullptr)
		{
			int playerX = (int)transform_.position_.x;
			int playerY = (int)transform_.position_.y;

			if (pField->IsHitClear(playerX, playerY))
			{
				SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
				pSceneManager->ChangeScene(SCENE_ID_CLEAR);
			}
		}

	if (CheckHitKey(KEY_INPUT_Q))
	{
		DebugLog_ = true;
	}
	else
	{
		DebugLog_ = false;
	}
}

void Player::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	int displayY = y - 30;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue(); 
	}
	
	if (NDTIME_ <= 0.0f)
	{
		DrawRectGraph(x, y, animFrame * 64, animType * 64, 64, 64, hImage, TRUE);
	}
	else
	{
		if (Flash_Count % 24 == 0)
		{
			DrawRectGraph(x, y, animFrame * 64, animType * 64, 64, 64, hImage, TRUE);
		}
	}
	
	++Flash_Count;
	

	if (Mp_GetFlag == true)
	{
		if (UIGetTimer > 0)
		{
			DrawFormatString(x, StringUi_Up, GetColor(255, 255, 255), "MP+5");
			StringUi_Up -= 1;
			UIGetTimer--;
		}
		else
		{
			Mp_GetFlag = false;
		}
	}

	if (Hp_GetFlag == true)
	{
		if (UIGetTimer > 0)
		{
			SetFontSize(24);
			DrawFormatString(x, StringUi_Up, GetColor(255, 255, 255), "Hp+2");

			SetFontSize(20);
			StringUi_Up -= 1;
			UIGetTimer--;
		}
		else
		{
			Hp_GetFlag = false;
		}
	}

	DrawFormatString(100, 60, GetColor(30, 144, 255), "UI:%d", UIGetTimer);//����ȊO�Ȃ��
	if (MagicPoint_ == 0)
	{
		DrawFormatString(0, 60, GetColor(255, 69, 0), "Mp: %d /20", MagicPoint_);//0�Ȃ�Ԃ�
	}
	else
	{
		DrawFormatString(0, 60, GetColor(30, 144, 255), "Mp: %d /20", MagicPoint_);//����ȊO�Ȃ��
	}

	if (DebugLog_ == false)
	{

	}
	else if(DebugLog_ == true)
	{
		
	//	DrawFormatString(1100, 5, GetColor(0, 0, 0), "N�L�[�œV��ω�");

		DrawFormatString(960, 0, GetColor(0, 0, 0), "�v���C���[(�J����)�̈ʒu: (%d, %d)", x, y);
		DrawFormatString(1100, 40, GetColor(255, 69, 0), "����HP: %d", Hp_);
		DrawFormatString(1100, 60, GetColor(255, 215, 0), "���G����: %f", NDTIME_);
		
		DrawFormatString(1100, 80, GetColor(46, 139, 87), "�n�ʔ���:%d", onGround);
	}

}

void Player::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

void Player::WeatherEffects (Weather* weather)
{
	WeatherState WeatherState = weather->GetWeatherState();
	float WeatherEffect = weather->GetWeatherChange();
	//Buffs*pBuff = GetParent()->FindGameObject<Buffs>();

	if (WeatherState == Sunny)
	{
		WeatherSpeed_ = MOVE_SPEED;
	}
	else if (WeatherState == Rainy)
	{
		if (MagicPoint_ > 0)
		{
			WeatherSpeed_ = MOVE_SPEED * (1.0f - WeatherEffect);
		}
		else
		{
			WeatherSpeed_ = MOVE_SPEED;
		}
	}
	else if (WeatherState == Gale)
	{
		WeatherSpeed_ = MOVE_SPEED;
	}
	
}

void Player::Jump()
{
	Jump_P = -sqrtf(2 * GRAVITY * JUMP_HEIGHT + WeatherSpeed_ ); // �v���C���[���W�����v������
	onGround = false;
}

int Player::GetHp()
{
 	return Hp_;
}

void Player::MagicUp(int _PMp)
{
	MagicPoint_ += _PMp;
	
	if (MagicPoint_ > MAX_MAGIC_POINT)
	{
		MagicPoint_ = MAX_MAGIC_POINT;
	}
}

void Player::MagicDown(int _MMp)
{
	MagicPoint_ -= _MMp;

	if (MagicPoint_ < 0)
	{
		MagicPoint_ = 0;
	}
}

void Player::HpUp(int _PHp)
{
	Hp_ += _PHp;

	if (Hp_ < MAX_DAMAGE_HP)
	{
		Hp_ > MAX_DAMAGE_HP;
	}
}

void Player::HpDown(int _MHp)
{
	Hp_ -= _MHp;
}

