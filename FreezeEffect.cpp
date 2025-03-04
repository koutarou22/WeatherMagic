#include "FreezeEffect.h"
#include "Camera.h"
#include "Weather.h"

namespace
{
    const XMFLOAT2 POS_MARGE = { 10,2 }; //座標調整用
    const int FRAME_SIZE = 64; //アニメーションの切り取りサイズ
    const int NORMAL_FRAME_COUNT = 16; //アニメーションの基準フレーム
    const int FREEZE_FRAME = 7; //凍っているときの基準フレーム(フレーム最大値)
    const int MELT_FRAME = 1; //溶けているときの基準フレーム(フレーム最小値)
}

FreezeEffect::FreezeEffect(GameObject* parent) : GameObject(parent, "FreezeEffect")
{
    freezeImage_ = -1;
    frameCounter_ = 0;
    eraseCounter_ = 0;
    animeFrame_ = 0;
    freezeSt_ = S_NONE;
}

FreezeEffect::~FreezeEffect()
{
    Release();
}

void FreezeEffect::Initialize()
{
    freezeImage_ = LoadGraph("Assets/Effect/Ice.png");
    assert(freezeImage_ > 0);

    freezeSt_ = S_Freeze;
}

void FreezeEffect::Update()
{
    switch (freezeSt_)
    {
    case FreezeEffect::S_Freeze:
        UpdateFreeze();
        break;
    case FreezeEffect::S_MELT:
        UpdateMelt();
        break;
    case FreezeEffect::S_NONE:
    default:
        break;
    }
}

void FreezeEffect::UpdateFreeze()
{
    //天候が雪でないときは溶けている状態
    Weather* pWeather = GetParent()->FindGameObject<Weather>();
    if (pWeather->GetWeatherState() != WeatherState::Snow) {
        freezeSt_ = S_MELT;
        frameCounter_ = 0;
    }

    //凍るアニメーション
    if (++frameCounter_ >= NORMAL_FRAME_COUNT)
    {
        animeFrame_++;
        if (animeFrame_ > FREEZE_FRAME)
        {
            animeFrame_ = FREEZE_FRAME; //最後の状態で固定
        }
        frameCounter_ = 0;
    }
}

void FreezeEffect::UpdateMelt()
{
    //溶ける時のアニメーション 凍る時の逆
    if (++frameCounter_ >= NORMAL_FRAME_COUNT)
    {
        animeFrame_--;
        if (animeFrame_ <= MELT_FRAME)
        {
            animeFrame_ = MELT_FRAME; //最後の状態で固定
            frameCounter_ = 0;
            KillMe();
        }
        frameCounter_ = 0;
    }
}

void FreezeEffect::Draw()
{
    //カメラ座標をとってきて描画
    int x = transform_.position_.x;
    int y = transform_.position_.y;
    Camera* cam = GetParent()->FindGameObject<Camera>();
    if (cam != nullptr)
    {
        x -= cam->GetValue();
    }
    int FrameX = 64;
    int FrameY = 64;
    DrawRectGraph(x, y, animeFrame_ * FRAME_SIZE, 0, FRAME_SIZE, FRAME_SIZE, freezeImage_, TRUE);

}

void FreezeEffect::Release()
{
    if (freezeImage_ > 0)
    {
        DeleteGraph(freezeImage_);
        freezeImage_ = -1;
    }
}

void FreezeEffect::SetPosition(int x, int y)
{
    transform_.position_.x = x + POS_MARGE.x;
    transform_.position_.y = y + POS_MARGE.y;
}
