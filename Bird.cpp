#include "Bird.h"
#include <assert.h>
#include "Camera.h"
#include "Weather.h"


namespace
{
	static const int SCREEN_WIDTH = 1280;
}
Bird::Bird(GameObject* scene)
{
	hImage = LoadGraph("Assets/bird.png");
	assert(hImage > 0);
	transform_.position_.x = 800.0f;
	transform_.position_.y = 580.0f;
}

Bird::~Bird()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Bird::Update()
{
	int x = (int)transform_.position_.x;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		x -= cam->GetValue();
	}
	if (x > SCREEN_WIDTH)//即値、マジックナンバー
		return;
	else if (x < -64)
	{
		KillMe();
		return;
	}
	

	//天候取得、雪ならスピードを0に
	Weather* pWeather = GetParent()->FindGameObject<Weather>();
	if(pWeather->GetWeatherState()==WeatherState::Snow)
	{
		//敵のスピードを0にする
		//処理なしでよいか...?
	}
	else
	{
		transform_.position_.x -= 1.0f;
		sinAngle += 3.0f;
		float sinValue = sinf(sinAngle * DX_PI_F / 180.0f);
		transform_.position_.y = 500.0f + sinValue * 50.0f;
	}

	
}

void Bird::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	DrawRectGraph(x, y, 0, 0, 64, 64, hImage, TRUE);
	DrawCircle(x + 32.0f, y + 32.0f, 24.0f, GetColor(255, 0, 0), 0);
}

void Bird::SetPosition(int x, int y)
{
	transform_.position_.x = x;
	transform_.position_.y = y;
}

bool Bird::ColliderCircle(float x, float y, float r)
{
	//x,y,rが相手の円の情報
	//自分の円の情報
	float myCenterX = transform_.position_.x + 32.0f;
	float myCenterY = transform_.position_.y + 32.0f;
	float myR = 24.0f;
	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if (sqrt(dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}
