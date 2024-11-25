#include "FreezeEffect.h"
#include "Camera.h"
#include "Weather.h"
FreezeEffect::FreezeEffect(GameObject* parent) : GameObject(parent, "FreezeEffect"), hImage_(-1), animeFrame(0), FrameCounter(0), eraseCounter(0), ReverseFrame(false)
{
    hImage_ = LoadGraph("Assets/Effect/Ice.png");
   /* assert(hImage_ > 0);*/
    freeze_s = S_Freeze;
}

FreezeEffect::~FreezeEffect()
{
    Release();
}

void FreezeEffect::Update()
{
    switch (freeze_s)
    {
    case FreezeEffect::S_Freeze:
        UpdateFreeze();
        break;
    case FreezeEffect::S_MELT:
        UpdateMelt();
        break;
    case FreezeEffect::S_NONE:
        break;
    default:
        break;
    }
}

void FreezeEffect::UpdateFreeze()
{
    Weather* pWeather = GetParent()->FindGameObject<Weather>();

    if (pWeather->GetWeatherState() != WeatherState::Snow) {
        freeze_s = S_MELT;
        FrameCounter = 0;
    }

    if (++FrameCounter >= 16)
    {
        animeFrame++;
        if (animeFrame >= 8)//animeFrame‚ðŒÅ’è
        {
            animeFrame = 7;
        }
        FrameCounter = 0;
     }
}

void FreezeEffect::UpdateMelt()
{
    if (++FrameCounter >= 16)
    {
        animeFrame--;
        if (animeFrame <= 1)
        {
            animeFrame = 1;
            FrameCounter = 0;
            KillMe();
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
    if (hImage_ > 0)
    {
        DeleteGraph(hImage_);
    }
}

void FreezeEffect::SetPosition(int x, int y)
{
    transform_.position_.x = x+10;
    transform_.position_.y = y+2;
}
