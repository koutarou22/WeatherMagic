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
#include "Damage.h"
#include "HealItem.h"
#include "MpItem.h"
#include "Rock.h"
#include"MP.h"
#include"WeatherChangeEffect.h"
#include"ClearFlag.h"
#include"Logo.h"
#include "LandingEffect.h"
#include "EnemyMagic.h"

//satou test
namespace
{
	const float MOVE_SPEED = 4.5f;
	const float GROUND = 605.0f;
	const float JUMP_HEIGHT = 64.0f * 1.45f;

	const float GRAVITY = 9.8f / 60.0f;
	const float MAX_GRAVITY = 6.0f;//Limit Gravity
	const int MAX_MAGIC_POINT = 100;
	const int MAX_DAMAGE_HP = 5;

	const float MAX_SNOW_FLAME = 120.0f * 10.0f;
	const float CHIP_SIZE = 64.0f;  //計算でつかうのでfloat
	const float DEAD_LINE = 800.0f;

};
Player::Player(GameObject* parent) : GameObject(sceneTop), WeatherSpeed_(MOVE_SPEED),
Hp_(5), NDTIME_(2.0f), Flash_Count(0), MagicPoint_(100), IsHitOneCount_(false), DebugLog_(false),hasLanded(false)
{
	hPlayer_ = LoadGraph("Assets/Chara/Clear_Wizard.png");
	assert(hPlayer_ > 0);

	pLanding = nullptr;

	transform_.position_.x = 100.0f;
	transform_.position_.y = GROUND;
	onGround = true;
	onRock = false;
	flameCounter = 0;
	animType = 0;
	animeFrame = 0;

	Hp_ = 5;//Hpの数を指定

	ChangeWeatherCoolTime = 60;
	CanChangeWeather = true;

	HitLanding = true;

	//MPの最大値100変更
	MagicPoint_ = 100;

	Hp_GetFlag = false;
	Hp_GetFlag = false;
	StringUi_Up = transform_.position_.y;
	MpHealTimer_ = 30;

	CountSnowFlame = MAX_SNOW_FLAME;
	IsTurnLeft = false;

	stickTilt.IsLeftStickTilt_left = false;
	stickTilt.IsLeftStickTilt_right = false;
	stickTilt.IsRightStickTilt_left = false;
	stickTilt.IsRightStickTilt_right = false;

	////----------------------天候音の登録------------------------
	//雨音
	RainHandle = LoadSoundMem("Assets/Music/SE/Weather/Rain.mp3");
	assert(RainHandle != -1);
	//風音
	WindHandle = LoadSoundMem("Assets/Music/SE/Weather/Wind.mp3");
	assert(WindHandle != -1);
	//雪音
	SnowHandle = LoadSoundMem("Assets/Music/SE/Weather/Snow.mp3");
	assert(SnowHandle != -1);
	//-----------------------------------------------------------

	//MP取得音取得音
	GetMPItemHandle = LoadSoundMem("Assets/Music/SE/Player/GetMPItem.mp3");
	assert(GetMPItemHandle != -1);

	//HP取得音取得音
	GetHPItemHandle = LoadSoundMem("Assets/Music/SE/Player/GetHPItem.mp3");
	assert(GetHPItemHandle != -1);

	//魔法音
	MagicHandle = LoadSoundMem("Assets/Music/SE/Player/AttackMagic.mp3");
	assert(MagicHandle != -1);

	//ジャンプ音
	JumpHandle = LoadSoundMem("Assets/Music/SE/Player/Jump.mp3");
	assert(JumpHandle != -1);

	//着地音
	LandingHandle = LoadSoundMem("Assets/Music/SE/Player/Landing.mp3");
	assert(LandingHandle != -1);

	//ダメージ音
	DamageHandle = LoadSoundMem("Assets/Music/SE/Player/Damage.mp3");
	assert(DamageHandle != -1);


	//HPが1になった時の警告音
	WarningHandle = LoadSoundMem("Assets/Music/SE/Player/Crisis.mp3");
	assert(WarningHandle != -1);

	//死亡時の音
	DieHandle = LoadSoundMem("Assets/Music/SE/Player/Die.mp3");
	assert(DieHandle != -1);

	//スピードアップ音
	SpeedUpHandle = LoadSoundMem("Assets/Music/SE/Weather/SpeedUp.mp3");
	assert(SpeedUpHandle != -1);

	//スライムバウンド音
	BoundHandle = LoadSoundMem("Assets/Music/SE/Slime/Bound.mp3");
	assert(BoundHandle != -1);

	//雨の日の時のスライムバウンド音
	HighBoundHandle = LoadSoundMem("Assets/Music/SE/Slime/HighBound.mp3");
	assert(HighBoundHandle != -1);

	//雪の時凍ってることがわかるSE
	FreezeHandle = LoadSoundMem("Assets/Music/SE/Weather/Freeze.mp3");
	assert(FreezeHandle != -1);

	ClearHandle = LoadSoundMem("Assets/Music/SE/Player/Clear3.mp3");
	assert(ClearHandle != -1);

	MultiDeadSE = false;//複数回鳴るのを阻止用

	ChangeVolumeSoundMem(HighBoundHandle, 200);

	hGoal = LoadGraph("Assets/Item/GoalFlag.png");
}

