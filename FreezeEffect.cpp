#include "FreezeEffect.h"
#include "Camera.h"
#include "Weather.h"

namespace
{
    const XMFLOAT2 POS_MARGE = { 10,2 }; //���W�����p
    const int FRAME_SIZE = 64; //�A�j���[�V�����̐؂���T�C�Y
    const int NORMAL_FRAME_COUNT = 16; //�A�j���[�V�����̊�t���[��
    const int FREEZE_FRAME = 7; //�����Ă���Ƃ��̊�t���[��(�t���[���ő�l)
    const int MELT_FRAME = 1; //�n���Ă���Ƃ��̊�t���[��(�t���[���ŏ��l)
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
    //�V�󂪐�łȂ��Ƃ��͗n���Ă�����
    Weather* pWeather = GetParent()->FindGameObject<Weather>();
    if (pWeather->GetWeatherState() != WeatherState::Snow) {
        freezeSt_ = S_MELT;
        frameCounter_ = 0;
    }

    //����A�j���[�V����
    if (++frameCounter_ >= NORMAL_FRAME_COUNT)
    {
        animeFrame_++;
        if (animeFrame_ > FREEZE_FRAME)
        {
            animeFrame_ = FREEZE_FRAME; //�Ō�̏�ԂŌŒ�
        }
        frameCounter_ = 0;
    }
}

void FreezeEffect::UpdateMelt()
{
    //�n���鎞�̃A�j���[�V���� ���鎞�̋t
    if (++frameCounter_ >= NORMAL_FRAME_COUNT)
    {
        animeFrame_--;
        if (animeFrame_ <= MELT_FRAME)
        {
            animeFrame_ = MELT_FRAME; //�Ō�̏�ԂŌŒ�
            frameCounter_ = 0;
            KillMe();
        }
        frameCounter_ = 0;
    }
}

void FreezeEffect::Draw()
{
    //�J�������W���Ƃ��Ă��ĕ`��
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
