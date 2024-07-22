#include "WeatherIcon.h"

WeatherIcon::WeatherIcon(Weather* parent) :Weather(parent)
{
    hImage_S = LoadGraph("Assets/Sun.png");
    assert(hImage_S > 0);
    hImage_R = LoadGraph("Assets/Rain1.png");
    assert(hImage_R > 0);
    hImage_G = LoadGraph("Assets/Wind.png");
    assert(hImage_G > 0);
}

void WeatherIcon::Update()
{
}


void WeatherIcon::Draw()
{
    switch (weather_)
    {
    case Sunny:
        DrawFormatString(500, 10, GetColor(255, 255, 0), "�V��: ���� �w�ω��Ȃ��x����Mp0");
        DrawGraph(450, 10, hImage_S, TRUE);  // ����

        break;
    case Rainy:
        DrawFormatString(500, 10, GetColor(100, 149, 237), "�V��: �J�@�w�n�ʂ��ʂ����..�x-�ړ����xDOWN  +�X���C�����剻");
        DrawGraph(450, 10, hImage_R, TRUE);  // �J
        break;
    case Gale:
        DrawFormatString(500, 10, GetColor(0, 250, 154), "����: �����@�w�G��(������)������ԁI�x ����Mp 4");
        //DrawGraph(0, 0, hImage_Wind, TRUE);  // �����̉摜�Ƃ�����񂩁H
        break;
    }
}