Player::~Player()
{
	Release();
}

void Player::Release()
{
	if (hPlayer_ > 0)
	{
		DeleteGraph(hPlayer_);
	}
	if (hGoal > 0)
	{
		DeleteGraph(hGoal);
	}

	if (RainHandle > 0)
	{
		DeleteSoundMem(RainHandle);
	}
	if (WindHandle > 0)
	{
		DeleteSoundMem(WindHandle);
	}
	if (SnowHandle > 0)
	{
		DeleteSoundMem(SnowHandle);
	}

	if (GetMPItemHandle > 0)
	{
		DeleteSoundMem(GetMPItemHandle);
	}
	if (GetHPItemHandle > 0)
	{
		DeleteSoundMem(GetHPItemHandle);
	}


	if (MagicHandle > 0)
	{
		DeleteSoundMem(MagicHandle);
	}
	if (JumpHandle > 0)
	{
		DeleteSoundMem(JumpHandle);
	}
	if (LandingHandle > 0)
	{
		DeleteSoundMem(LandingHandle);
	}
	if (DamageHandle > 0)
	{
		DeleteSoundMem(DamageHandle);
	}
	if (WarningHandle > 0)
	{
		DeleteSoundMem(WarningHandle);
	}
	if (DieHandle > 0)
	{
		DeleteSoundMem(DieHandle);
	}
	if (SpeedUpHandle > 0)
	{
		DeleteSoundMem(SpeedUpHandle);
	}
	if (BoundHandle > 0)
	{
		DeleteSoundMem(BoundHandle);
	}
	if (FreezeHandle > 0)
	{
		DeleteSoundMem(FreezeHandle);
	}
	if (FreezeHandle > 0)
	{
		DeleteSoundMem(FreezeHandle);
	}
	if (ClearHandle > 0)
	{
		DeleteSoundMem(ClearHandle);
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
		break;
	case Player::S_Clear:
		UpdateClear();
		break;
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
	//CameraPosX = x;

	switch (player_animation_state)
	{
	case Player::S_Walk_A:
	{
		if (NDTIME_ <= 0.0f)
		{
			if (IsTurnLeft)
			{
				DrawRectGraph(x, y, animeFrame * 64, animType * 64, 64, 64, hPlayer_, TRUE, 1, 0);//1...左右反転on 0...上下反転off
			}
			else
			{
				DrawRectGraph(x, y, animeFrame * 64, animType * 64, 64, 64, hPlayer_, TRUE);
			}

		}
		else
		{
			if (Flash_Count % 10 == 0)
			{
				if (IsTurnLeft)
				{
					DrawRectGraph(x, y, animeFrame * 64, animType * 64, 64, 64, hPlayer_, TRUE, 1, 0);
				}
				else
				{
					DrawRectGraph(x, y, animeFrame * 64, animType * 64, 64, 64, hPlayer_, TRUE);
				}
			}
		}
		++Flash_Count;
		break;
	}
	case Player::S_Damage_A:

		if (IsTurnLeft)
		{
			DrawRectGraph(x, y, 2 * 64, animType * 64, 64, 64, hPlayer_, TRUE, 1, 0);
		}
		else
		{
			DrawRectGraph(x, y, 2 * 64, animType * 64, 64, 64, hPlayer_, TRUE);
		}

		break;
	case Player::S_Dead_A:

		if (IsTurnLeft)
		{
			DrawRectGraph(x, y, animeFrame * 64, animType * 64, 64, 64, hPlayer_, TRUE, 1, 0);
			if (!MultiDeadSE)
			{
				PlaySoundMem(DieHandle, DX_PLAYTYPE_BACK); // 音声を再生
				MultiDeadSE = true;
			}
		}
		else
		{
			DrawRectGraph(x, y, animeFrame * 64, animType * 64, 64, 64, hPlayer_, TRUE);
			if (!MultiDeadSE)
			{
				PlaySoundMem(DieHandle, DX_PLAYTYPE_BACK); // 音声を再生
				MultiDeadSE = true;
			}
		}
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
			DrawFormatString(x, StringUi_Up, GetColor(255, 255, 255), "MP+10");

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
			DrawFormatString(x, StringUi_Up, GetColor(255, 255, 255), "HP+2");
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
		DrawFormatString(20, 80, GetColor(255, 0, 0), "%d", MagicPoint_);//0なら赤に
	}
	else
	{
		DrawFormatString(20, 80, GetColor(0, 0, 255), "%d", MagicPoint_);//それ以外なら青に
	}

	if (DebugLog_ == true)
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



void Player::WeatherEffects(Weather* weather)
{
	WeatherState WeatherState = weather->GetWeatherState();
	float WeatherEffect = weather->GetWeatherChange();

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

void Player::DamageSE()
{
	//ダメージ音が何回も呼ばれるバグが発生したので、ここに書きます
	PlaySoundMem(DamageHandle, DX_PLAYTYPE_BACK); // 音声を再生
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
	if (CheckSoundMem(SnowHandle) == 1)
	{
		StopSoundMem(SnowHandle);
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
}

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


	if (Jump_P > 20.0f)
	{
		Jump_P = 20.0f; // 落下速度が最大値を超えないように制限
	}

	//input.ThumbLXで左スティック入力をとる 倒した横軸値が-10000以下か10000以上で動く
	if (CheckHitKey(KEY_INPUT_D) || stickTilt.IsLeftStickTilt_right)
	{
		IsTurnLeft = false;
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
		IsTurnLeft = true;
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
			if (!onGround && GetParent() != nullptr) 
			{

				onGround = true;

					if (pLanding == nullptr)
					{
       					pLanding = Instantiate<LandingEffect>(GetParent());
					}
					if (pLanding != nullptr) 
					{
						if (!pLanding->GetIsDraw())
						{
							pLanding->SetIsDraw(true);
							pLanding->SetPosition(transform_.position_.x, transform_.position_.y);
							HitLanding = true;
							PlaySoundMem(LandingHandle, DX_PLAYTYPE_BACK);
						}
					}
			}
		}
		else 
		{
			onGround = false;
			HitLanding = false;
			hasLanded = false; // 地面から離れたらフラグをリセット
		}
	}
	//-----------------------------------------------------------

	//天気を変える　Controller & keyboard
	//一回だけ初期化
	if (pWCE_ == nullptr)
	{
		pWCE_ = Instantiate<WeatherChangeEffect>(GetParent());
	}

	if (input.Buttons[0] || CheckHitKey(KEY_INPUT_UP))//↑晴れにする
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

				//WeatherChangeEffect* pWCE = Instantiate<WeatherChangeEffect>(this);
				if (pWCE_ != nullptr) {
					if (!pWCE_->GetIsDraw()) {
						pWCE_->SetIsDraw(true);
						pWCE_->SetPosition(transform_.position_.x, transform_.position_.y, transform_.position_.z);
					}
				}
			}

		}
	}
	else if (input.Buttons[2] || CheckHitKey(KEY_INPUT_LEFT))//←雨にする
	{

		if (CanChangeWeather && pWeather != nullptr)
		{
			// 現在の天候状態を取得
			WeatherState WeatherState = pWeather->GetWeatherState();

			if (WeatherState != Rain)//雨以外なら
			{
				PlaySoundMem(RainHandle, DX_PLAYTYPE_BACK);
				ChangeWeatherCoolTime = 60;
				CanChangeWeather = false;
				pWeather->SetWeather(Rain);

				StopSoundMem(SnowHandle);
				StopSoundMem(WindHandle);
				//WeatherChangeEffect* pWCE = Instantiate<WeatherChangeEffect>(this);
				if (pWCE_ != nullptr) {
					if (!pWCE_->GetIsDraw()) {
						pWCE_->SetIsDraw(true);
						pWCE_->SetPosition(transform_.position_.x, transform_.position_.y, transform_.position_.z);
					}
				}
			}
		}
	}
	else if (input.Buttons[3] || CheckHitKey(KEY_INPUT_RIGHT))//→雪にする
	{
		if (CanChangeWeather && pWeather != nullptr)
		{
			// 現在の天候状態を取得
			WeatherState WeatherState = pWeather->GetWeatherState();

			if (WeatherState != Snow)//風以外なら
			{
				PlaySoundMem(FreezeHandle, DX_PLAYTYPE_BACK);
				PlaySoundMem(SnowHandle, DX_PLAYTYPE_BACK);
				ChangeWeatherCoolTime = 60;
				CanChangeWeather = false;
				pWeather->SetWeather(Snow);

				StopSoundMem(RainHandle);
				StopSoundMem(WindHandle);

				//WeatherChangeEffect* pWCE = Instantiate<WeatherChangeEffect>(this);
				if (pWCE_ != nullptr) {
					if (!pWCE_->GetIsDraw()) {
						pWCE_->SetIsDraw(true);
						pWCE_->SetPosition(transform_.position_.x, transform_.position_.y, transform_.position_.z);
					}
				}
			}
		}
	}
	else if (input.Buttons[1] || CheckHitKey(KEY_INPUT_DOWN))//↓風にする
	{
		if (CanChangeWeather && pWeather != nullptr)
		{
			// 現在の天候状態を取得
			WeatherState WeatherState = pWeather->GetWeatherState();

			if (WeatherState != Gale)//雪以外なら
			{
				PlaySoundMem(SpeedUpHandle, DX_PLAYTYPE_BACK);
				PlaySoundMem(WindHandle, DX_PLAYTYPE_BACK);
				ChangeWeatherCoolTime = 60;
				CanChangeWeather = false;
				pWeather->SetWeather(Gale);

				StopSoundMem(RainHandle);
				StopSoundMem(SnowHandle);

				//WeatherChangeEffect* pWCE = Instantiate<WeatherChangeEffect>(this);
				if (pWCE_ != nullptr) {
					if (!pWCE_->GetIsDraw()) {
						pWCE_->SetIsDraw(true);
						pWCE_->SetPosition(transform_.position_.x, transform_.position_.y, transform_.position_.z);
					}
				}
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
		//Gale MP Management
		if (pWeather->GetWeatherState() == Gale) //風の機能
		{
			GaleEffect(Gale);
			if (MagicPoint_ > 0)
			{
				if (GaleTime_ < 0)//約5秒ごとに行う処理
				{
					GaleTime_ = 420;
					MagicDown(2);//消費量は要調整
				}
				else
				{
					GaleTime_--;
				}
			}
		}

		//Rain MP Management
		if (pWeather->GetWeatherState() == Rain)
		{

			if (MagicPoint_ > 0)
			{

				if (RainTime_ < 0)//約5秒ごとに行う処理
				{
					MagicDown(1);
					/*RainTime_ = 10;*/
					RainTime_ = 420;
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
			//一回だけ初期化
			if (pMagic_ == nullptr)
			{
				pMagic_ = Instantiate<Magic>(GetParent());
			}

			if (pMagic_ != nullptr)
			{
				if (!pMagic_->GetIsDraw()) 
				{
					pMagic_->SetIsDraw(true);
					pMagic_->SetMagicStateMove();
					pMagic_->SetPosition(transform_.position_.x, transform_.position_.y);
					VECTOR dir = { 0.0f, 0.0f };
					if (IsTurnLeft)
					{
						dir.x = -1.0f;
					}
					else
					{
						dir.x = 1.0f;
					}
					pMagic_->SetDirection(dir);
					pMagic_->SetSpeed(5.5f);
				}
			}
			CoolDownMagic_ = timer_;

			mp->SetGaugeVal(MagicPoint_, MAX_MAGIC_POINT);
			MagicPoint_--;

			PlaySoundMem(MagicHandle, DX_PLAYTYPE_BACK);

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

		if (pSlime->ColliderRect(x + pSlime->GetScale().x, y + pSlime->GetScale().y, 42.0f, 42.0f))
		{
			if (y + 42.0f + pSlime->GetScale().x <= pSlime->GetPosition().y + 42 - (42.0f * pSlime->GetScale().y) / 2) // プレイヤーがスライムの上部にある
			{
				WeatherState WeatherState = pWeather->GetWeatherState();
				float RainBound = 0.5; // 雨の日に発生するスライムの弾性
				if (WeatherState == Rain && MagicPoint_ > 0)
				{
					PlaySoundMem(HighBoundHandle, DX_PLAYTYPE_BACK);
					RainBound = 3.5f; // 雨の時のみジャンプ力を2.5倍
				}
				else
				{
					PlaySoundMem(BoundHandle, DX_PLAYTYPE_BACK);
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

					DamageSE();

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
		if (pEnemyMagic->GetIsDraw())
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

					DamageSE();

					NDTIME_ = 2.0f;//個々の数値で無敵時間がきまる
				}
				break;
			}
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

				DamageSE();

				NDTIME_ = 3.0f;
			}
			break;
		}
	}

	std::list<HealItem*> pHeals = GetParent()->FindGameObjects<HealItem>();
	for (HealItem* pHeal : pHeals)
	{
		float dx = pHeal->GetPosition().x + 32 - (transform_.position_.x + 32.0f);
		float dy = pHeal->GetPosition().y + 32 - (transform_.position_.y + 32.0f);

		float distance = sqrt(dx * dx + dy * dy);

		if (distance <= 42.0f)
		{
			PlaySoundMem(GetHPItemHandle, DX_PLAYTYPE_BACK); // 音声を再生
			Hp_GetFlag = true;
			if (Hp_ < 5)
			{

				hp->HeelHp();
				Hp_++;
			}
			pHeal->KillMe();
			Hp_GetFlag = true;
			UIGetTimer = 65;
			StringUi_Up = transform_.position_.y;
			break;
		}

	}

	std::list<MpItem*> pMps = GetParent()->FindGameObjects<MpItem>();
	for (MpItem* pMp : pMps)
	{
		float dx = pMp->GetPosition().x + 32 - (transform_.position_.x + 32.0f);
		float dy = pMp->GetPosition().y + 32 - (transform_.position_.y + 32.0f);

		float distance = sqrt(dx * dx + dy * dy);

		if (distance <= 42.0f)
		{

			if (!IsHitOneCount_) // アイテムを拾ったときに一度だけMagicPoint_を増やす
			{
				PlaySoundMem(GetMPItemHandle, DX_PLAYTYPE_BACK); // 音声を再生
				MagicUp(10);
				IsHitOneCount_ = true; // MagicPoint_を増やした後はIsHitOneCount_をtrueに設定
			}
			pMp->KillMe();
			Mp_GetFlag = true;
			UIGetTimer = 65;
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
			if (dy <= 0 && abs(dx) <= 32.0f)
			{
				transform_.position_.y = pRock->GetPosition().y - 64 + push;
				onGround = true;
				onRock = true;
			}
			else if (dy > 0 && abs(dx) <= 32.0f)
			{
				transform_.position_.y = pRock->GetPosition().y + push;
			}
			else if (dx < 0 && abs(dy) <= 32.0f)
			{
				transform_.position_.x += push;
			}
			else if (dx > 0 && abs(dy) <= 32.0f)
			{
				transform_.position_.x -= push;
			}
		}

		Field* pField = GetParent()->FindGameObject<Field>();
		if (pField != nullptr)
		{
			int hitX = pRock->GetPosition().x + 32;
			int hitY = pRock->GetPosition().y + 32;

			if (pField->CollisionLeft(hitX, hitY) > 0 || pField->CollisionRight(hitX, hitY) > 0 ||
				pField->CollisionUp(hitX, hitY) > 0 || pField->CollisionDown(hitX, hitY) > 0)
			{
				onRock = false;
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
		int playerY = (int)transform_.position_.y - 5;

		if (pField->IsHitClear(playerX, playerY))
		{
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			ClearFlag* pClearFlag = (ClearFlag*)FindObject("ClearFlag");

			PlaySoundMem(ClearHandle, DX_PLAYTYPE_BACK);

			if (pClearFlag != nullptr)
			{
				pClearFlag->KillMe();


				if (pSceneManager != nullptr)
				{
					// MPの保存
					int MpPass = MagicPoint_; // 現在のMPを変数に格納
					pSceneManager->SetMagicPoint(MpPass); // Set関数に保存
				}

				player_state = S_Clear;
				Instantiate<Logo>(this);
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
				if (mp != nullptr)
				{
					mp->SetGaugeVal(MagicPoint_, MAX_MAGIC_POINT);
				}

				if (Hp_ >= 2)
				{
					HpDown(1);
					PlaySoundMem(DamageHandle, DX_PLAYTYPE_BACK);
				}
			}
			else
			{
				MagicPoint_ = 0;//10より少なかったら0に
			}
			CountSnowFlame = MAX_SNOW_FLAME; //元に戻す
		}

		if (CheckHitKey(KEY_INPUT_P))
		{
			CheckWall(pField);
		}
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

	///アニメーション終了後消える
	if (animeFrame >= 7)
	{
		player_animation_state = S_Erase_A;
		player_state = S_Erase;
		animeFrame = 7;
		flameCounter = 0;
	}
}

void Player::Jump()
{
	Jump_P = -sqrtf(2 * GRAVITY * JUMP_HEIGHT + WeatherSpeed_); // プレイヤーをジャンプさせる
	onGround = false;
	onRock = false;
	HitLanding = false;
	PlaySoundMem(JumpHandle, DX_PLAYTYPE_BACK); // 音声を再生
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
	//PlaySoundMem(GetItemSound, DX_PLAYTYPE_BACK);
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

	if (Hp_ == 1)
	{
		PlaySoundMem(WarningHandle, DX_PLAYTYPE_BACK);
	}

}

void Player::WhereIs()
{
	//横線関連
	static int SenStart = 1000; //横線の始点x
	static int SenLength = 200; //横線の長さx
	static int SenY = 50; //横線の始点y
	static int SenHeight = 5; //横線の幅
	static int WakuX = 20; //枠の調整用x
	static int WakuY = 20; //枠の調整用y
	static int FRAME = 3; //枠の太さ
	//↓定数にすべきだな...
	static unsigned int WHITE = GetColor(255, 255, 255); //白
	static unsigned int YELLOW = GetColor(255, 255, 0); //黄色
	static unsigned int GRAY = GetColor(128, 128, 128); //灰色
	static unsigned int BLUE = GetColor(65, 105, 225); //青
	static unsigned int GREEN = GetColor(59, 175, 117); //緑
	static unsigned int BLACK = GetColor(0, 0, 0); //黒


	//フレーム
	DrawBox(SenStart - WakuX - FRAME, SenY - WakuY - 7 - FRAME, SenStart + SenLength + WakuX + FRAME, SenY + SenHeight + WakuY - 7 + FRAME, BLACK, true);
	//後ろの箱
	DrawBox(SenStart - WakuX, SenY - WakuY - 7, SenStart + SenLength + WakuX, SenY + SenHeight + WakuY - 7, WHITE, true);
	//元の横線
	DrawBox(SenStart, SenY, SenStart + SenLength, SenY + SenHeight, GRAY, true);

	//三角形関連
	Field* pField = GetParent()->FindGameObject<Field>();
	float max = CHIP_SIZE * pField->GetGoalWidth();
	float now = transform_.position_.x;
	float nowLine = SenStart + SenLength * (now / max) * 2; //縦線引くところのX
	if (nowLine >= SenStart + SenLength)
	{
		nowLine = SenStart + SenLength; //マップは続くがゴールしたら縦線は動かない
	}
	//三角
	DrawTriangle(nowLine - 4, SenY - 14, (nowLine - 4 + nowLine + SenHeight + 4) / 2, (SenY - 10 + SenY + 14) / 2, nowLine + SenHeight + 4, SenY - 14, BLUE, true); //三角形かく
	//色変え
	DrawBox(SenStart, SenY, nowLine + 2, SenY + SenHeight, BLUE, true); //横線かく
	//ゴール
	DrawRotaGraph(SenStart + SenLength + 2, SenY - 9, 0.75, 0, hGoal, true);
}

void Player::UpdateErase()
{
	Field* pField = GetParent()->FindGameObject<Field>();
	if (++flameCounter >= 60)
	{
		//死んだときプレイの時のBGM
		pField->StopPlayBGM();

		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
		StopWeatherSE();
		flameCounter = 0;
	}
}

void Player::UpdateClear()
{
	if (++flameCounter >= 240)
	{
		flameCounter = 0;
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		Field* pField = GetParent()->FindGameObject<Field>();
		if (pSceneManager != nullptr)
		{
			pField->StopPlayBGM();
			//pSceneManager->ClearCountPlus();
			pSceneManager->ChangeScene(SCENE_ID_CLEAR);

			StopWeatherSE();
		}
	}
}

void Player::CheckWall(Field* pf)
{
	bool wallNow = pf->IsWallBlock(transform_.position_.x, transform_.position_.y);

	if (wallNow)
	{
		transform_.position_.x -= 32;
	}
}

//風の影響
void Player::GaleEffect(WeatherState state)
{
	Camera* cam = GetParent()->FindGameObject<Camera>();
	Rock* pRock = GetParent()->FindGameObject<Rock>();

	// xboxコントローラーの入力情報を取得
	padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);

	if (cam != nullptr)
	{
		// カメラの位置を取得
		int camX = cam->GetValue();

		//岩の上に乗る処理
		if (onRock == true)
		{
			if (state == Gale)
			{
				int MpVanish = GetMp();
				if (MpVanish >= 4)
				{
					if (input.ThumbRX <= -10000 || CheckHitKey(KEY_INPUT_K))
					{
						transform_.position_.x -= 1.2f;
					}
					else if (input.ThumbRX >= 10000 || CheckHitKey(KEY_INPUT_L))
					{
						transform_.position_.x += 1.2f;
					}
				}
			}
		}
	}
}

//vector<Magic*> Player::GetMagicBlank()
//{
//	return Magics_;
//}


