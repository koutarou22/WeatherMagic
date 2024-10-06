#include "Weather.h"
#include "Player.h"


void Weather::Initialize()
{
    //----------------�w�i------------------------------------
    hImage_Sun = LoadGraph("Assets/BackImage/Sky.png");
    assert(hImage_Sun > 0);
    hImage_Rain = LoadGraph("Assets/BackImage/Rain.png");
    assert(hImage_Rain > 0);
    hImage_Wind = LoadGraph("Assets/BackImage/Wind.png");
    assert(hImage_Wind > 0);
    hImage_Snow = LoadGraph("Assets/BackImage/Snow.png");
    assert(hImage_Snow > 0);

    //---------------UI--------------------------------------
    Sun_Icon = LoadGraph("Assets/UI/Sun.png");//����̃A�C�R��
    assert(Sun_Icon > 0);
    Rain_Icon = LoadGraph("Assets/UI/Rain1.png");//�J�̃A�C�R��
    assert(Rain_Icon > 0);
    Gale_Icon = LoadGraph("Assets/UI/Gale.png");//���̃A�C�R��
    assert(Gale_Icon > 0);
    Snow_Icon = LoadGraph("Assets/UI/Snow.png");//���̃A�C�R��
    assert(Snow_Icon > 0);


    //--------------����������Ă���UI-------------------------

    hImage_StateSun = LoadGraph("Assets/UI/SState.png");//����̉��UI
    assert(hImage_StateSun > 0);
    hImage_StateRain = LoadGraph("Assets/UI/RState.png");//�J�̉��UI
    assert(hImage_StateRain > 0);
    hImage_StateWind = LoadGraph("Assets/UI/WState.png");//���̉��UI
    assert(hImage_StateWind > 0);
    //hImage_Book = LoadGraph("Assets/Book.png");
    //assert(hImage_Book > 0);


    //----------------Mp���؂ꂽ�Ƃ�------------------------------
    hImage_RainNoMp = LoadGraph("Assets/UI/Rain4.png");//�D�F�Ńo�c�������J�̃A�C�R��
    assert(hImage_RainNoMp > 0);

    hImage_WindNoMp = LoadGraph("Assets/UI/Gale3.png"); //�D�F�Ńo�c���������̃A�C�R��
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
            animeFrame_ = (animeFrame_ + 1) % 4; //if�����g��Ȃ��œK��
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
            DrawGraph(600, 0, Sun_Icon, TRUE);  // ����
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
            DrawGraph(0, 0, hImage_Sun, TRUE);  // ����
            break;

        case Rain:

            DrawGraph(0, 110, hImage_StateRain, TRUE);
            if (pPlayer->GetMp() > 0)
            {
                DrawGraph(600, 0, Rain_Icon, TRUE);  // �J
              //  DrawFormatString(580, 38, GetColor(100, 149, 237), "�펞����Mp1");
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
                DrawGraph(0, 0, hImage_Rain, TRUE);  // �J
                RainOnChecker = false;
            }
            else
            {
                RainOnChecker = true;
                DrawGraph(600, 0, hImage_RainNoMp, TRUE);  // �J
                DrawFormatString(580, 48, GetColor(255, 0, 0), "Mp������܂���I");  // �ԕ����ŕ\��
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
                DrawFormatString(580, 48, GetColor(255, 0, 0), "Mp������܂���I");  // �ԕ����ŕ\��
            }
            break;

        case Snow:
            DrawGraph(600, 0, Snow_Icon, TRUE);
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha40);
            DrawGraph(0, 0, hImage_Snow, TRUE);  // ��
            break;
        }
    }

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//�����x�����ɖ߂�

    //�V��֘A�̃��O�̕\��(Q�L�[�ŕ\���ł���)
    //�����Ă�����ɂ͖��Ȃ�
    if (DebugLog_ == true)
    {
        DrawFormatString(990, 230, GetColor(255, 255, 255), "���݂̓V��� % d", weather_,"�ł�");
        switch (weather_)
        {
        case Sun:

            DrawFormatString(990, 120, GetColor(220, 20, 60), "�V��:���� ");
            DrawFormatString(990, 145, GetColor(220, 20, 60), "����:�w�Ȃ��x");
            break;

        case Rain:

            DrawFormatString(990, 120, GetColor(65, 105, 225), "�V��: �J");
            DrawFormatString(990, 145, GetColor(65, 105, 225), "����1:�w�ꕔ�̓G�ɕω��x");
            DrawFormatString(990, 169, GetColor(255, 0, 0),  "����2:�w���bMp�P�����x");
            break;

        case Gale:

            DrawFormatString(990, 120, GetColor(0, 255, 127), "�V��: ��");
            DrawFormatString(990, 145, GetColor(0, 187, 133), "����1:�w�ړ����x�㏸�x");
            DrawFormatString(990, 169, GetColor(0, 187, 133), "����2:�w�����𔭐��x");
            DrawFormatString(990, 192, GetColor(255, 0, 0), "������Mp 4");
            break;

        case Snow:
            DrawFormatString(990, 120, GetColor(0, 255, 127), "�V��: ��");
            DrawFormatString(990, 145, GetColor(0, 187, 133), "����:�w����x");
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
        return 1.0f; // ����̓��͒ʏ�̑��x
    case Rain:
        return 1.0f; // �O��:�J�̓��͑��x��20%����
    case Gale: 
        return 1.2f; //�����@1.2�{�̑��x
    case Snow:
        return 0.8;
    default:
        return 1.0f;
    }
}

