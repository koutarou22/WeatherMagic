#include "DxLib.h"
#include "Hp.h"
#include "Player.h"

Hp::Hp(GameObject* parent):GameObject(parent, "Hp"), hImage_(-1),BgImage_(-1), Wide_(3) /*bagImage_(-1)*/
{

}

void Hp::Initialize()
{
    Wide_ = 3;
    hImage_ = LoadGraph("Assets/HP.png");
    assert(hImage_ >= 0);

    BgImage_ = LoadGraph("Assets/HpFrame.png");
    assert(BgImage_ >= 0);
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

    DrawGraph(0,-15, BgImage_, TRUE);

    if (player != nullptr && player->GetHp() > 0)
    {

        for (int i = 0; i < player->GetHp(); i++)
        {
            transform_.position_.x = -0.9 + i * heartWidth;
            DrawExtendGraph(transform_.position_.x, transform_.position_.y, transform_.position_.x + 64 * transform_.scale_.x, transform_.position_.y + 64 * transform_.scale_.y, hImage_, TRUE);
        }

    }
  
}

void Hp::Release()
{
    DeleteGraph(hImage_);
    //DeleteGraph(bagImage_);
}
