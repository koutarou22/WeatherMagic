#include "LandingEffect.h"
#include "Camera.h"
#include "Debug.h"

namespace
{
    const XMFLOAT2 FRAME_SIZE = { 64,32 };
    const int MIN_FRAME_NUM = 4;
    const int MAX_FRAME_NUM = 7;
}


LandingEffect::LandingEffect(GameObject* parent) : GameObject(parent, "LandingEffect")
{
    dustImage_ = -1;
    frameCounter_ = 0;
    eraseCounter_ = 0;
    animeFrame_ = 0;
    isDraw_ = false;
}

LandingEffect::~LandingEffect()
{
    Release();
}

void LandingEffect::Initialize()
{
    dustImage_ = LoadGraph("Assets/Effect/landing1.png");
    assert(dustImage_ > 0);

}

void LandingEffect::Update()
{
    if (isDraw_)
    {
        //描画(時間は フレーム数で管理)
        if (++frameCounter_ >= MIN_FRAME_NUM)
        {
            animeFrame_ = (animeFrame_ + 1) % MAX_FRAME_NUM;
            frameCounter_ = 0;
            eraseCounter_++;
        }

        //描画終了判定・初期化
        if (eraseCounter_ >= MAX_FRAME_NUM)
        {
            eraseCounter_ = 0;
            animeFrame_ = 0;
            isDraw_ = false;
        }
    }
}

void LandingEffect::Draw()
{
    //カメラ座標をとってきて描画
    int x = (int)transform_.position_.x;
    int y = (int)transform_.position_.y;
    Camera* cam = GetParent()->FindGameObject<Camera>();
    if (cam != nullptr) {
        x -= cam->GetValue();
    }

    if (isDraw_)
    {
        DrawRectGraph(x, y, animeFrame_ * FRAME_SIZE.x, 0, FRAME_SIZE.x, FRAME_SIZE.y, dustImage_, TRUE);
    }
  
}

void LandingEffect::SetPosition(int x, int y)
{
    transform_.position_.x = x;
    transform_.position_.y = y + FRAME_SIZE.y; // プレイヤーの下に配置するので位置調整
}

void LandingEffect::Release()
{
    if (dustImage_ > 0) 
    {
        DeleteGraph(dustImage_);
        dustImage_ = -1;
    }
}