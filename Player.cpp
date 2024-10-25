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

//satou test
namespace
{
	const float MOVE_SPEED = 4.5f;
	const float GROUND = 600.0f;
	const float JUMP_HEIGHT = 64.0f * 1.45f;
    float GRAVITY = 9.8f / 60.0f;
	const int MAX_MAGIC_POINT = 100;
	const int MAX_DAMAGE_HP = 5;
	const float MAX_SNOW_FLAME = 120.0f * 5.0f;
	const float CHIP_SIZE = 64.0f; //計算で使ぁE�Eでfloat
 
};
Player::Player(GameObject* parent) : GameObject(sceneTop), WeatherSpeed_(MOVE_SPEED), Hp_(3), NDTIME_(2.0f), Flash_Count(0), IsHitOneCount_(false),DebugLog_(false)
{
	hImage = LoadGraph("Assets/Chara/Wizard.png");
	assert(hImage > 0);
	transform_.position_.x = 100.0f;
	transform_.position_.y = GROUND;
	onGround = true;
	flameCounter = 0;
	animType = 0;
	animeFrame = 0;

	Hp_ = 5;
	
	ChangeWeatherCoolTime = 60;
	CanChangeWeather = true;
	

	MagicPoint_ = 100;//MPの最大値100変更

	Hp_GetFlag = false;
	Hp_GetFlag = false;
	StringUi_Up = transform_.position_.y;
	MpHealTimer_ = 30;

	CountSnowFlame = MAX_SNOW_FLAME;

	stickTilt.IsLeftStickTilt_left = false;
	stickTilt.IsLeftStickTilt_right = false;
	stickTilt.IsRightStickTilt_left = false;
	stickTilt.IsRightStickTilt_right = false;

	soundHandle = LoadSoundMem("Assets/Music/SE/jump06.mp3");
	assert(soundHandle != -1);
	
	RainHandle = LoadSoundMem("Assets/Music/SE/Rain.mp3");
	assert(RainHandle != -1);

	WindHandle = LoadSoundMem("Assets/Music/SE/Wind.mp3");
	assert(WindHandle != -1);

	GetItemSound = LoadSoundMem("Assets/Music/SE/poka01.mp3");
	assert(GetItemSound != -1);

	MagicSound = LoadSoundMem("Assets/Music/SE/8bit_magic1.mp3");
	assert(MagicSound != -1);

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

	//xboxコントローラーの入力情報を取得
	padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);
	StickTiltCheck();

	SetFontSize(24);

	if (hp == nullptr)
	{
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
	if (Jump_P > 20.0f) {
		Jump_P = 20.0f; // 落下速度が最大値を超えないように制限
	}


	/*if (state == S_Cry)
	{
		flameCounter++;
		if (flameCounter);
	}*/

	//input.ThumbLXで左スティック入力をとる 倒した横軸値が-10000以下か10000以上で動く
	if (CheckHitKey(KEY_INPUT_D) || stickTilt.IsLeftStickTilt_right)
	{
		transform_.position_.x += WeatherSpeed_;
		if (++flameCounter >= 24)
		{
			animeFrame = (animeFrame + 1) % 2;
			flameCounter = 0;
		}

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
	else if (CheckHitKey(KEY_INPUT_A) || stickTilt.IsLeftStickTilt_left)
	{

		transform_.position_.x -= WeatherSpeed_;
		if (++flameCounter >= 24)
		{
			animeFrame = (animeFrame + 1) % 2;
			flameCounter = 0;
		}

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
	else
	{
		animeFrame = 0;
		flameCounter = 0;
	}
	//padInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//ジャンプ
	if (CheckHitKey(KEY_INPUT_SPACE) || input.Buttons[12])//Aボタン
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
			// 現在の天候状態を取得
			WeatherState WeatherState = pWeather->GetWeatherState();
			// 次に切り替える天候を決定
			if (WeatherState == Sun)//現在晴れなら
			{
				pWeather->SetWeather(Rain);//次は雨に
				StopSoundMem(WindHandle);
			}
			else if (WeatherState == Rain)
			{
				pWeather->SetWeather(Gale);//次は強風に
				StopSoundMem(RainHandle);
				StopSoundMem(WindHandle);
			}
			else if (WeatherState == Gale)
			{
				pWeather->SetWeather(Snow);//次は雪に
				StopSoundMem(WindHandle);
			}
			else if (WeatherState == Snow)
			{
				pWeather->SetWeather(Sun);
			}
			WeatherTime_ = 60;
		}
		WeatherSwitch = true;
	}
	else
	{
		WeatherSwitch = false;
	}

	//天気を変える（十字キー）
	if (input.Buttons[0])//↑晴れにする
	{
		if (CanChangeWeather && pWeather != nullptr)
		{
			// 現在の天候状態を取得
			WeatherState WeatherState = pWeather->GetWeatherState();

			if (WeatherState != Sun)//晴れ以外なら
			{
				ChangeWeatherCoolTime = 60;
				CanChangeWeather = false;
				pWeather->SetWeather(Sun);
				StopWeatherSE();
			}
		}
	}
	else if (input.Buttons[2])//←雨にする
	{
		if (CanChangeWeather && pWeather != nullptr)
		{
			// 現在の天候状態を取得
			WeatherState WeatherState = pWeather->GetWeatherState();

			if (WeatherState != Rain)//雨以外なら
			{
				ChangeWeatherCoolTime = 60;
				CanChangeWeather = false;
				pWeather->SetWeather(Rain);
				StopWeatherSE();
			}
		}
	}
	else if (input.Buttons[3])//→風にする
	{
		if (CanChangeWeather && pWeather != nullptr)
		{
			// 現在の天候状態を取得
			WeatherState WeatherState = pWeather->GetWeatherState();

			if (WeatherState != Gale)//風以外なら
			{
				ChangeWeatherCoolTime = 60;
				CanChangeWeather = false;
				pWeather->SetWeather(Gale);
				StopWeatherSE();
			}
		}
	}
	else if (input.Buttons[1])//↓雪にする
	{
		if (CanChangeWeather && pWeather != nullptr)
		{
			// 現在の天候状態を取得
			WeatherState WeatherState = pWeather->GetWeatherState();

			if (WeatherState != Snow)//雪以外なら
			{
				ChangeWeatherCoolTime = 60;
				CanChangeWeather = false;
				pWeather->SetWeather(Snow);
				StopWeatherSE();
			}
		}
	}
	//タイマーが切れてCanChangeWeather = trueになるまで再度天気の変更不可
	if (--ChangeWeatherCoolTime < 0)
	{
		CanChangeWeather = true;
	}



	if (pWeather != nullptr)
	{

		if (pWeather->GetWeatherState() == Gale) //風の機能
		{
			if (MagicPoint_ > 0)
			{
				if (GaleTime_ < 0)//約5秒ごとに行う処理
				{
					GaleTime_ = 420;
					MagicDown(2);//4だと消費量多すぎるかもしれない　要調整
					PlaySoundMem(WindHandle, DX_PLAYTYPE_BACK);
				}
				else
				{
					GaleTime_--;
				}
			}	
		}

		if (pWeather->GetWeatherState() == Rain)
		{
			if (MagicPoint_ > 0)
			{
				if (RainTime_ < 0)//約5秒ごとに行う処理
				{
					RainTime_ = 420;
					MagicDown(1);
					PlaySoundMem(RainHandle, DX_PLAYTYPE_BACK);
				}
				else
				{
					RainTime_--;
				}
			}
		}
	}


	//拡張性はない
	//if (transform_.position_.y >= GROUND)//地面についたら速度を元に戻す、戻さないと貫通する恐れあり
	//{
	//	transform_.position_.y = GROUND;
	//	Jump_P = 0.0f;
	//	onGround = true;
	//}
	//------------------------------------------------------------------------------------------

	//攻撃魔法の処理
	if (CheckHitKey(KEY_INPUT_M) || input.Buttons[13])//bボタン
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

			PlaySoundMem(MagicSound, DX_PLAYTYPE_BACK);
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
		if (pSlime->ColliderRect(transform_.position_.x + pSlime->GetScale().x, transform_.position_.y + pSlime->GetScale().y, 64.0f, 64.0f))
		{
			if (transform_.position_.y + 64.0f <= pSlime->GetPosition().y + (64.0f * pSlime->GetScale().y) / 2 + 20) // プレイヤーがスライムの上部にある
			{
				WeatherState WeatherState = pWeather->GetWeatherState();
				float RainBound = 0.5; // 雨の日に発生するスライムの弾性
				if (WeatherState == Rain && MagicPoint_ > 0)
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
					break; // ダメージを与えた後にループを抜ける
				}
			}
		}
	}

	//Damage* pDamage = GetParent()->FindGameObject<Damage>();
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

	
	std::list<EnemyMagic*> pEMagics = GetParent()->FindGameObjects<EnemyMagic>();
	for (EnemyMagic* pEnemyMagic : pEMagics)
	{
		//『EnemyMagic』と『Slime』の距離を求めている
		float dx = pEnemyMagic->GetPosition().x - (transform_.position_.x + 32.0f);//Mgの座標X - Slの座標X
		float dy = pEnemyMagic->GetPosition().y - (transform_.position_.y + 32.0f);//Mgの座標Y - Slの座標Y
		float distance = sqrt(dx * dx + dy * dy);//ここで明確な距離を計算

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

				NDTIME_ = 2.0f;//個々の数値で無敵時間がきまる
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
			if (!IsHitOneCount_) // アイテムを拾ったときに一度だけMagicPoint_を増やす
			{
				MagicUp(5);
				IsHitOneCount_ = true; // MagicPoint_を増やした後はIsHitOneCount_をtrueに設定
			}
			pMp->KillMe();
			Mp_GetFlag = true;
			UIGetTimer = 60;
			StringUi_Up = transform_.position_.y;
		}
		else
		{
			IsHitOneCount_ = false; // アイテムが範囲外になったらIsHitOneCount_をfalseにリセット
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
			//<= 32.0fの意味は横との接触の幅を制限している
			if (dy < 0 && abs(dx) <= 32.0f) //岩の上に乗る
			{
				transform_.position_.y = pRock->GetPosition().y - 64; // プレイヤーを上に移動
				WeatherSpeed_ = 0;
				onGround = true;
			}
			else if (dy > 0 && abs(dx) <= 32.0f) //岩の下にぶつかる
			{
				int push = 3;
				transform_.position_.y = pRock->GetPosition().y + push; // プレイヤーを下に移動
				WeatherSpeed_ = MOVE_SPEED;
			}
			else if (dx < 0) // 岩の右側の衝突判定
			{
				int push = 1;
				transform_.position_.x += push; // プレイヤーを右に移動
			}
			else if (dx > 0) // 岩の左側の衝突判定
			{
				int push = 1;
				transform_.position_.x -= push; // プレイヤーを左に移動
			}
		}
	}

	//死亡したらゲームオーバー画面へ
	if (transform_.position_.y > GROUND || Hp_ == 0)
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
		StopSoundMem(WindHandle);
	}


	if (pField != nullptr)
	{
		int playerX = (int)transform_.position_.x;
		int playerY = (int)transform_.position_.y;

		if (pField->IsHitClear(playerX, playerY))
		{
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_CLEAR);
			StopSoundMem(WindHandle);
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
  
	//mp20以下でmp自動回復
	if (MagicPoint_ < 20)
	{
		if (--MpHealTimer_ < 0)
		{
			MagicPoint_++;
			MpHealTimer_ = 30;
		}
	}
  
	//雪の晁E時間経過(とりあえずフレーム経過)でMPが減る
	if (pWeather->GetWeatherState() == WeatherState::Snow)
	{
		//フレーム基準だからなぁE..
		CountSnowFlame--;
	}

	//残りの雪時間ぁEを�Eったら
	if (CountSnowFlame <= 0)
	{
		if (MagicPoint_ >= 10)//MPぁE0以上�E時�E10減らぁE
		{
			MagicPoint_ -= 10;
			
		}
		else
		{
			MagicPoint_ = 0;//10よりすくなぁE��き�E0にしちめE��
		}
		CountSnowFlame = MAX_SNOW_FLAME; //また�EチE��スに戻ぁE
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
		DrawRectGraph(x, y, animeFrame * 64, animType * 64, 64, 64, hImage, TRUE);
	}
	else
	{
		if (Flash_Count % 24 == 0)
		{
			DrawRectGraph(x, y, animeFrame * 64, animType * 64, 64, 64, hImage, TRUE);
		}
	}
	
	++Flash_Count;

	if (Mp_GetFlag == true)
	{
		if (UIGetTimer > 0)
		{
			DrawFormatString(x, StringUi_Up, GetColor(255,255,255), "MP+5");
			PlaySoundMem(GetItemSound, DX_PLAYTYPE_BACK); // 音声を再生
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
			DrawFormatString(x, StringUi_Up, GetColor(255,255,255), "Hp+2");
			PlaySoundMem(GetItemSound, DX_PLAYTYPE_BACK); 
			StringUi_Up -= 1;
			UIGetTimer--;
		}
		else
		{
			Hp_GetFlag = false;
		}
	}

	if (MagicPoint_ == 0)
	{
		DrawFormatString(0, 60, GetColor(255, 69, 0), "MP: %d /20", MagicPoint_);//0なら赤に
	}
	else
	{
		DrawFormatString(0, 60, GetColor(30, 144, 255), "MP: %d /100", MagicPoint_);//それ以外なら青に
	}

    if(DebugLog_ == true)
	{
		DrawFormatString(815, 0, GetColor(0, 0, 0), "プレイヤー(カメラ)の位置: (%d, %d)", x, y);
		DrawFormatString(1000, 30, GetColor(0, 0, 0), "HP: %d", Hp_);
		DrawFormatString(1000, 54, GetColor(0, 0, 0), "無敵時間: %f", NDTIME_);
		DrawFormatString(1000, 76, GetColor(0, 0, 0), "地面判定:%d", onGround);
	}

	//DrawFormatString(800, 0, GetColor(255, 255, 255), "風が起こせる時閁E%d", GaleTime_);
	WhereIs();
	DrawFormatString(800, 0, GetColor(255, 0, 0), "thumbLX:%d", input.ThumbLX);
	//DrawFormatString(800, 0, GetColor(255, 255, 255), "風が起こせる時間:%d", GaleTime_);
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

	if (WeatherState == Sun)
	{
		WeatherSpeed_ = MOVE_SPEED;
	}
	else if (WeatherState == Rain)
	{
		WeatherSpeed_ = MOVE_SPEED;
	}
	else if (WeatherState == Gale)
	{
		if (MagicPoint_ > 0)//0以上なら移動速度を普通に戻す
		{
			WeatherSpeed_ = MOVE_SPEED * (0.2f + WeatherEffect);
		}
		else
		{
			WeatherSpeed_ = MOVE_SPEED;
		}
	}
	else if (WeatherState == Snow)
	{
		if (MagicPoint_ > 0)
		{
			WeatherSpeed_ = MOVE_SPEED * (1.2f - WeatherEffect);
		}
		else
		{
			WeatherSpeed_ = MOVE_SPEED;
		}
	}
	
}

