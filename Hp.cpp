#include "DxLib.h"
#include "Hp.h"
#include "Player.h"

Hp::Hp(GameObject* parent)
    :GameObject(parent, "Hp"), hHp_(-1),hHpFrame_(-1), Wide_(3) /*bagImage_(-1)*/
{

}

Hp::~Hp()
{
    Release();
}

void Hp::Initialize()
{
    /*Wide_ = 3;*/
    hHp_ = LoadGraph("Assets/UI/HP.png");
    assert(hHp_ >= 0);

    hHpFrame_ = LoadGraph("Assets/UI/HpFrame.png");
    assert(hHpFrame_ >= 0);
}

void Hp::Update()
{
    //bagImage_ = LoadGraph("Image/BackImage.png");
    //assert(bagImage_ >= 0);

    transform_.scale_ = XMFLOAT3(1.0, 1.0, 1.0);
    transform_.position_ = XMFLOAT3(-0.85, -4, 0);
}

void Hp::DamageHp()
{
    if (Wide_ > 0) 
    {
        Wide_--;
    }
}

void Hp::HeelHp()
{
    if (Wide_ > 0)
    {
        Wide_++;
    }
}

void Hp::Draw()
{
    // 画面のサイズを取得
    int screenWidth, screenHeight, colorBitDepth;
    GetScreenState(&screenWidth, &screenHeight, &colorBitDepth);

    //// 画面全体に背景画像を描画
    //DrawExtendGraph(0, 0, screenWidth, screenHeight, bagImage_, FALSE);

    float heartWidth = 50.0f;  // ハートの画像の幅に合わせて調整
    Player* player = GetParent()->FindGameObject<Player>();  // Playerオブジェクトを取得

    DrawGraph(0,-15, hHpFrame_, TRUE);

    if (player != nullptr && player->GetHp() > 0)
    {

        for (int i = 0; i < player->GetHp(); i++)
        {
            transform_.position_.x = -0.9 + i * heartWidth;
            DrawExtendGraph(transform_.position_.x, transform_.position_.y,transform_.position_.x + 64 * transform_.scale_.x, transform_.position_.y + 64 * transform_.scale_.y, hHp_, TRUE);
        }

    }
  
}

void Hp::Release()
{
    if (hHp_ > 0)
    {
        DeleteGraph(hHp_);
    }
    if (hHpFrame_ > 0)
    {
        DeleteGraph(hHpFrame_);
    }
}
