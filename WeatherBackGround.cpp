#include "WeatherBackGround.h"
#include "Camera.h"
#include "Player.h"

namespace
{
	const int SCREEN_WIDTH = 1280; //スクリーンの横幅
	const int SCREEN_HEIGHT = 720; //スクリーンの縦幅
	const int GALE_MP = 4; //風に変えられる最小のMP
	const int ALPHA = 128; //アルファ値
	const int FRAME_COUNT = 24; //フレーム全体の数
	const int IMAGE_SIZE[STATE_NUM] = { 64,128,512,64 }; //エフェクト画像のサイズ
	const int GALE_SIZE_X = 5076 / 6; //風のエフェクト画像のサイズX
	const XMINT2 POS_MARGE = { 500,100 }; //表示座標の調整用
	const int MAX_INPUT = 10000; //コントローラーの入力取得上
	const int MIN_INPUT = -10000; //コントローラーの入力取得用下
}



WeatherBackGround::WeatherBackGround(GameObject* parent)
	:GameObject(parent, "WeatherBackGround")
{
	for (int i = 0; i < STATE_NUM; i++)
	{
		images_[i] = -1;
		nowWeather_[i] = false;
	}

	animeFrame_ = 0;
	frameCounter_ = 0;
	eraseCounter_ = 0;
}

WeatherBackGround::~WeatherBackGround()
{
	Release();
}

void WeatherBackGround::Initialize()
{
	images_[RAINBACK] = LoadGraph("Assets/BackAnimation/Rain_Back.png");
	assert(images_[RAINBACK] > 0);

	images_[RAINFRONT] = LoadGraph("Assets/BackAnimation/Rain_Front.png");
	assert(images_[RAINFRONT] > 0);

	images_[GALE] = LoadGraph("Assets/BackAnimation/GaleAnimation.png");
	assert(images_[GALE] > 0);

	images_[SNOW] = LoadGraph("Assets/BackAnimation/SnowAnimation.png");
	assert(images_[SNOW] > 0);
}

void WeatherBackGround::Update()
{
	WeatherStateConfirm(Rain, nowWeather_[RAINBACK], FRAME_COUNT, 10);
	WeatherStateConfirm(Gale, nowWeather_[GALE], FRAME_COUNT, 6);
	WeatherStateConfirm(Snow, nowWeather_[SNOW], FRAME_COUNT, 16);
}

void WeatherBackGround::Draw()
{
	WeatherAnimation(nowWeather_[RAINBACK], ALPHA, images_[RAINBACK], IMAGE_SIZE[RAINBACK]);
	WeatherAnimation(nowWeather_[RAINBACK], ALPHA, images_[RAINFRONT], IMAGE_SIZE[RAINFRONT]);
	GaleAnimation(nowWeather_[GALE], ALPHA, images_[GALE], GALE_SIZE_X, IMAGE_SIZE[GALE]);
	WeatherAnimation(nowWeather_[SNOW], ALPHA, images_[SNOW], IMAGE_SIZE[SNOW]);
}

void WeatherBackGround::Release()
{
	for (int i = 0; i < STATE_NUM; i++)
	{
		if (images_[i] > 0)
		{
			DeleteGraph(images_[i]);
			images_[i] = -1;
		}
	}
}

void WeatherBackGround::WeatherStateConfirm(WeatherState State, bool& Flag, int FrameCount, int Frame)
{
	//特定の天候かどうか(現在の天候がStateと同じか)確かめる
	Weather* pWeather = GetParent()->FindGameObject<Weather>(); 
	if (pWeather->GetWeatherState() == State)
	{
		if (FrameCount > 0)
		{
			if (++frameCounter_ >= FrameCount)
			{
				animeFrame_ = (animeFrame_ + 1) % Frame;
				frameCounter_ = 0;
			}
		}
		Flag = true;
	}
	else
	{
		Flag = false;
	}
}

void WeatherBackGround::WeatherAnimation(bool& flag, int alpha, int image, int size)
{
	//カメラ座標をとってくる
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	Weather* pWeather = GetParent()->FindGameObject<Weather>();
	Camera* cam = GetParent()->FindGameObject<Camera>();
	int CameraSet = 0;
	if (cam != nullptr)
	{
		x -= cam->GetValue();
		CameraSet = 0;
	}

	//天候に応じたエフェクトを描画
	if (flag)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		for (int y = 0; y < SCREEN_HEIGHT; y += size)
		{
			for (int x = 0; x < SCREEN_WIDTH; x += size)
			{
				DrawRectGraph(x - CameraSet, y, animeFrame_ * size, 0, size, size, image, TRUE);
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha); //元に戻す
	}
}

void WeatherBackGround::GaleAnimation(bool& flag, int alpha, int image, int SizeX, int SizeY)
{
	//カメラ座標をとってくる
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	Weather* pWeather = GetParent()->FindGameObject<Weather>();
	Camera* cam = GetParent()->FindGameObject<Camera>();
	Player* pPlayer = GetParent()->FindGameObject<Player>();
	padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);

	//岩を動かすときの風描画
	if (flag)
	{
		int MpVanish = pPlayer->GetMp();
		if (MpVanish >= GALE_MP) //Mpが残っているとき
		{  
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			//入力方向に応じて反転
			if (input.ThumbRX <= MIN_INPUT || CheckHitKey(KEY_INPUT_K))
			{
				//左に反転
				DrawRectGraph(x, y + POS_MARGE.y, animeFrame_ * SizeX, 0, SizeX, SizeY, image, TRUE, TRUE);
			}
			else if (input.ThumbRX >= MAX_INPUT || CheckHitKey(KEY_INPUT_L))
			{
				//反転しない
				DrawRectGraph(x + POS_MARGE.x, y + POS_MARGE.y, animeFrame_ * SizeX, 0, SizeX, SizeY, image, TRUE, FALSE);
			}

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha); // 元に戻す
		}
	}
}
