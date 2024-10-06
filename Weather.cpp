#include "Weather.h"
#include "Player.h"


void Weather::Initialize()
{
    //----------------背景------------------------------------
    hImage_Sun = LoadGraph("Assets/BackImage/Sky.png");
    assert(hImage_Sun > 0);
    hImage_Rain = LoadGraph("Assets/BackImage/Rain.png");
    assert(hImage_Rain > 0);
    hImage_Wind = LoadGraph("Assets/BackImage/Wind.png");
    assert(hImage_Wind > 0);
    hImage_Snow = LoadGraph("Assets/BackImage/Snow.png");
    assert(hImage_Snow > 0);

    //---------------UI--------------------------------------
    Sun_Icon = LoadGraph("Assets/UI/Sun.png");//晴れのアイコン
    assert(Sun_Icon > 0);
    Rain_Icon = LoadGraph("Assets/UI/Rain1.png");//雨のアイコン
    assert(Rain_Icon > 0);
    Gale_Icon = LoadGraph("Assets/UI/Gale.png");//風のアイコン
    assert(Gale_Icon > 0);
    Snow_Icon = LoadGraph("Assets/UI/Snow.png");//風のアイコン
    assert(Snow_Icon > 0);


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
    hImage_RainNoMp = LoadGraph("Assets/UI/Rain4.png");//灰色でバツがついた雨のアイコン
    assert(hImage_RainNoMp > 0);

    hImage_WindNoMp = LoadGraph("Assets/UI/Gale3.png"); //灰色でバツがついた風のアイコン
    assert(hImage_WindNoMp > 0);
  
    RainOnChecker = false;
    DebugLog_ = false;
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

    if (CheckHitKey(KEY_INPUT_Q))
    {
        DebugLog_ = true;
    }
    else
    {
        DebugLog_ = false;
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
    int alpha40 = 40;
    int SBookW = 128 / 3;
    int SBookH = 175 / 4;
    int AnimeS = animeFrame_ % 4 * SBookH;


    if (pPlayer != nullptr)
    {
        switch (weather_)
        {
        case Sun:
     
            DrawGraph(0, 110, hImage_StateSun, TRUE);
            DrawGraph(600, 0, Sun_Icon, TRUE);  // 晴れ
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
            DrawGraph(0, 0, hImage_Sun, TRUE);  // 晴れ
            break;

        case Rain:

            DrawGraph(0, 110, hImage_StateRain, TRUE);
            if (pPlayer->GetMp() > 0)
            {
                DrawGraph(600, 0, Rain_Icon, TRUE);  // 雨
              //  DrawFormatString(580, 38, GetColor(100, 149, 237), "常時消費Mp1");
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
                DrawGraph(0, 0, hImage_Rain, TRUE);  // 雨
                RainOnChecker = false;
            }
            else
            {
                RainOnChecker = true;
                DrawGraph(600, 0, hImage_RainNoMp, TRUE);  // 雨
                DrawFormatString(580, 48, GetColor(255, 0, 0), "Mpが足りません！");  // 赤文字で表示
            }
            break;

        case Gale:

            DrawGraph(0, 110, hImage_StateWind, TRUE);
            if (pPlayer->GetMp() > 3)
            {
                DrawGraph(600, 0, Gale_Icon, TRUE);
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

        case Snow:
            DrawGraph(600, 0, Snow_Icon, TRUE);
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha40);
            DrawGraph(0, 0, hImage_Snow, TRUE);  // 雪
            break;
        }
    }

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//透明度を元に戻す

    //天候関連のログの表示(Qキーで表示できる)
    //消しても動作には問題ない
    if (DebugLog_ == true)
    {
        DrawFormatString(990, 230, GetColor(255, 255, 255), "現在の天候は % d", weather_,"です");
        switch (weather_)
        {
        case Sun:

            DrawFormatString(990, 120, GetColor(220, 20, 60), "天候:快晴 ");
            DrawFormatString(990, 145, GetColor(220, 20, 60), "効果:『なし』");
            break;

        case Rain:

            DrawFormatString(990, 120, GetColor(65, 105, 225), "天候: 雨");
            DrawFormatString(990, 145, GetColor(65, 105, 225), "効果1:『一部の敵に変化』");
            DrawFormatString(990, 169, GetColor(255, 0, 0),  "効果2:『毎秒Mp１減少』");
            break;

        case Gale:

            DrawFormatString(990, 120, GetColor(0, 255, 127), "天候: 風");
            DrawFormatString(990, 145, GetColor(0, 187, 133), "効果1:『移動速度上昇』");
            DrawFormatString(990, 169, GetColor(0, 187, 133), "効果2:『強風を発生』");
            DrawFormatString(990, 192, GetColor(255, 0, 0), "↑消費Mp 4");
            break;

        case Snow:
            DrawFormatString(990, 120, GetColor(0, 255, 127), "天候: 雪");
            DrawFormatString(990, 145, GetColor(0, 187, 133), "効果:『未定』");
            break;

        }
    }   
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
    case Sun:
        return 1.0f; // 晴れの日は通常の速度
    case Rain:
        return 1.0f; // 前回:雨の日は速度を20%減少
    case Gale: 
        return 1.2f; //強風　1.2倍の速度
    case Snow:
        return 0.8;
    default:
        return 1.0f;
    }
}

