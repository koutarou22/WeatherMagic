#include "Weather.h"

void Weather::Initialize()
{
    hImage_Sunny = LoadGraph("Assets/Sky.png");
    assert(hImage_Sunny > 0);
    hImage_Rainy = LoadGraph("Assets/Rain.png");
    assert(hImage_Rainy > 0);
}

void Weather::Update()
{

}

void Weather::Draw() 
{
    int alpha = 24;  // �����x�𔼕��ɐݒ�

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

    // �V��ɉ������`�揈��
    switch (weather_) 
    {
    case Sunny:
        DrawFormatString(500, 10, GetColor(255, 255, 0), "�V��: ���� �w���C�I�x");
        DrawGraph(0, 0, hImage_Sunny, TRUE);  // ����
        break;
    case Rainy:
        DrawFormatString(500, 10, GetColor(255, 255, 0), "�V��: �J�@�w�n�ʂ��ʂ����..�x");
        DrawGraph(0, 0, hImage_Rainy, TRUE);  // �J
        break;
    }

    // �`�惂�[�h�����ɖ߂�
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

float Weather::GetWeatherChange()
{
    switch (weather_)
    {
    case Sunny:
        return 1.0f; // ����̓��͒ʏ�̑��x
    case Rainy:
        return 0.8f; // �J�̓��͑��x��20%����
    default:
        return 1.0f;
    }
}

