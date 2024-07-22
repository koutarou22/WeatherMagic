#include "Weather.h"
#include "Player.h"


void Weather::Initialize()
{
    hImage_Sunny = LoadGraph("Assets/Sky.png");
    assert(hImage_Sunny > 0);
    hImage_Rainy = LoadGraph("Assets/Rain.png");
    assert(hImage_Rainy > 0);
    hImage_Wind = LoadGraph("Assets/Wind.png");
    assert(hImage_Wind > 0);

    //---------------UI--------------------------------------
    hImage_SIcon = LoadGraph("Assets/Sun.png");
    assert(hImage_SIcon > 0);
    hImage_RIcon = LoadGraph("Assets/Rain1.png");
    assert(hImage_RIcon > 0);
    hImage_WIcon = LoadGraph("Assets/Gale.png");
    assert(hImage_WIcon > 0);
    //------------------------------------------------------

    //----------------Mp切れ用------------------------------
   /* hImage_RainyNoMp = LoadGraph("Assets/Sun.png");灰色の画像か×の画像予定
    assert(hImage_RainyNoMp > 0);*/

    //hImage_WindNoMp = LoadGraph("Assets/Sun.png"); //灰色の画像か×の画像予定
    //assert(hImage_WindNoMp > 0);
    //------------------------------------------------------


    //hImage_Book = LoadGraph("Assets/Book.png");
    //assert(hImage_Book > 0);
   
    //bool
    RainOnChecker = false;
}

void Weather::Update()
{
    if (++flameCounter_ >= 24)
    {
        if (animeFrame_ < 3) 
        {
            animeFrame_ = (animeFrame_ + 1) % 4; //if文を使わない最適解
        }
        flameCounter_ = 0;
    }
}

void Weather::Draw()
{
    Player* pPlayer = GetParent()->FindGameObject<Player>();

    if (pPlayer == nullptr)
    {
        // pPlayerがnullptrの場合のエラーハンドリング
        DrawFormatString(0, 0, GetColor(255, 0, 0), "Error: Player not found!");
        return;
    }
    int alpha = 24;
    int SBookW = 128 / 3;
    int SBookH = 175 / 4;
    int AnimeS = animeFrame_ % 4 * SBookH;

    if (pPlayer != nullptr)
    {
        switch (weather_)
        {
        case Sunny:
            DrawFormatString(580, 10, GetColor(255, 255, 0), "天候: 晴れ 『変化なし』消費Mp0");
            DrawGraph(500, 0, hImage_SIcon, TRUE);  // 晴れ
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
            DrawGraph(0, 0, hImage_Sunny, TRUE);  // 晴れ
            break;

        case Rainy:
            DrawFormatString(580, 10, GetColor(100, 149, 237), "天候: 雨　『地面がぬかるむ..』-移動速度DOWN  +スライム巨大化");
            DrawGraph(500, 0, hImage_RIcon, TRUE);  // 雨

            if (pPlayer->GetMp() > 0)
            {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
                DrawGraph(0, 0, hImage_Rainy, TRUE);  // 雨
                RainOnChecker = false;
            }
            else
            {
                RainOnChecker = true;
                DrawFormatString(580, 30, GetColor(255, 0, 0), "Mpが足りません！");  // 赤文字で表示
            }
            break;

        case Gale:
            DrawFormatString(580, 10, GetColor(0, 250, 154), "事象: 強風　『敵が(自分も)吹っ飛ぶ！』 消費Mp 4");
            DrawGraph(500, 0, hImage_WIcon, TRUE);

            if (pPlayer->GetMp() > 4)
            {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
                DrawGraph(0, 0, hImage_Wind, TRUE);  // 強風
                WindOnChecker = false;
            }
            else
            {
                WindOnChecker = true;
                DrawFormatString(580, 30, GetColor(255, 0, 0), "Mpが足りません！");  // 赤文字で表示
            }
            break;
        }
    }
   

    // 描画モードを元に戻す
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    DrawFormatString(0, 80, GetColor(0, 0, 255), "今どの天候呼んでる？: %d", weather_);
}


void Weather::SetPosition(int x, int y)
{
    transform_.position_.x = x;
    transform_.position_.y = y;
}

float Weather::GetWeatherChange()
{
    switch (weather_)
    {
    case Sunny:
        return 1.0f; // 晴れの日は通常の速度
    case Rainy:
        return 0.8f; // 雨の日は速度を20%減少
    case Gale: 
        return 1.2f; //強風
    default:
        return 1.0f;
    }
}

