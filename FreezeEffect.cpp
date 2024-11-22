#include "FreezeEffect.h"
#include "Camera.h"
#include "Weather.h"
FreezeEffect::FreezeEffect(GameObject* parent) : GameObject(parent, "FreezeEffect"), hImage_(-1), animeFrame(0), FrameCounter(0), eraseCounter(0), ReverseFrame(false)
{
    hImage_ = LoadGraph("Assets/Effect/Ice.png");
    assert(hImage_ > 0);
}

FreezeEffect::~FreezeEffect()
{
}

void FreezeEffect::Update()
{
    Weather* pWeather = GetParent()->FindGameObject<Weather>();

    if (pWeather->GetWeatherState() != WeatherState::Snow)
    {
        ReverseFrame = true;
    }
    else
    {
        ReverseFrame = false;
    }

    if (++FrameCounter >= 16)
    {
        if (ReverseFrame)
        {
            animeFrame--;
            if (animeFrame < 5)
            {
                animeFrame = 5; 
                KillMe();
            }
        }
        else
        {
            animeFrame++;
            if (animeFrame >= 8)
            {
                animeFrame = 7; 
            }
        }
        FrameCounter = 0;
    }
}

void FreezeEffect::Draw()
{
    int x = transform_.position_.x;
    int y = transform_.position_.y;

    Camera* cam = GetParent()->FindGameObject<Camera>();
    if (cam != nullptr) 
    {
        x -= cam->GetValue();
    }

    int FrameX = 64; 
    int FrameY = 64; 

    DrawRectGraph(x, y, animeFrame * FrameX, 0, FrameX, FrameY, hImage_, TRUE);
}

void FreezeEffect::Release()
{

}

void FreezeEffect::SetPosition(int x, int y)
{
    transform_.position_.x = x+10;
    transform_.position_.y = y+2;
}
