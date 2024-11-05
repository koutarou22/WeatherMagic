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
#include"MP.h"
#include <iostream>

//satou test
namespace
{
	const float MOVE_SPEED = 4.5f;
	const float GROUND = 600.0f;
	const float JUMP_HEIGHT = 64.0f * 1.45f;

    const float GRAVITY = 9.8f / 60.0f;
	const float MAX_GRAVITY = 6.0f;//Limit Gravity
	const int MAX_MAGIC_POINT = 100;
	const int MAX_DAMAGE_HP = 5;

	const float MAX_SNOW_FLAME = 120.0f * 10.0f;
  const float CHIP_SIZE = 64.0f;  //計算でつかうのでfloat
	const float DEAD_LINE = 900.0f;
	
};
Player::Player(GameObject* parent) : GameObject(sceneTop), WeatherSpeed_(MOVE_SPEED),
        Hp_(5), NDTIME_(2.0f), Flash_Count(0), MagicPoint_(100),IsHitOneCount_(false),DebugLog_(false)
{
	hImage = LoadGraph("Assets/Chara/Wizard.png");
	assert(hImage > 0);
	transform_.position_.x = 100.0f;
	transform_.position_.y = GROUND;
	onGround = true;
	onRock = false;
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
	switch (player_state)
	{
	case Player::S_WaIk:
		UpdateWalk();
		break;
	case Player::S_Damage:
		UpdateDamage();
		break;
	case Player::S_Dead:
		UpdateDead();
		break;
	case Player::S_Erase:
		UpdateErase();
	default:
		break;
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

	switch (player_animation_state)
	{
	case Player::S_Walk_A:
	{
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
		break;
	}
	case Player::S_Damage_A:
		DrawRectGraph(x, y, 2 * 64, animType * 64, 64, 64, hImage, TRUE);
		break;
	case Player::S_Dead_A:
		DrawRectGraph(x, y, animeFrame * 64, animType * 64, 64, 64, hImage, TRUE);
		break;
	case Player::S_Erase_A:
		break;
	default:
		break;

	}
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
		DrawFormatString(0, 130, GetColor(255, 69, 0), "MP: %d /100", MagicPoint_);//0なら赤に
	}
	else
	{
		DrawFormatString(0, 130, GetColor(30, 144, 255), "MP: %d /100", MagicPoint_);//それ以外なら青に
	}

    if(DebugLog_ == true)
	{
		//DrawFormatString(815, 0, GetColor(0, 0, 0), "プレイヤー(カメラ)の位置: (%d, %d)", x, y); 文字化けしてるので　使うなら再度書き直し
		//DrawFormatString(1000, 30, GetColor(0, 0, 0), "HP: %d", Hp_);
		//DrawFormatString(1000, 54, GetColor(0, 0, 0), "無敵時間: %f", NDTIME_);
		//DrawFormatString(1000, 76, GetColor(0, 0, 0), "地面判定:%d", onGround);
	}
	WhereIs();
	//DrawFormatString(800, 0, GetColor(255, 0, 0), "thumbLX:%d", input.ThumbLX);
	//DrawFormatString(800, 0, GetColor(255, 255, 255), "風が起こせる時間:%d", GaleTime_);

	//DrawCircle(x+32, y+32, 32, GetColor(255, 0, 0), FALSE);
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
/*
void Player::Update()
{
	
}
*/


void Player::UpdateWalk()
{
	Field* pField = GetParent()->FindGameObject<Field>();
	Weather* pWeather = GetParent()->FindGameObject<Weather>();
	std::list<Slime*> pSlimes = GetParent()->FindGameObjects<Slime>();
	Rock* pRock = GetParent()->FindGameObject<Rock>();

	Hp* hp = GetParent()->FindGameObject<Hp>();
	MP* mp = GetParent()->FindGameObject<MP>();

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
	if (Jump_P > MAX_GRAVITY) 
	{
		Jump_P = MAX_GRAVITY;
	}
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
			GaleEffect(Gale);
			if (MagicPoint_ > 0)
			{
				if (GaleTime_ < 0)//約5秒ごとに行う処理
				{
					GaleTime_ = 420;
					MagicDown(2);//消費量は要調整
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
					MagicDown(1);
					/*RainTime_ = 10;*/
					RainTime_ = 420;
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
			mg->SetPosition(transform_.position_.x,transform_.position_.y);
			VECTOR dir = { 1.0f, 0.0f };
			mg->SetDirection(dir);
			mg->SetSpeed(5.5f);
			CoolDownMagic_ = timer_;


			mp->SetGaugeVal(MagicPoint_, MAX_MAGIC_POINT);
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
		float x = transform_.position_.x;
		float y = transform_.position_.y;

		if (pSlime->ColliderRect(x + pSlime->GetScale().x, y + pSlime->GetScale().y, 43.0f, 43.0f))
		{
			if (y + 43.0f <= pSlime->GetPosition().y + 42 - (43.0f * pSlime->GetScale().y) / 2 + 20) // プレイヤーがスライムの上部にある
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
		float dx = pEnemyMagic->GetPosition().x + 16 - (transform_.position_.x + 32.0f);//Mgの座標X - Slの座標X
		float dy = pEnemyMagic->GetPosition().y + 16 - (transform_.position_.y + 32.0f);//Mgの座標Y - Slの座標Y
		float distance = sqrt(dx * dx + dy * dy);//ここで明確な距離を計算

		if (distance <= 30.0f)
		{
			if (NDTIME_ <= 0.0f)
			{
				hp->DamageHp();
				HpDown(1);

				NDTIME_ = 2.0f;//個々の数値で無敵時間がきまる
			}
			break;
		}
	}

	std::list<Ghost*> pGhosts = GetParent()->FindGameObjects<Ghost>();
	for (Ghost* pGhost : pGhosts)
	{
		float dx = pGhost->GetPosition().x + 42 - (transform_.position_.x + 32.0f);
		float dy = pGhost->GetPosition().y + 42 - (transform_.position_.y + 32.0f);

		float distance = sqrt(dx * dx + dy * dy);

		if (distance <= 40.0f)
		{
			if (NDTIME_ <= 0.0f)
			{
				hp->DamageHp();
				HpDown(1);

				NDTIME_ = 3.0f;
			}
			break;
		}
	}

	std::list<HealItem*> pHeals = GetParent()->FindGameObjects<HealItem>();
	for (HealItem* pHeal : pHeals)
	{
		float dx = pHeal->GetPosition().x + 35 - (transform_.position_.x + 32.0f);
		float dy = pHeal->GetPosition().y + 32 - (transform_.position_.y + 32.0f);

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
		float dx = pMp->GetPosition().x + 35 - (transform_.position_.x + 32.0f);
		float dy = pMp->GetPosition().y + 32 - (transform_.position_.y + 32.0f);

		float distance = sqrt(dx * dx + dy * dy);

		if (distance <= 20.0f)
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
	onRock = false;
	for (Rock* pRock : pRocks)
	{

		WeatherState WeatherState = pWeather->GetWeatherState();

		float dx = pRock->GetPosition().x - transform_.position_.x;
		float dy = pRock->GetPosition().y - transform_.position_.y;

		float distance = sqrt(dx * dx + dy * dy);
		float push = 3.5;

		if (distance <= 64.0f) 
		{
			if (dy <= -0.1 && abs(dx) <= 32.0f)
			{
				transform_.position_.y = pRock->GetPosition().y - 64 + push; 
				onGround = true;
				onRock = true;
			}
			else if (dy > -0.1 && abs(dx) <= 32.0f) 
			{
				transform_.position_.y = pRock->GetPosition().y + push; 
			}
			else if (dx < -0.1 && abs(dy) <= 32.0f)
			{
				transform_.position_.x += push; 
			}
			else if (dx > -0.1 && abs(dy) <= 32.0f)
			{
				transform_.position_.x -= push; 
			}
		}
	}


	//死亡したらゲームオーバー画面へ
	if (Hp_ <= 0 || transform_.position_.y > DEAD_LINE)
	{
		animeFrame = 5;
		flameCounter = 0;
		player_animation_state = S_Dead_A;
		player_state = S_Dead;
		//isDead_ = true;
	}

	if (pField != nullptr)
	{
		int playerX = (int)transform_.position_.x;
		int playerY = (int)transform_.position_.y;

		if (pField->IsHitClear(playerX, playerY))
		{
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");

			if (pSceneManager != nullptr)
			{
				int MpPass = MagicPoint_;//現在のMｐを変数に格納
				pSceneManager->SetMagicPoint(MpPass);//Set関数に送り保存
			}

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

	//mp20以下でmp自動回復
	if (MagicPoint_ < 20)
	{
		if (--MpHealTimer_ < 0)
		{
			mp->SetGaugeVal(MagicPoint_, MAX_MAGIC_POINT);
			MagicPoint_++;
			MpHealTimer_ = 60;
		}
	}

	//雪の時間経過(とりあえずフレーム経過)でMPが減る
	if (pWeather != nullptr)
	{
		if (pWeather->GetWeatherState() == WeatherState::Snow)
		{
			//フレーム基準だからなぁE..
			CountSnowFlame--;
		}
	}

	//残りの雪時間が0以下だったら
	if (CountSnowFlame <= 0)
	{
		if (MagicPoint_ >= 10)//MPが10以上なら減らす
		{
			MagicPoint_ -= 10;
			HpDown(1);
		}
		else
		{
			MagicPoint_ = 0;//10より少なかったら0に
		}
		CountSnowFlame = MAX_SNOW_FLAME; //元に戻す
	}
}

void Player::UpdateDamage()
{
	animeFrame = 2;
	if (++flameCounter >= 24)
	{
		player_state = S_WaIk;
		player_animation_state = S_Walk_A;
		animeFrame = 0;
	}
}

void Player::UpdateDead()
{

	//死亡のアニメーション
		if (++flameCounter >= 30)
		{
			animeFrame++;
			flameCounter = 0;
		}
		
		
		if (animeFrame >= 7) 
		{
			player_animation_state = S_Erase_A;
			player_state = S_Erase;
			animeFrame = 7;
		}
}

void Player::Jump()
{
	Jump_P = -sqrtf(2 * GRAVITY * JUMP_HEIGHT + WeatherSpeed_ ); // プレイヤーをジャンプさせる
	onGround = false;
	onRock = false;
	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK); // 音声を再生
}

int Player::GetMp()
{
	return MagicPoint_;
}

int Player::GetHp()
{
 	return Hp_;
}

void Player::MagicUp(int _PMp)
{
	MP* mp = GetParent()->FindGameObject<MP>();
	mp->SetGaugeVal(MagicPoint_, MAX_MAGIC_POINT);
	MagicPoint_ += _PMp;
	PlaySoundMem(GetItemSound, DX_PLAYTYPE_BACK); 
	if (MagicPoint_ > MAX_MAGIC_POINT)
	{
		MagicPoint_ = MAX_MAGIC_POINT;
	}
}

void Player::MagicDown(int _MMp)
{
	MP* mp = GetParent()->FindGameObject<MP>();
	mp->SetGaugeVal(MagicPoint_, MAX_MAGIC_POINT);
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
	player_animation_state = S_Damage_A;
	player_state = S_Damage;
}


void Player::WhereIs()
{
	//横線関連
	static int SenStart = 1000; //横線の始点x
	static int SenLength = 200; //横線の長さx
	static int SenY = 50; //横線の始点y
	static int SenHeight = 5; //横線の幅
	DrawBox(SenStart, SenY, SenStart + SenLength, SenY + SenHeight, GetColor(128, 128, 128), true); //横線かく

	//縦線関連
	Field* pField = GetParent()->FindGameObject<Field>(); 
	static float max = CHIP_SIZE * pField->GetGoalWidth();
	float now = transform_.position_.x;
	float nowLine = SenStart + SenLength * (now / max) * 2; //縦線引くところのX
	if (nowLine >= SenStart + SenLength)
	{
		nowLine = SenStart + SenLength; //マップは続くがゴールしたら縦線は動かない
	}
	DrawBox(nowLine, SenY - 10, nowLine + SenHeight, SenY + 10, GetColor(128, 128, 128),true);  //縦線かく

	//スタート
	SetFontSize(20);
	DrawCircle(SenStart-5, SenY, 10,GetColor(128, 128, 128), true);
	DrawFormatString(SenStart-9,SenY-8, GetColor(255, 255, 255),"S");

	//ゴール
	SetFontSize(20);
	DrawCircle(SenStart+SenLength+ 5, SenY, 10, GetColor(128, 128, 128), true);
	DrawFormatString(SenStart + SenLength +2, SenY-8, GetColor(255, 255, 255), "G");

	SetFontSize(32); //一応デフォルトなサイズに戻す
}

void Player::UpdateErase()
{
	if (++flameCounter >= 60)
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
		StopSoundMem(WindHandle);
		flameCounter = 0;
	}
}

void Player::GaleEffect(WeatherState state)
{
	Camera* cam = GetParent()->FindGameObject<Camera>();

	// xboxコントローラーの入力情報を取得
	padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);

	if (cam != nullptr)
	{
		// カメラの位置を取得
		int camX = cam->GetValue();
		//if (transform_.position_.x >= camX && transform_.position_.x <= camX)
		//{

		if (onRock == true)
		{
			if (state == Gale)
			{
				int MpVanish = GetMp();
				if (MpVanish >= 4)
				{
					if (input.ThumbRX <= -10000 || CheckHitKey(KEY_INPUT_LEFT))
					{
						transform_.position_.x -= 0.6f;
					}
					else if (input.ThumbRX >= 10000 || CheckHitKey(KEY_INPUT_RIGHT))
					{
						transform_.position_.x += 0.6f;
					}
				}
			}
		}
	}
}


