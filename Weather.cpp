#include "Weather.h"

void Weather::Update() 
{

}

void Weather::Draw() {
    // �V��ɉ������`�揈��
    switch (weather_) {
    case Sunny:
        DrawFormatString(500, 10, GetColor(255, 255, 0), "�V��: ���� �w���C�I�x");
        break;
    case Rainy:
        DrawFormatString(500, 10, GetColor(255, 255, 0), "�V��: �J�@�w�n�ʂ��ʂ����..�x");
        break;
    }
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

