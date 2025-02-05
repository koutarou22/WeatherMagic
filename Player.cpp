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

namespace
{
	//移動速度
	const float MOVE_SPEED = 4.5f;


	//スタート時の初期位置
	const float START_POSITION_X = 100.0f;
	const float START_POSITION_Y = 605.0f;

	//ジャンプの高さ
	const float JUMP_HEIGHT = 64.0f * 1.45f;

	//重力
	const float GRAVITY = 9.8f / 60.0f;

	//最大の重力値
	const float MAX_GRAVITY = 6.0f;

	//最大MP
	const int MAX_MAGIC_POINT = 100;

	//最大HP
	const int MAX_DAMAGE_HP = 5;

	//時間経過でMPを減少させるフレーム
	const float MAX_SNOW_FLAME = 120.0f * 10.0f;
	const float MAX_RAIN_FLAME = 420.0f;
	const float MAX_GALE_FLAME = 300.0f;


	const float CHIP_SIZE = 64.0f;  
	const float DEAD_LINE = 800.0f;

};
Player::Player(GameObject* parent) : GameObject(sceneTop),
WeatherSpeed_(MOVE_SPEED), ChangeWeatherCoolTime_(60), CanChangeWeather_(true)

,InvincibleTime_(2.0f),FlashCount_(0), Hp_(5),MagicPoint_(100), MpHealTimer_(30)

,OnGround_(true), OnRock_(false),HitLanding_(true)

,FlameCounter_(0),AnimType_(0),AnimeFrame_(0)
{
	hPlayer_ = LoadGraph("Assets/Chara/Clear_Wizard.png");
	assert(hPlayer_ > 0);

	hGoal_ = LoadGraph("Assets/Item/GoalFlag.png");
	assert(hGoal_ > 0);

	pLanding = nullptr;

	transform_.position_ = { START_POSITION_X,START_POSITION_Y,0 };

	CharUp_ = transform_.position_.y;
	
	GaleFlameDownMp_ = MAX_GALE_FLAME;
	RainFlameDownMp_ = MAX_RAIN_FLAME;
	SnowFlameDownMp_ = MAX_SNOW_FLAME;


	HpGetFlag_ = false;
	HpGetFlag_ = false;
	IsTurnLeft = false;
	MultiDeadSE_ = false;

	stickTilt.IsLeftStickTilt_left = false;
	stickTilt.IsLeftStickTilt_right = false;
	stickTilt.IsRightStickTilt_left = false;
	stickTilt.IsRightStickTilt_right = false;


	//天候音の登録

	RainSound_ = LoadSoundMem("Assets/Music/SE/Weather/Rain.mp3");
	assert(RainSound_ != -1);

	WindSound_ = LoadSoundMem("Assets/Music/SE/Weather/Wind.mp3");
	assert(WindSound_ != -1);

	SnowSound_ = LoadSoundMem("Assets/Music/SE/Weather/Snow.mp3");
	assert(SnowSound_ != -1);

	//アイテム取得音の登録

	GetMPItemSound_ = LoadSoundMem("Assets/Music/SE/Player/GetMPItem.mp3");
	assert(GetMPItemSound_ != -1);

	GetHPItemSound_ = LoadSoundMem("Assets/Music/SE/Player/GetHPItem.mp3");
	assert(GetHPItemSound_ != -1);

	//基本的な動作音の登録
	
	//攻撃音
	MagicSound_ = LoadSoundMem("Assets/Music/SE/Player/AttackMagic.mp3");
	assert(MagicSound_ != -1);

	//ジャンプ音
	JumpSound_ = LoadSoundMem("Assets/Music/SE/Player/Jump.mp3");
	assert(JumpSound_ != -1);

	//着地音
	LandingSound_ = LoadSoundMem("Assets/Music/SE/Player/Landing.mp3");
	assert(LandingSound_ != -1);

	//ダメージ音
	DamageSound_ = LoadSoundMem("Assets/Music/SE/Player/Damage.mp3");
	assert(DamageSound_ != -1);

	//HPが1になった時の警告音
	WarningSound_ = LoadSoundMem("Assets/Music/SE/Player/Crisis.mp3");
	assert(WarningSound_ != -1);

	//死亡時の音
	DieSound_ = LoadSoundMem("Assets/Music/SE/Player/Die.mp3");
	assert(DieSound_ != -1);

	//スピードアップ音
	SpeedUpSound_ = LoadSoundMem("Assets/Music/SE/Weather/SpeedUp.mp3");
	assert(SpeedUpSound_ != -1);

	//特殊な音の登録
	
	//スライムバウンド音
	BoundSound_ = LoadSoundMem("Assets/Music/SE/Slime/Bound.mp3");
	assert(BoundSound_ != -1);

	//雨の日の時のスライムバウンド音
	HighBoundSound_ = LoadSoundMem("Assets/Music/SE/Slime/HighBound.mp3");
	assert(HighBoundSound_ != -1);

	//雪の時凍ってることがわかるSE
	FreezeSound_ = LoadSoundMem("Assets/Music/SE/Weather/Freeze.mp3");
	assert(FreezeSound_ != -1);

	ClearSound_ = LoadSoundMem("Assets/Music/SE/Player/Clear3.mp3");
	assert(ClearSound_ != -1);

	ChangeVolumeSoundMem(HighBoundSound_, 200);

}

