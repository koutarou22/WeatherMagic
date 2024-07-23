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

    BgImage_ = LoadGraph("Assets/BgWeather.png");
    assert(BgImage_ > 0);
    //------------------------------------------------------

    //----------------Mp�؂�p------------------------------
    hImage_RainyNoMp = LoadGraph("Assets/Rain4.png");//�D�F�̉摜���~�̉摜�\��
    assert(hImage_RainyNoMp > 0);

    hImage_WindNoMp = LoadGraph("Assets/Gale3.png"); //�D�F�̉摜���~�̉摜�\��
    assert(hImage_WindNoMp > 0);
    //------------------------------------------------------

    hImage_StateSun = LoadGraph("Assets/SState.png");
    assert(hImage_StateSun > 0);
    hImage_StateRain = LoadGraph("Assets/RState.png");
    assert(hImage_StateRain > 0);
    hImage_StateWind = LoadGraph("Assets/WState.png");
    assert(hImage_StateWind > 0);
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
            animeFrame_ = (animeFrame_ + 1) % 4; //if�����g��Ȃ��œK��
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
            /*DrawFormatString(580, 0, GetColor(255, 255, 0), "�V��: ����");
            DrawFormatString(580, 18,GetColor(255, 255, 0), "����:�w�ω��Ȃ��x");
            DrawFormatString(580, 38, GetColor(255, 255, 0), "����Mp0");*/
           /* DrawFormatString(0, 120, GetColor(255, 255, 0), "�V��: ����");
            DrawFormatString(0, 130, GetColor(255, 255, 0), "����:�w�ω��Ȃ��x");
            DrawFormatString(0, 140, GetColor(255, 255, 0), "����Mp0");*/
            DrawGraph(0, 110, hImage_StateSun, TRUE);
            DrawGraph(500, 0, hImage_SIcon, TRUE);  // ����
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
            DrawGraph(0, 0, hImage_Sunny, TRUE);  // ����
            break;

        case Rainy:
           /* DrawFormatString(580, 0, GetColor(100, 149, 237), "�V��: �J");
            DrawFormatString(580, 18, GetColor(100, 149, 237), "����:�w�ړ����x�ቺ +�ꕔ�̓G�ɕω��x");*/

            DrawGraph(0, 110, hImage_StateRain, TRUE);
            if (pPlayer->GetMp() > 0)
            {
                DrawGraph(500, 0, hImage_RIcon, TRUE);  // �J
                DrawFormatString(580, 38, GetColor(100, 149, 237), "�펞����Mp1");
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
                DrawGraph(0, 0, hImage_Rainy, TRUE);  // �J
                RainOnChecker = false;
            }
            else
            {
                RainOnChecker = true;
                DrawGraph(500, 0, hImage_RainyNoMp, TRUE);  // �J
                DrawFormatString(580, 38, GetColor(255, 0, 0), "Mp������܂���I");  // �ԕ����ŕ\��
            }
            break;

        case Gale:
            /*DrawFormatString(580, 3, GetColor(0, 250, 154), "����: ����");
            DrawFormatString(580, 24, GetColor(0, 250, 154), "����:�w�ꕔ�̓G�������I�ɓ������x");
            DrawFormatString(580, 34, GetColor(0, 250, 154), "�\��:�w�E�L�[�����L�[���������ƂłT�b�ԋ����𔭐�������x");*/

            DrawGraph(0, 110, hImage_StateWind, TRUE);
            if (pPlayer->GetMp() > 3)
            {
                DrawGraph(500, 0, hImage_WIcon, TRUE);
                DrawFormatString(575, 41, GetColor(0, 250, 154), "����Mp 4");
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
                DrawGraph(0, 0, hImage_Wind, TRUE);
                WindOnChecker = false;
            }
            else
            {
                WindOnChecker = true;
                DrawGraph(500, 0, hImage_WindNoMp, TRUE);
                DrawFormatString(575, 41, GetColor(255, 0, 0), "Mp������܂���I");  // �ԕ����ŕ\��
            }
            break;
        }
    }
   
    
    // �`�惂�[�h�����ɖ߂�
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    DrawFormatString(0, 80, GetColor(0, 0, 255), "���ǂ̓V��Ă�ł�H: %d", weather_);
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
        return 1.0f; // ����̓��͒ʏ�̑��x
    case Rainy:
        return 0.8f; // �J�̓��͑��x��20%����
    case Gale: 
        return 1.2f; //����
    default:
        return 1.0f;
    }
}

