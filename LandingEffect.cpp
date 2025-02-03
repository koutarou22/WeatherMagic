#include "LandingEffect.h"
#include "Camera.h"
#include "Debug.h"


int LandingEffect::hImage_ = -1;

LandingEffect::LandingEffect(GameObject* parent) : GameObject(parent, "LandingEffect"), animeFrame(0), FrameCounter(0), eraseCounter(0), isActive_(true)
{
    if (hImage_ == -1) 
    {
        hImage_ = LoadGraph("Assets/Effect/landing1.png");
        assert(hImage_ > 0);
    }
}

LandingEffect::~LandingEffect()
{
    if (hImage_ > 0)
    {
        DeleteGraph(hImage_);
        hImage_ = -1;
    }
}

void LandingEffect::Update()
{
    if (!isActive_) return;
        if (++FrameCounter >= 4)
        {
            animeFrame = (animeFrame + 1) % 7;
            FrameCounter = 0;
            eraseCounter++;
        }

        if (eraseCounter >= 7)
        {
            Deactivate();
        }
}

void LandingEffect::Draw()
{
    if (!isActive_) return;

    int x = (int)transform_.position_.x;
    int y = (int)transform_.position_.y;

    Camera* cam = GetParent()->FindGameObject<Camera>();
    if (cam != nullptr) {
        x -= cam->GetValue();
    }

    int FrameX = 64;
    int FrameY = 32;

    DrawRectGraph(x, y, animeFrame * FrameX, 0, FrameX, FrameY, hImage_, TRUE);
}

void LandingEffect::SetPosition(int x, int y)
{
    transform_.position_.x = x;
    transform_.position_.y = y + 32; // プレイヤーの下に配置するので位置調整
}

void LandingEffect::Activate()
{
    isActive_ = true;
    eraseCounter = 0;
    animeFrame = 0;
    FrameCounter = 0;
    Debug::OutPrint(L"着地は生きてる", true);
}

void LandingEffect::Deactivate()
{
    isActive_ = false;
    Debug::OutPrint(L"着地が死亡", true);
}

bool LandingEffect::IsActive() const 
{
    return isActive_;
}

void LandingEffect::Release()
{
    if (hImage_ > 0) 
    {
        DeleteGraph(hImage_);
        hImage_ = -1;
        Debug::OutPrint(L"着地アニメーションは解放された", true);
    }
}