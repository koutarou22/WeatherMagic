#include "Weather.h"
#include "Player.h"


void Weather::Initialize()
{
    //----------------背景------------------------------------
    hImage_Sunny = LoadGraph("Assets/BackImage/Sky.png");
    assert(hImage_Sunny > 0);
    hImage_Rainy = LoadGraph("Assets/BackImage/Rain.png");
    assert(hImage_Rainy > 0);
    hImage_Wind = LoadGraph("Assets/BackImage/Wind.png");
    assert(hImage_Wind > 0);

    //---------------UI--------------------------------------
    hImage_SIcon = LoadGraph("Assets/UI/Sun.png");//晴れのアイコン
    assert(hImage_SIcon > 0);
    hImage_RIcon = LoadGraph("Assets/UI/Rain1.png");//雨のアイコン
    assert(hImage_RIcon > 0);
    hImage_WIcon = LoadGraph("Assets/UI/Gale.png");//風のアイコン
    assert(hImage_WIcon > 0);

    //BgImage_ = LoadGraph("Assets/BgWeather.png");//縦長の黒い枠
    //assert(BgImage_ > 0);

    //--------------解説が書いてあるUI-------------------------

    hImage_StateSun = LoadGraph("Assets/UI/SState.png");//晴れの解説UI
    assert(hImage_StateSun > 0);
    hImage_StateRain = LoadGraph("Assets/UI/RState.png");//雨の解説UI
    assert(hImage_StateRain > 0);
    hImage_StateWind = LoadGraph("Assets/UI/WState.png");//風の解説UI
    assert(hImage_StateWind > 0);
    //hImage_Book = LoadGraph("Assets/Book.png");
    //assert(hImage_Book > 0);


    //----------------Mpが切れたとき------------------------------
    hImage_RainyNoMp = LoadGraph("Assets/UI/Rain4.png");//灰色でバツがついた雨のアイコン
    assert(hImage_RainyNoMp > 0);

    hImage_WindNoMp = LoadGraph("Assets/UI/Gale3.png"); //灰色でバツがついた風のアイコン
    assert(hImage_WindNoMp > 0);
  
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
        DrawFormatString(0, 0, GetColor(255, 0, 0), "Error: Player not found!");
        return;
    }
    int alpha = 24;
    int SBookW = 128 / 3;
    int SBookH = 175 / 4;
    int AnimeS = animeFrame_ % 4 * SBookH;

   // DrawGraph(0, 110, BgImage_, TRUE);

    if (pPlayer != nullptr)
    {
        switch (weather_)
        {
        case Sunny:
           
            DrawGraph(0, 110, hImage_StateSun, TRUE);
            DrawGraph(600, 0, hImage_SIcon, TRUE);  // 晴れ
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
            DrawGraph(0, 0, hImage_Sunny, TRUE);  // 晴れ
            break;

        case Rainy:
           /* DrawFormatString(580, 0, GetColor(100, 149, 237), "天候: 雨");
            DrawFormatString(580, 18, GetColor(100, 149, 237), "効果:『移動速度低下 +一部の敵に変化』");*/

            DrawGraph(0, 110, hImage_StateRain, TRUE);
            if (pPlayer->GetMp() > 0)
            {
                DrawGraph(600, 0, hImage_RIcon, TRUE);  // 雨
              //  DrawFormatString(580, 38, GetColor(100, 149, 237), "常時消費Mp1");
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
                DrawGraph(0, 0, hImage_Rainy, TRUE);  // 雨
                RainOnChecker = false;
            }
            else
            {
                RainOnChecker = true;
                DrawGraph(600, 0, hImage_RainyNoMp, TRUE);  // 雨
                DrawFormatString(580, 48, GetColor(255, 0, 0), "Mpが足りません！");  // 赤文字で表示
            }
            break;

        case Gale:
            /*DrawFormatString(580, 3, GetColor(0, 250, 154), "事象: 強風");
            DrawFormatString(580, 24, GetColor(0, 250, 154), "効果:『一部の敵を強制的に動かす』");
            DrawFormatString(580, 34, GetColor(0, 250, 154), "能力:『右キーか左キーを押すことで５秒間強風を発生させる』");*/

            DrawGraph(0, 110, hImage_StateWind, TRUE);
            if (pPlayer->GetMp() > 3)
            {
                DrawGraph(600, 0, hImage_WIcon, TRUE);
               // DrawFormatString(575, 41, GetColor(0, 250, 154), "消費Mp 4");
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
                DrawGraph(0, 0, hImage_Wind, TRUE);
                WindOnChecker = false;
            }
            else
            {
                WindOnChecker = true;
                DrawGraph(600, 0, hImage_WindNoMp, TRUE);
                DrawFormatString(580, 48, GetColor(255, 0, 0), "Mpが足りません！");  // 赤文字で表示
            }
            break;
        }
    }
   
    
    // 描画モードを元に戻す
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

  //  DrawFormatString(0, 80, GetColor(0, 0, 255), "今どの天候呼んでる？: %d", weather_);
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