void Player::Jump()
{
	Jump_P = -sqrtf(2 * GRAVITY * JUMP_HEIGHT + WeatherSpeed_ ); // プレイヤーをジャンプさせる
	onGround = false;
	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK); // 音声を再生
}

int Player::GetHp()
{
 	return Hp_;
}

void Player::MagicUp(int _PMp)
{
	MagicPoint_ += _PMp;
	PlaySoundMem(GetItemSound, DX_PLAYTYPE_BACK); 
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


void Player::WhereIs()
{
	/*
	64*csvの横幁Emax
	ぁE��ぁE��とぁEnow
	よこせんばーひぁE��、線�E長ぁEnow/maxに縦線引く かんじ！E
	*/

	//横線関連
	static int SenStart = 1000; //横線�E始点x
	static int SenLength = 200; //横線�E長さx
	static int SenY = 50; //横線�Ey
	static int SenHeight = 5; //横線�E幁E
	DrawBox(SenStart, SenY, SenStart + SenLength, SenY + SenHeight, GetColor(128, 128, 128), true);

	//縦線関連
	Field* pField = GetParent()->FindGameObject<Field>();
	static float max = CHIP_SIZE * pField->GetCsvWidth();
	float now = transform_.position_.x;
	float nowLine = SenStart + SenLength * (now / max); //縦線引くところの
	DrawLine(nowLine, SenY - 10, nowLine, SenY + 10, GetColor(128, 128, 128));


	//進行度作�EのチE��チE��用
	DrawFormatString(0, 0, GetColor(255, 0, 0), "%f", transform_.position_.x);
	DrawFormatString(0, 10, GetColor(255, 0, 0), "%f", nowLine);
  
void Player::StopWeatherSE()
{
	if (CheckSoundMem(RainHandle) == 1)
	{
		StopSoundMem(RainHandle);
	}
	if (CheckSoundMem(WindHandle) == 1)
	{
		StopSoundMem(WindHandle);
	}
}

/// <summary>
/// sticktiltの構造体の変数を設定（各フレーム）
/// </summary>
void Player::StickTiltCheck()
{
	//左スティックを倒してる方向にtrue
	if (input.ThumbLX <= -10000)
	{
		stickTilt.IsLeftStickTilt_left = true;
	}
	else if (input.ThumbLX >= 10000)
	{
		stickTilt.IsLeftStickTilt_right = true;
	}
	else
	{
		stickTilt.IsLeftStickTilt_left = false;
		stickTilt.IsLeftStickTilt_right = false;
	}
	
	//右スティックを倒してる方向にtrue
	//player関連で右スティックを使うならコメント外す
	/*if (input.ThumbRX <= -10000)
	{
		stickTilt.IsRightStickTilt_left = true;
	}
	else if(input.ThumbRX >= 10000)
	{
		stickTilt.IsRightStickTilt_right = true;
	}
	else
	{
		stickTilt.IsRightStickTilt_left = false;
		stickTilt.IsRightStickTilt_right = false;
	}*/
}