Player::~Player()
{

}

void Player::Release()
{
	if (hPlayer_ > 0)
	{
		DeleteGraph(hPlayer_);
	}
	if (hGoal_ > 0)
	{
		DeleteGraph(hGoal_);
	}

	if (RainSound_ > 0)
	{
		DeleteSoundMem(RainSound_);
	}
	if (WindSound_ > 0)
	{
		DeleteSoundMem(WindSound_);
	}
	if (SnowSound_ > 0)
	{
		DeleteSoundMem(SnowSound_);
	}

	if (GetMPItemSound_ > 0)
	{
		DeleteSoundMem(GetMPItemSound_);
	}
	if (GetHPItemSound_ > 0)
	{
		DeleteSoundMem(GetHPItemSound_);
	}


	if (MagicSound_ > 0)
	{
		DeleteSoundMem(MagicSound_);
	}
	if (JumpSound_ > 0)
	{
		DeleteSoundMem(JumpSound_);
	}
	if (LandingSound_ > 0)
	{
		DeleteSoundMem(LandingSound_);
	}
	if (DamageSound_ > 0)
	{
		DeleteSoundMem(DamageSound_);
	}
	if (WarningSound_ > 0)
	{
		DeleteSoundMem(WarningSound_);
	}
	if (DieSound_ > 0)
	{
		DeleteSoundMem(DieSound_);
	}
	if (SpeedUpSound_ > 0)
	{
		DeleteSoundMem(SpeedUpSound_);
	}
	if (BoundSound_ > 0)
	{
		DeleteSoundMem(BoundSound_);
	}
	if (FreezeSound_ > 0)
	{
		DeleteSoundMem(FreezeSound_);
	}
	if (FreezeSound_ > 0)
	{
		DeleteSoundMem(FreezeSound_);
	}
	if (ClearSound_ > 0)
	{
		DeleteSoundMem(ClearSound_);
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

	switch (player_animation_state)
	{
	case Player::S_Walk_A:
	{
		if (InvincibleTime_ <= 0.0f)
		{
			if (IsTurnLeft)
			{
				DrawRectGraph(x, y, AnimeFrame_ * 64, AnimType_ * 64, 64, 64, hPlayer_, TRUE, 1, 0);//1...左右反転on 0...上下反転off
			}
			else
			{
				DrawRectGraph(x, y, AnimeFrame_ * 64, AnimType_ * 64, 64, 64, hPlayer_, TRUE);
			}

		}
		else
		{
			if (FlashCount_ % 10 == 0)
			{
				if (IsTurnLeft)
				{
					DrawRectGraph(x, y, AnimeFrame_ * 64, AnimType_ * 64, 64, 64, hPlayer_, TRUE, 1, 0);
				}
				else
				{
					DrawRectGraph(x, y, AnimeFrame_ * 64, AnimType_ * 64, 64, 64, hPlayer_, TRUE);
				}
			}
		}
		++FlashCount_;
		break;
	}
	case Player::S_Damage_A:

		if (IsTurnLeft)
		{
			DrawRectGraph(x, y, 2 * 64, AnimType_ * 64, 64, 64, hPlayer_, TRUE, 1, 0);
		}
		else
		{
			DrawRectGraph(x, y, 2 * 64, AnimType_ * 64, 64, 64, hPlayer_, TRUE);
		}

		break;
	case Player::S_Dead_A:

		if (IsTurnLeft)
		{
			DrawRectGraph(x, y, AnimeFrame_ * 64, AnimType_ * 64, 64, 64, hPlayer_, TRUE, 1, 0);
			if (!MultiDeadSE_)
			{
				PlaySoundMem(DieSound_, DX_PLAYTYPE_BACK); // 音声を再生
				MultiDeadSE_ = true;
			}
		}
		else
		{
			DrawRectGraph(x, y, AnimeFrame_ * 64, AnimType_ * 64, 64, 64, hPlayer_, TRUE);
			if (!MultiDeadSE_)
			{
				PlaySoundMem(DieSound_, DX_PLAYTYPE_BACK); // 音声を再生
				MultiDeadSE_ = true;
			}
		}
		break;
	case Player::S_Erase_A:
		break;
	default:
		break;

	}
	if (MpGetFlag_ == true)
	{
		if (ItemGetTimer_ > 0)
		{
			DrawFormatString(x, CharUp_, GetColor(255, 255, 255), "MP+10");

			CharUp_ -= 1;
			ItemGetTimer_--;
		}
		else
		{
			MpGetFlag_ = false;
		}
	}

	if (HpGetFlag_ == true)
	{
		if (ItemGetTimer_ > 0)
		{
			DrawFormatString(x, CharUp_, GetColor(255, 255, 255), "HP+2");
			CharUp_ -= 1;
			ItemGetTimer_--;
		}
		else
		{
			HpGetFlag_ = false;
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


	WhereIs();

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
	PlaySoundMem(DamageSound_, DX_PLAYTYPE_BACK);
}

void Player::StopWeatherSE()
{
	if (CheckSoundMem(RainSound_) == 1)
	{
		StopSoundMem(RainSound_);
	}
	if (CheckSoundMem(WindSound_) == 1)
	{
		StopSoundMem(WindSound_);
	}
	if (CheckSoundMem(SnowSound_) == 1)
	{
		StopSoundMem(SnowSound_);
	}
}

/// <summary>
/// sticktiltの構造体の変数を設定（各フレーム）
/// </summary>
void Player::StickTiltCheck()
{
	//左スティックを倒してる方向にtrue
	if (Input_.ThumbLX <= -10000)
	{
		stickTilt.IsLeftStickTilt_left = true;
	}
	else if (Input_.ThumbLX >= 10000)
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
	Rock* pRock = GetParent()->FindGameObject<Rock>();
	Hp* hp = GetParent()->FindGameObject<Hp>();
	MP* mp = GetParent()->FindGameObject<MP>();


	//xboxコントローラーの入力情報を取得
	PadAnalogInput_ = GetJoypadXInputState(DX_INPUT_PAD1, &Input_);
	StickTiltCheck();

	SetFontSize(24);

	WeatherController();
	PlayerController();
	
	HitSlime();
	HitGhost();
	HitRock();
	HitItem();

	HitClear();

	HitStageDown();
	HitStageUp();

	

}
void Player::UpdateDamage()
{
	AnimeFrame_ = 2;
	if (++FlameCounter_ >= 24)
	{
		player_state = S_WaIk;
		player_animation_state = S_Walk_A;
		AnimeFrame_ = 0;
	}
}

void Player::UpdateDead()
{
	//死亡のアニメーション
	if (++FlameCounter_ >= 30)
	{
		AnimeFrame_++;
		FlameCounter_ = 0;
	}

	///アニメーション終了後消える
	if (AnimeFrame_ >= 7)
	{
		player_animation_state = S_Erase_A;
		player_state = S_Erase;
		AnimeFrame_ = 7;
		FlameCounter_ = 0;
	}
}

void Player::Jump()
{
	JumpPower_ = -sqrtf(2 * GRAVITY * JUMP_HEIGHT + WeatherSpeed_); 
	OnGround_ = false;
	OnRock_ = false;
	HitLanding_ = false;
	PlaySoundMem(JumpSound_, DX_PLAYTYPE_BACK); 
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
		PlaySoundMem(WarningSound_, DX_PLAYTYPE_BACK);
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

	//色関連
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
	DrawRotaGraph(SenStart + SenLength + 2, SenY - 9, 0.75, 0, hGoal_, true);
}

void Player::UpdateErase()
{
	Field* pField = GetParent()->FindGameObject<Field>();
	if (++FlameCounter_ >= 60)
	{
		//死んだときプレイの時のBGM
		pField->StopPlayBGM();

		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
		StopWeatherSE();
		FlameCounter_ = 0;
	}
}

void Player::UpdateClear()
{
	if (++FlameCounter_ >= 240)
	{
		FlameCounter_ = 0;
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		Field* pField = GetParent()->FindGameObject<Field>();
		if (pSceneManager != nullptr)
		{
			pField->StopPlayBGM();
			pSceneManager->ClearCountPlus();
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



void Player::HitRock()
{

	Weather* pWeather = GetParent()->FindGameObject<Weather>();
	Field* pField = GetParent()->FindGameObject<Field>();

	std::list<Rock*> pRocks = GetParent()->FindGameObjects<Rock>();
	OnRock_ = false;
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
				OnGround_ = true;
				OnRock_ = true;
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

	
		if (pField != nullptr)
		{
			int HitX = pRock->GetPosition().x + 32;
			int HitY = pRock->GetPosition().y + 32;

			if (pField->CollisionLeft(HitX, HitY) > 0 || pField->CollisionRight(HitX, HitY) > 0 ||
				pField->CollisionUp(HitX, HitY) > 0 || pField->CollisionDown(HitX, HitY) > 0)
			{
				OnRock_ = false;
			}
		}
	}
}

void Player::HitGhost()
{
	Hp* hp = GetParent()->FindGameObject<Hp>();

	std::list<Ghost*> pGhosts = GetParent()->FindGameObjects<Ghost>();
	for (Ghost* pGhost : pGhosts)
	{
		float dx = pGhost->GetPosition().x + 42 - (transform_.position_.x + 32.0f);
		float dy = pGhost->GetPosition().y + 42 - (transform_.position_.y + 32.0f);

		float distance = sqrt(dx * dx + dy * dy);

		if (distance <= 40.0f)
		{
			if (InvincibleTime_ <= 0.0f)
			{
				hp->DamageHp();
				HpDown(1);

				DamageSE();

				InvincibleTime_ = 3.0f;
			}
			break;
		}
	}


	std::list<EnemyMagic*> pEMagics = GetParent()->FindGameObjects<EnemyMagic>();
	for (EnemyMagic* pEnemyMagic : pEMagics)
	{
		if (pEnemyMagic->GetIsDraw())
		{
			float dx = pEnemyMagic->GetPosition().x + 16 - (transform_.position_.x + 32.0f);//Mgの座標X - Slの座標X
			float dy = pEnemyMagic->GetPosition().y + 16 - (transform_.position_.y + 32.0f);//Mgの座標Y - Slの座標Y
			float distance = sqrt(dx * dx + dy * dy);

			if (distance <= 30.0f)
			{
				if (InvincibleTime_ <= 0.0f)
				{
					hp->DamageHp();
					HpDown(1);

					DamageSE();

					InvincibleTime_ = 2.0f;
				}
				break;
			}
		}
	}
}
void Player::HitSlime()
{
	Weather* pWeather = GetParent()->FindGameObject<Weather>();
	Hp* hp = GetParent()->FindGameObject<Hp>();

	std::list<Slime*> pSlimes = GetParent()->FindGameObjects<Slime>();

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
					PlaySoundMem(HighBoundSound_, DX_PLAYTYPE_BACK);
					RainBound = 3.5f; // 雨の時のみジャンプ力を2.5倍
				}
				else
				{
					PlaySoundMem(BoundSound_, DX_PLAYTYPE_BACK);
				}

				JumpPower_ = -sqrtf(2 * GRAVITY * JUMP_HEIGHT * RainBound);
				OnGround_ = false;
			}
			else
			{
				if (InvincibleTime_ <= 0.0f)
				{
					hp->DamageHp();
					HpDown(1);

					DamageSE();

					InvincibleTime_ = 3.0f;
					break; // ダメージを与えた後にループを抜ける
				}
			}
		}
	}
}
void Player::HitItem()
{
	Hp* hp = GetParent()->FindGameObject<Hp>();


	if (hp == nullptr)
	{
		return;
	}

	std::list<HealItem*> pHeals = GetParent()->FindGameObjects<HealItem>();
	for (HealItem* pHeal : pHeals)
	{
		float dx = pHeal->GetPosition().x + 32 - (transform_.position_.x + 32.0f);
		float dy = pHeal->GetPosition().y + 32 - (transform_.position_.y + 32.0f);

		float distance = sqrt(dx * dx + dy * dy);

		if (distance <= 42.0f)
		{
			PlaySoundMem(GetHPItemSound_, DX_PLAYTYPE_BACK); // 音声を再生
			HpGetFlag_ = true;
			if (Hp_ < 5)
			{

				hp->HeelHp();
				Hp_++;
			}
			pHeal->KillMe();
			HpGetFlag_ = true;
			ItemGetTimer_ = 65;
			CharUp_ = transform_.position_.y;
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

			if (!GetItemFlag_) // アイテムを拾ったときに一度だけMagicPoint_を増やす
			{
				PlaySoundMem(GetMPItemSound_, DX_PLAYTYPE_BACK); // 音声を再生
				MagicUp(10);
				GetItemFlag_ = true; // MagicPoint_を増やした後はGetItemFlag_をtrueに設定
			}
			pMp->KillMe();
			MpGetFlag_ = true;
			ItemGetTimer_ = 65;
			CharUp_ = transform_.position_.y;
		}
		else
		{
			GetItemFlag_ = false; // アイテムが範囲外になったらGetItemFlag_をfalseにリセット
		}
	}
}


void Player::GaleEffect(WeatherState state)
{
	Camera* cam = GetParent()->FindGameObject<Camera>();
	Rock* pRock = GetParent()->FindGameObject<Rock>();

	// xboxコントローラーの入力情報を取得
	PadAnalogInput_ = GetJoypadXInputState(DX_INPUT_PAD1, &Input_);

	if (cam != nullptr)
	{
		// カメラの位置を取得
		int camX = cam->GetValue();

		//岩の上に乗ってる時のみ座標を移動する
		if (OnRock_ == true)
		{
			if (state == Gale)
			{
				int MpVanish = GetMp();
				if (MpVanish >= 4)
				{
					if (Input_.ThumbRX <= -10000 || CheckHitKey(KEY_INPUT_K))
					{
						transform_.position_.x -= 1.2f;
					}
					else if (Input_.ThumbRX >= 10000 || CheckHitKey(KEY_INPUT_L))
					{
						transform_.position_.x += 1.2f;
					}
				}
			}
		}
	}
}

void Player::WeatherController()
{
	Weather* pWeather = GetParent()->FindGameObject<Weather>();
	MP* mp = GetParent()->FindGameObject<MP>();


	if (pWeather != nullptr)
	{
		WeatherEffects(pWeather);
	}

	//天気を変える　Controller & keyboard
    //一回だけ初期化
	if (pWCE_ == nullptr)
	{
		pWCE_ = Instantiate<WeatherChangeEffect>(GetParent());
	}

	if (Input_.Buttons[0] || CheckHitKey(KEY_INPUT_UP))//↑晴れにする
	{

		if (CanChangeWeather_ && pWeather != nullptr)
		{
			// 現在の天候状態を取得
			WeatherState WeatherState = pWeather->GetWeatherState();

			if (WeatherState != Sun)//晴れ以外なら
			{
				ChangeWeatherCoolTime_ = 60;
				CanChangeWeather_ = false;
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
	else if (Input_.Buttons[2] || CheckHitKey(KEY_INPUT_LEFT))//←雨にする
	{

		if (CanChangeWeather_ && pWeather != nullptr)
		{
			// 現在の天候状態を取得
			WeatherState WeatherState = pWeather->GetWeatherState();

			if (WeatherState != Rain)//雨以外なら
			{
				PlaySoundMem(RainSound_, DX_PLAYTYPE_BACK);
				ChangeWeatherCoolTime_ = 60;
				CanChangeWeather_ = false;
				pWeather->SetWeather(Rain);

				StopSoundMem(SnowSound_);
				StopSoundMem(WindSound_);
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
	else if (Input_.Buttons[3] || CheckHitKey(KEY_INPUT_RIGHT))//→雪にする
	{
		if (CanChangeWeather_ && pWeather != nullptr)
		{
			// 現在の天候状態を取得
			WeatherState WeatherState = pWeather->GetWeatherState();

			if (WeatherState != Snow)//風以外なら
			{
				PlaySoundMem(FreezeSound_, DX_PLAYTYPE_BACK);
				PlaySoundMem(SnowSound_, DX_PLAYTYPE_BACK);
				ChangeWeatherCoolTime_ = 60;
				CanChangeWeather_ = false;
				pWeather->SetWeather(Snow);

				StopSoundMem(RainSound_);
				StopSoundMem(WindSound_);

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
	else if (Input_.Buttons[1] || CheckHitKey(KEY_INPUT_DOWN))//↓風にする
	{
		if (CanChangeWeather_ && pWeather != nullptr)
		{
			// 現在の天候状態を取得
			WeatherState WeatherState = pWeather->GetWeatherState();

			if (WeatherState != Gale)//雪以外なら
			{
				PlaySoundMem(SpeedUpSound_, DX_PLAYTYPE_BACK);
				PlaySoundMem(WindSound_, DX_PLAYTYPE_BACK);
				ChangeWeatherCoolTime_ = 60;
				CanChangeWeather_ = false;
				pWeather->SetWeather(Gale);

				StopSoundMem(RainSound_);
				StopSoundMem(SnowSound_);

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
	//タイマーが切れてCanChangeWeather_ = trueになるまで再度天気の変更不可
	if (--ChangeWeatherCoolTime_ < 0)
	{
		CanChangeWeather_ = true;
	}

	if (pWeather != nullptr)
	{
		//Gale MP Management
		if (pWeather->GetWeatherState() == Gale) //風の機能
		{
			GaleEffect(Gale);
			if (MagicPoint_ > 0)
			{
				if (GaleFlameDownMp_ < 0)//約5秒ごとに行う処理
				{
					GaleFlameDownMp_ = MAX_GALE_FLAME;
					MagicDown(2);//消費量は要調整
				}
				else
				{
					GaleFlameDownMp_--;
				}
			}
		}

		//Rain MP Management
		if (pWeather->GetWeatherState() == Rain)
		{

			if (MagicPoint_ > 0)
			{

				if (RainFlameDownMp_ < 0)//約5秒ごとに行う処理
				{
					MagicDown(1);
					RainFlameDownMp_ = MAX_RAIN_FLAME;
				}
				else
				{
					RainFlameDownMp_--;
				}
			}
		}
	}


	//雪の時間経過(とりあえずフレーム経過)でMPが減る
	if (pWeather != nullptr)
	{
		if (pWeather->GetWeatherState() == WeatherState::Snow)
		{
			//フレーム基準だからなぁE..
			SnowFlameDownMp_--;
		}
	}

	//残りの雪時間が0以下だったら
	if (SnowFlameDownMp_ <= 0)
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
				PlaySoundMem(DamageSound_, DX_PLAYTYPE_BACK);
			}
		}
		else
		{
			MagicPoint_ = 0;//10より少なかったら0に
		}
		SnowFlameDownMp_ = MAX_SNOW_FLAME; //元に戻す
	}

}

void Player::PlayerController()
{
	
	MP* mp = GetParent()->FindGameObject<MP>();

	//Input_.ThumbLXで左スティック入力をとる 倒した横軸値が-10000以下か10000以上で動く
	//右移動
	if (CheckHitKey(KEY_INPUT_D) || stickTilt.IsLeftStickTilt_right)
	{
		IsTurnLeft = false;
		transform_.position_.x += WeatherSpeed_;
		if (++FlameCounter_ >= 24)
		{
			AnimeFrame_ = (AnimeFrame_ + 1) % 2;
			FlameCounter_ = 0;
		}

		HitStageRight();
		
	}
	//左移動
	else if (CheckHitKey(KEY_INPUT_A) || stickTilt.IsLeftStickTilt_left)
	{
		IsTurnLeft = true;
		transform_.position_.x -= WeatherSpeed_;
		if (++FlameCounter_ >= 24)
		{
			AnimeFrame_ = (AnimeFrame_ + 1) % 2;
			FlameCounter_ = 0;
		}

		HitStageLeft();
	
	}
	else
	{
		AnimeFrame_ = 0;
		FlameCounter_ = 0;
	}

	//ジャンプ
	if (CheckHitKey(KEY_INPUT_SPACE) || Input_.Buttons[12])//Aボタン
	{
		PictFlame_ = 80;

		if (prevSpaceKey_ == false)
		{
			if (OnGround_)
			{
				Jump();
			}
		}
		prevSpaceKey_ = true;
	}
	else
	{
		prevSpaceKey_ = false;
	}

	//攻撃
	if (CheckHitKey(KEY_INPUT_M) || Input_.Buttons[13])//bボタン
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
			CoolDownMagic_ = 90;

			mp->SetGaugeVal(MagicPoint_, MAX_MAGIC_POINT);
			MagicPoint_--;

			PlaySoundMem(MagicSound_, DX_PLAYTYPE_BACK);

		}
	}
	if (CoolDownMagic_ > 0)
	{
		CoolDownMagic_--;
	}

	//カメラの追従
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



	//画面外に行かないようにする処理
	if (transform_.position_.x < 0)
	{
		transform_.position_.x = 0;
	}

	//落下速度の上昇を制限する処理
	if (JumpPower_ > 20.0f)
	{
		JumpPower_ = 20.0f; // 落下速度が最大値を超えないように制限
	}

	//重力の処理
	JumpPower_ += GRAVITY; //速度 += 加速度
	if (JumpPower_ > MAX_GRAVITY)
	{
		JumpPower_ = MAX_GRAVITY;
	}
	transform_.position_.y += JumpPower_; //座標 += 速度


	// 無敵時間の更新
	if (InvincibleTime_ > 0.0f)
	{
		InvincibleTime_ -= 0.016f;
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

	//死亡したらゲームオーバー画面へ
	if (Hp_ <= 0 || transform_.position_.y > DEAD_LINE)
	{
		AnimeFrame_ = 5;
		FlameCounter_ = 0;
		player_animation_state = S_Dead_A;
		player_state = S_Dead;
		//isDead_ = true;
	}
}

void Player::HitClear()
{

	Field* pField = GetParent()->FindGameObject<Field>();

	if (pField != nullptr)
	{
		int playerX = (int)transform_.position_.x;
		int playerY = (int)transform_.position_.y - 5;

		if (pField->IsHitClear(playerX, playerY))
		{
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			ClearFlag* pClearFlag = (ClearFlag*)FindObject("ClearFlag");

			PlaySoundMem(ClearSound_, DX_PLAYTYPE_BACK);

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

		if (CheckHitKey(KEY_INPUT_P))
		{
			CheckWall(pField);
		}
	}
}


void Player::HitStageRight()
{
	Field* pField = GetParent()->FindGameObject<Field>();

	//衝突判定(右)
	int HitX = transform_.position_.x + 50;
	int HitY = transform_.position_.y + 63;


	if (pField != nullptr)
	{
		int push = pField->CollisionRight(HitX, HitY);
		transform_.position_.x -= push;
	}
}
void Player::HitStageLeft()
{
	Field* pField = GetParent()->FindGameObject<Field>();

	//衝突判定(左)
	int HitX = transform_.position_.x;
	int HitY = transform_.position_.y + 63;
	if (pField != nullptr)
	{
		int push = pField->CollisionLeft(HitX, HitY);
		transform_.position_.x += push;
	}
}
void Player::HitStageUp()
{
	Field* pField = GetParent()->FindGameObject<Field>();

	//衝突判定(上)
	if (!OnGround_ && pField != nullptr)
	{
		int HitX = transform_.position_.x + 32;
		int HitY = transform_.position_.y;

		int push = pField->CollisionUp(HitX, HitY);
		if (push > 0) {
			JumpPower_ = 0.0f;
			transform_.position_.y += push;

		}
	}
}
void Player::HitStageDown()
{
	Field* pField = GetParent()->FindGameObject<Field>();

	//衝突判定(下)
	if (pField != nullptr)
	{
		int pushR = pField->CollisionDown(transform_.position_.x + 50, transform_.position_.y + 63);
		int pushL = pField->CollisionDown(transform_.position_.x + 14, transform_.position_.y + 63);
		int push = max(pushR, pushL);//２つの足元のめりこみの大きいほう
		if (push >= 1)
		{

			transform_.position_.y -= push - 1;
			JumpPower_ = 0.0f;
			if (!OnGround_ && GetParent() != nullptr)
			{

				OnGround_ = true;

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

						PlaySoundMem(LandingSound_, DX_PLAYTYPE_BACK);
					}
				}
			}
		}
		else
		{
			OnGround_ = false;
			HitLanding_ = false;
		}
	}

}