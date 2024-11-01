#include "Score.h"
#include "Player.h"
#include "Engine/SceneManager.h"

Score::Score(GameObject* parent)
{
	hImage_ = LoadGraph("Assets/UI/Star.png");
    assert(hImage_ > 0);

}

Score::~Score()
{
}

void Score::Initialize()
{
    transform_.scale_ = XMFLOAT3(1.0, 1.0, 1.0);
}

void Score::Update()
{
}

void Score::Draw() 
{
    SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
    int mp = pSceneManager->GetMagicPoint(); // GetMp

    float Width = 66.0f;  //間隔を調整
    int StarCount = 0;    //個数を指定

    if (mp > 80) 
    {
        StarCount = 3;
        DrawFormatString(0, 70, GetColor(0, 255, 0), "評価☆3");
    }
    else if (mp > 60)
    {
        StarCount = 2;
        DrawFormatString(0, 70, GetColor(0, 255, 0), "評価☆2");
    }
    else
    {
        StarCount = 1;
        DrawFormatString(0, 70, GetColor(0, 255, 0), "評価☆1");
    }

    for (int i = 0; i < StarCount; i++) 
    {
        float x = i * Width;
        float y = transform_.position_.y;//見ずらいから格納しただけ
        DrawExtendGraph(x, y, x + 64, y + 64 , hImage_, TRUE);
    }
}


void Score::Release()
{
}

void Score::SetPosition(int x, int y)
{
    transform_.position_.x = x;
    transform_.position_.y = y;
}

void Score::SetPosition(XMFLOAT3 pos)
{
}
