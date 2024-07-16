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
#include "Ghost.h"
#include "EnemyMagic.h"
#include "Damage.h"
#include "HealItem.h"
#include "Buffs.h"
#include "MpItem.h"

namespace
{
	const float MOVE_SPEED = 4.5f;
	const float GROUND = 600.0f;
	const float JUMP_HEIGHT = 64.0f * 1.45f;
    float GRAVITY = 9.8f / 60.0f;
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


	MagicPoint_ = 0;
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

	rect.x = transform_.position_.x;
	rect.y = transform_.position_.y;
	rect.w = 64 * 2;  // 画像の幅を二倍に
	rect.h = 64 * 2;  // 画像の高さを二倍に

	Field* pField = GetParent()->FindGameObject<Field>();
	Weather* pWeather = GetParent()->FindGameObject<Weather>();
	std::list<Slime*> pSlimes = GetParent()->FindGameObjects<Slime>();
	Hp* hp = GetParent()->FindGameObject<Hp>();

	if (hp == nullptr) {
		
		return;
	}

	if (pWeather != nullptr)
	{
		WeatherEffects(pWeather); // 天候関数を呼び出す
	}

	//画面外に行かないようにする処理
	if (transform_.position_.x < 0)
	{
		transform_.position_.x = 0;
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
		//	animFrame = (animFrame + 1) % 4;//if文を使わない最適解
		//	flameCounter = 0;
		//}

		//---------------衝突判定(右)--------------------------------
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
		//	animFrame = (animFrame + 1) % 4;//if文を使わない最適解
		//	flameCounter = 0;

		//}

		//---------------衝突判定(左)--------------------------------
		hitX = transform_.position_.x;
		hitY = transform_.position_.y + 63; // プレイヤーの足元のY座標
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

	//-------------------+++加速のプログラムは基礎の基礎+++-------------------

	Jump_P += GRAVITY; //速度 += 加速度
	transform_.position_.y += Jump_P; //座標 += 速度

	//---------------衝突判定(上)--------------------------------
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

	
	//---------------衝突判定(下)--------------------------------
	if (pField != nullptr)
	{
		int pushR = pField->CollisionDown(transform_.position_.x + 50, transform_.position_.y + 63);
		int pushL = pField->CollisionDown(transform_.position_.x + 14, transform_.position_.y + 63);
		int push = max(pushR, pushL);//２つの足元のめりこみの大きいほう
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
			// 現在の天候状態を取得
			WeatherState WeatherState = pWeather->GetWeatherState();
			// 次に切り替える天候を決定
			if (WeatherState == Sunny)//現在晴れなら
			{
				pWeather->SetWeather(Rainy);//次は雨に
			}
			else if (WeatherState == Rainy)
			{
				pWeather->SetWeather(Gale);//次は強風に
			}
			else
			{
				pWeather->SetWeather(Sunny);//次は晴れに
			}
			WeatherTime_= 60; 
		}
		WeatherSwitch = true;
	}
	else
	{
		WeatherSwitch = false;
	}



	//拡張性はない
	//if (transform_.position_.y >= GROUND)//地面についたら速度を元に戻す、戻さないと貫通する恐れあり
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

	
	// 無敵時間の更新
	if (NDTIME_ > 0.0f)
	{
		NDTIME_ -= 0.016f;
	}

	////-----------------スライムとの接触判定-----------------------------
	for (Slime* pSlime : pSlimes)
	{
		if (pSlime->ColliderRect(transform_.position_.x, transform_.position_.y, 64.0f, 64.0f))
		{
			if (transform_.position_.y + 64.0f <= pSlime->GetPosition().y + (64.0f * pSlime->GetScale().y) / 2) // プレイヤーがスライムの上部にある
			{
				WeatherState WeatherState = pWeather->GetWeatherState();
				float RainBound = 0.5; // 雨の日に発生するスライムの弾性
				if (WeatherState == Rainy)
				{
					RainBound = 3.5f; // 雨の時のみジャンプ力を2.5倍
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
					}
					if (Hp_ > 3)
					{
						Hp_--;
					}
					
					NDTIME_ = 3.0f;
				}
			}
		}

