#include "Weather.h"


void Weather::Initialize()
{
    hImage_Sunny = LoadGraph("Assets/Sky.png");
    assert(hImage_Sunny > 0);
    hImage_Rainy = LoadGraph("Assets/Rain.png");
    assert(hImage_Rainy > 0);
    hImage_Wind = LoadGraph("Assets/Wind.png");
    assert(hImage_Wind > 0);
}

void Weather::Update()
{
   
}

void Weather::Draw() 
{
    int alpha = 24;  // �����x�𔼕��ɐݒ�

    switch (weather_)
    {
    case Sunny:
        DrawFormatString(500, 10, GetColor(255, 255, 0), "�V��: ���� �w�ω��Ȃ��x");
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawGraph(0, 0, hImage_Sunny, TRUE);  // ����
        break;
    case Rainy:
        DrawFormatString(500, 10, GetColor(0, 0, 0), "�V��: �J�@�w�n�ʂ��ʂ����..�x-�ړ����xDOWN  +�X���C�����剻");
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawGraph(0, 0, hImage_Rainy, TRUE);  // �J
        break;
    case Gale:
        DrawFormatString(500, 10, GetColor(255, 255, 255), "����: �����@�w�G��(������)������ԁI�x");
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawGraph(0, 0, hImage_Wind, TRUE);  // �����̉摜�Ƃ�����񂩁H
        break;
    }

    // �`�惂�[�h�����ɖ߂�
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    DrawFormatString(0, 80, GetColor(0, 0, 255), "���ǂ̓V��Ă�ł�H: %d", weather_);
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
