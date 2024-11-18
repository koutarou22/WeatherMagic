#include "WeatherBackGround.h"
#include "Camera.h"
#include "Player.h"

namespace
{
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	const int Size = 64;
	const int RAIN_SIZE = 64;
}



WeatherBackGround::WeatherBackGround(GameObject* parent)
	:GameObject(parent, "WeatherBackGround"), hImage_Sun(-1), hImage_Rain(-1), hImage_Gale(-1),hImage_Snow(-1),animeFrame(0), FrameCounter(0), eraseCounter(0)
{

	/*hImage_Sun = LoadGraph("");
	assert(hImage_Sun > 0);*/
	hImage_Rain = LoadGraph("Assets/BackAnimation/Rain_Back.png");
	assert(hImage_Rain > 0);

	hImage_Rain2 = LoadGraph("Assets/BackAnimation/Rain_Front.png");
	assert(hImage_Rain2 > 0);

	hImage_Gale = LoadGraph("Assets/BackAnimation/GaleAnimation.png");
	assert(hImage_Gale > 0);

	hImage_Snow = LoadGraph("Assets/BackAnimation/SnowAnimation.png");
	assert(hImage_Snow);
}

WeatherBackGround::~WeatherBackGround()
{
	if (hImage_Sun > 0)
	{
		DeleteGraph(hImage_Sun);
	}
	if (hImage_Rain > 0)
	{
		DeleteGraph(hImage_Rain);
	}
	if (hImage_Gale > 0)
	{
		DeleteGraph(hImage_Gale);
	}
	if (hImage_Snow > 0)
	{
		DeleteGraph(hImage_Snow);
	}
}

void WeatherBackGround::Update()
{
	//WeatherStateConfirm(Sun, SunNow, 0, 0); 
	WeatherStateConfirm(Rain, RainNow, 24, 10); 
	WeatherStateConfirm(Gale, GaleNow, 24, 6); 
	WeatherStateConfirm(Snow, SnowNow, 24, 16);
}

void WeatherBackGround::Draw()
{
	WeatherAnimation(RainNow, 128, hImage_Rain, 64);
	WeatherAnimation(RainNow, 128, hImage_Rain2, 128);
	GaleAnimation(GaleNow, 128, hImage_Gale, 5076/6, 512);
	WeatherAnimation(SnowNow, 128, hImage_Snow, 64);	
}

void WeatherBackGround::Release()
{
}

void WeatherBackGround::WeatherStateConfirm(WeatherState State, bool& Flag, int frameCount, int Frame)
{
	Weather* pWeather = GetParent()->FindGameObject<Weather>(); 
	if (pWeather->GetWeatherState() == State)
	{
		if (frameCount > 0)
		{
			if (++FrameCounter >= frameCount)
			{
				animeFrame = (animeFrame + 1) % Frame;
				FrameCounter = 0;
			}
		}
		Flag = true;
	}
	else
	{
		Flag = false;
	}
}

void WeatherBackGround::WeatherAnimation(bool& flag, int alpha, int hImage, int Size)
{
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

	if (flag)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		for (int y = 0; y < SCREEN_HEIGHT; y += Size)
		{
			for (int x = 0; x < SCREEN_WIDTH; x += Size)
			{
				DrawRectGraph(x - CameraSet, y, animeFrame * Size, 0, Size, Size, hImage, TRUE);
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);//Œ³‚É–ß‚·
	}
}

void WeatherBackGround::GaleAnimation(bool& flag, int alpha, int hImage, int SizeX, int SizeY)
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Weather* pWeather = GetParent()->FindGameObject<Weather>();
	Camera* cam = GetParent()->FindGameObject<Camera>();
	Player* pPlayer = GetParent()->FindGameObject<Player>();
	padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);

	int CameraSet = 0;
	if (cam != nullptr)
	{
		//x -= cam->GetValue();
		CameraSet = 0;
	}

	if (flag)
	{
		int MpVanish = pPlayer->GetMp();
		if (MpVanish >= 4)
		{  
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			// “ü—Í•ûŒü‚É‰ž‚¶‚Ä”½“]
			if (input.ThumbRX <= -10000 || CheckHitKey(KEY_INPUT_K))
			{
				// ¶‚É”½“]
				DrawRectGraph(x  - CameraSet, y + 100, animeFrame * SizeX, 0, SizeX, SizeY, hImage, TRUE, TRUE);
			}
			else if (input.ThumbRX >= 10000 || CheckHitKey(KEY_INPUT_L))
			{
				// ‰E‚É”½“]‚µ‚È‚¢
				DrawRectGraph(x + 500- CameraSet, y + 100, animeFrame * SizeX, 0, SizeX, SizeY, hImage, TRUE, FALSE);
			}

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha); // Œ³‚É–ß‚·
		}
	}
}