		Damage* pDamage = GetParent()->FindGameObject<Damage>();
		//カメラの処理
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

		//2点間の距離の便利さを身に染みて実感しました
		std::list<EnemyMagic*> pEMagics = GetParent()->FindGameObjects<EnemyMagic>();
		for (EnemyMagic* pEnemyMagic : pEMagics)
		{
			//解説　見ればわかると思うがこれは『EnemyMagic』と『Slime』の距離を求めている
			float dx = pEnemyMagic->GetPosition().x - (transform_.position_.x + 12.0f);//Mgの座標X - Slの座標X
			float dy = pEnemyMagic->GetPosition().y - (transform_.position_.y + 12.0f);//Mgの座標Y - Slの座標Y
			float distance = sqrt(dx * dx + dy * dy);//ここで明確な距離を計算

			if (distance <= 20.0f)
			{
				if (NDTIME_ <= 0.0f)
				{
					
					hp->DamageHp();
					Hp_--;

					if (Hp_ <= 0)
					{
						KillMe();
						break;
					}

					NDTIME_ = 2.0f;//個々の数値で無敵時間がきまる
				}
				break;
			}
		}

		std::list<Ghost*> pGhosts = GetParent()->FindGameObjects<Ghost>();
		for (Ghost* pGhost : pGhosts)
		{
			float dx = pGhost->GetPosition().x - (transform_.position_.x + 10.0f);
			float dy = pGhost->GetPosition().y - (transform_.position_.y + 10.0f);

			float distance = sqrt(dx * dx + dy + dy);

			if (distance <= 10.0f)
			{
				if (NDTIME_ <= 0.0f)
				{
					hp->DamageHp();
					Hp_--;
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
			float dx = pHeal->GetPosition().x - (transform_.position_.x /*+ 10.0f*/);
			float dy = pHeal->GetPosition().y - (transform_.position_.y /*+ 10.0f*/);

			float distance = sqrt(dx * dx + dy + dy);

			if (distance <= 10.0f)
			{
				if (Hp_ < 3) 
				{
					hp->HeelHp();
					Hp_++;
				}
				pHeal->KillMe();
				break;
			}
		}
		std::list<MpItem*> pMps = GetParent()->FindGameObjects<MpItem>();
		for (MpItem* pMp : pMps)
		{
			float dx = pMp->GetPosition().x - (transform_.position_.x/* + 16.0f*/);
			float dy = pMp->GetPosition().y - (transform_.position_.y/* + 16.0f*/);

			float distance = sqrt(dx * dx + dy + dy);

			if (distance <= 10.0f)
			{
				IsHitOneCount_ = true;
				if (IsHitOneCount_ = true)
				{
					MagicPoint_ += 5;

					if (MagicPoint_ >100)
					{
						MagicPoint_ = 100;
					}

					pMp->KillMe();
					break;
				}
			}
			else
			{
				IsHitOneCount_ = false;
			}
		}

		//死亡したらゲームオーバー画面へ
		if (transform_.position_.y > GROUND || Hp_ == 0)
		{
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
		}
		//特定のタイルに触れたらクリアSceneへ
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
   
	if (DebugLog_ == false)
	{

	}
	else if(DebugLog_ == true)
	{
		DrawFormatString(0, 0, GetColor(255, 255, 255), "プレイヤー(カメラ)の位置: (%d, %d)", x, y);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "Hp_: %d", Hp_);
		DrawFormatString(0, 40, GetColor(255, 255, 255), "NDTIME_: %f", NDTIME_);
		DrawFormatString(1100, 5, GetColor(255, 255, 255), "Nキーで天候変化");
		DrawFormatString(1100, 20, GetColor(255, 255, 255), "現在打てる魔法: %d", MagicPoint_);
	}
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
	//Buffs*pBuff = GetParent()->FindGameObject<Buffs>();

	if (WeatherState == Sunny)
	{
		WeatherSpeed_ = MOVE_SPEED;
		//pBuff->SetPosition(transform_.position_);
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
	Jump_P = -sqrtf(2 * GRAVITY * JUMP_HEIGHT + WeatherSpeed_ ); // プレイヤーをジャンプさせる
	onGround = false;
}

int Player::GetHp()
{
 	return Hp_;
}
