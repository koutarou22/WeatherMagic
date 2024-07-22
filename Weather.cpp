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

    //----------------Mp�؂�p------------------------------
   /* hImage_RainyNoMp = LoadGraph("Assets/Sun.png");�D�F�̉摜���~�̉摜�\��
    assert(hImage_RainyNoMp > 0);*/

    //hImage_WindNoMp = LoadGraph("Assets/Sun.png"); //�D�F�̉摜���~�̉摜�\��
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
        // pPlayer��nullptr�̏ꍇ�̃G���[�n���h�����O
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
            DrawFormatString(580, 10, GetColor(255, 255, 0), "�V��: ���� �w�ω��Ȃ��x����Mp0");
            DrawGraph(500, 0, hImage_SIcon, TRUE);  // ����
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
            DrawGraph(0, 0, hImage_Sunny, TRUE);  // ����
            break;

        case Rainy:
            DrawFormatString(580, 10, GetColor(100, 149, 237), "�V��: �J�@�w�n�ʂ��ʂ����..�x-�ړ����xDOWN  +�X���C�����剻");
            DrawGraph(500, 0, hImage_RIcon, TRUE);  // �J

            if (pPlayer->GetMp() > 0)
            {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
                DrawGraph(0, 0, hImage_Rainy, TRUE);  // �J
                RainOnChecker = false;
            }
            else
            {
                RainOnChecker = true;
                DrawFormatString(580, 30, GetColor(255, 0, 0), "Mp������܂���I");  // �ԕ����ŕ\��
            }
            break;

        case Gale:
            DrawFormatString(580, 10, GetColor(0, 250, 154), "����: �����@�w�G��(������)������ԁI�x ����Mp 4");
            DrawGraph(500, 0, hImage_WIcon, TRUE);

            if (pPlayer->GetMp() > 4)
            {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
                DrawGraph(0, 0, hImage_Wind, TRUE);  // ����
                WindOnChecker = false;
            }
            else
            {
                WindOnChecker = true;
                DrawFormatString(580, 30, GetColor(255, 0, 0), "Mp������܂���I");  // �ԕ����ŕ\��
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

