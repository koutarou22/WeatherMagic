#include "LandingEffect.h"
#include "Camera.h"

LandingEffect::LandingEffect(GameObject* parent) : GameObject(parent, "LandingEffect"), hImage_(-1), animeFrame(0), FrameCounter(0), eraseCounter(0)
{
    hImage_ = LoadGraph("Assets/Effect/landing1.png");
    assert(hImage_ > 0);
}

LandingEffect::~LandingEffect()
{
    Release();
}

void LandingEffect::Update()
{
    if (++FrameCounter >= 4) // アニメーション速度を調整
    {
        animeFrame = (animeFrame + 1) % 7; // 7フレームに調整
        FrameCounter = 0;
        eraseCounter++;
    }

    if (eraseCounter >= 7) // アニメーションを完了させるフレーム数に合わせる
    {
        KillMe();
    }
}

void LandingEffect::Draw()
{
    int x = (int)transform_.position_.x;
    int y = (int)transform_.position_.y;

    Camera* cam = GetParent()->FindGameObject<Camera>();
    if (cam != nullptr) {
        x -= cam->GetValue();
    }

    //↓32の場合
    int FrameX = 64;
    int FrameY = 32;
    //↓64の場合
    //int FrameX = 128;
    //int FrameY = 64; 

    // フレームごとの画像の一部を描画
    DrawRectGraph(x, y, animeFrame * FrameX, 0, FrameX, FrameY, hImage_, TRUE);
}

void LandingEffect::Release()
{
    if (hImage_ > 0)
    {
        DeleteGraph(hImage_);
    }
}

void LandingEffect::SetPosition(int x, int y)
{
    transform_.position_.x = x;
    transform_.position_.y = y + 32;//プレイヤーの下に配置するので位置調整
}
