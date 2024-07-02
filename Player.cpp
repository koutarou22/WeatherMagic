#include <DxLib.h>
#include <assert.h>
#include"Weather.h"
#include "Player.h"
#include "Camera.h"
#include "Bird.h"
#include "Field.h"
#include "Time.h"
#include "Slime.h"
#include "HP.h" 
#include "Engine/SceneManager.h"
#include "Magic.h"

namespace
{
	const float MOVE_SPEED = 4.5f;
	const float GROUND = 600.0f;
	const float JUMP_HEIGHT = 64.0f * 1.45f;
    float GRAVITY = 9.8f / 60.0f;
};
Player::Player(GameObject* parent) : GameObject(sceneTop),WeatherSpeed_(MOVE_SPEED),Hp_(3), NDTIME_(1.0f)
{
	hImage = LoadGraph("Assets/magic.png");
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
	Weather* pWeather = GetParent()->FindGameObject<Weather>();
	std::list<Slime*> pSlimes = GetParent()->FindGameObjects<Slime>();
	Hp* hp = GetParent()->FindGameObject<Hp>();

	if (hp == nullptr) {
		
		return;
	}

	if (pWeather != nullptr)
	{
		WeatherEffects(pWeather); // �V��֐����Ăяo��
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
		else {
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
			// �V���؂�ւ���
			if (WeatherState == Sunny)//���ݐ���Ȃ�
			{
				pWeather->SetWeather(Rainy);//�J��
			}
			else if (WeatherState == Rainy)
			{
				pWeather->SetWeather(Gale);
			}
			else 
			{
				pWeather->SetWeather(Sunny);
			}
		}
		WeatherSwitch = true;
	}
	else
	{
		WeatherSwitch = false;
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
	    Magic* mg = Instantiate<Magic>(GetParent());
	    //mg->SetPosition(transform_.position_.x,transform_.position_.y);
	    mg->Setposition(transform_.position_);
	}

	Camera* cam = GetParent()->FindGameObject<Camera>();

	if (cam != nullptr) {
		cam->GetPlayerPos(this);
	}

	// ���G���Ԃ̍X�V
	if (NDTIME_ > 0.0f)
	{
		NDTIME_ -= 0.016f; 
	}
	//-----------------�X���C���Ƃ̐ڐG����-----------------------------
	for (Slime* pSlime : pSlimes)
	{
		Weather* pWeather = GetParent()->FindGameObject<Weather>();
		if (pSlime->ColliderRect(transform_.position_.x, transform_.position_.y, 64.0f, 64.0f))
		{
			Hp* hp = (Hp*)FindObject("Hp");
			if (transform_.position_.y + 64.0f <= pSlime->GetPosition().y + (64.0f * pSlime->GetScale().y) / 2) // �v���C���[���X���C���̏㕔�ɂ���
			{
				WeatherState WeatherState = pWeather->GetWeatherState();
				float RainBound = 0.5; // �J�̓��ɔ�������X���C���̒e��
				if (WeatherState == Rainy)
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
					Hp_--;
					if (Hp_ <= 0)
					{
						KillMe();
						//Hp_ = 3; // �O�̂��߃��Z�b�g
					}
					// �_���[�W���󂯂����莞�Ԗ��G�ɂȂ�
					NDTIME_ = 3.0f;
					if (transform_.position_.y > GROUND + 200)
					{
						KillMe();
					}
				}
				
			}
		}
	}
	//----------------------------------------------------------------------------------

	//���S������Q�[���I�[�o�[��ʂ�
	if (transform_.position_.y > GROUND || Hp_ == 0)
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
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

    // �ʏ�̕`�揈��...
    DrawRectGraph(x, y, animFrame * 64, animType * 64, 64, 64, hImage, TRUE);
	
	// �v���C���[�̍��W����ʂɕ\��
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "�v���C���[(�J����)�̈ʒu: (%d, %d)", x, y);
//	DrawFormatString(0, 20, GetColor(255, 255, 255), "Hp_: %d", Hp_);
	//DrawFormatString(0, 40, GetColor(255, 255, 255), "NDTIME_: %f", NDTIME_);
	DrawFormatString(1100, 5, GetColor(255, 255, 255), "N�L�[�œV��ω�");
}

void Player::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

void Player::WeatherEffects(Weather* weather)
{
	WeatherState WeatherState = weather->GetWeatherState();
	float WeatherEffect = weather->GetWeatherChange();

	if (WeatherState == Sunny)
	{
		WeatherSpeed_ = MOVE_SPEED;
	}
	else if (WeatherState == Rainy)
	{
		WeatherSpeed_ = MOVE_SPEED * (1.0f - WeatherEffect); 
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
