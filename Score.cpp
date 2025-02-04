#include "Score.h"
#include "Player.h"
#include "Engine/SceneManager.h"
#include"cmath"
#include<array>

namespace {
    const int StarPosPlay = 72;

    //一旦文字で評価文を出す（内容は変更可）
    const char* Message_3Star = "Excellent!!";
    const char* Message_2Star = "Good!";
    const char* Message_1Star = "Nice!";
    std::array<const char*, 3> ResultMassage = { Message_1Star, Message_2Star,Message_3Star };
}

Score::Score(GameObject* parent)
    :StarMoveX(0), MessageMoveX(0.0f),frame_Star(0.0f), frame_Message(0.0f),IsStarMoveEnd(false), isPlaying(true),hStar_(-1)
{
	hStar_ = LoadGraph("Assets/UI/Star.png");
    assert(hStar_ > 0);

}

Score::~Score()
{
    Release();
}

void Score::Initialize()
{
    transform_.scale_ = XMFLOAT3(1.0, 1.0, 1.0);
}

void Score::Update()
{
    StarMoveX = easeOutQuart(frame_Star);
    frame_Star += 1.0f / 60.0f;

    if (IsStarMoveEnd)
    {
        MessageMoveX = easeBackOut(frame_Message) + 500;
        frame_Message += 1.0f / 60.0f;
    }

    if (frame_Star >= 1.0f) {
        IsStarMoveEnd = true;
    }
}

void Score::Draw() 
{
    SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
    int mp = pSceneManager->GetMagicPoint(); // GetMp

    const float Width = 33.0f;  //間隔を調整
    int StarCount = 0;    //個数を指定

    if (mp > 80) 
    {
        StarCount = 3;
    }
    else if (mp > 60)
    {
        StarCount = 2;
    }
    else
    {
        StarCount = 1;
    }

    if (!isPlaying) //プレイシーンじゃない
    {
        for (int i = 0; i < StarCount; i++)
        {
            float x = (i * 2.0) * Width + 530;
            float y = 500;
            DrawExtendGraph(x*StarMoveX, y, x + 64, y + 64, hStar_, TRUE);
        }

        if (IsStarMoveEnd) {
            DrawFormatString( 550,620, GetColor(0, 255, 0), ResultMassage[StarCount - 1]);
        }
    }
    else //プレイシーン用
    {
        for (int i = 0; i < StarCount; i++)
        {
            float x = i * Width + 260;
            DrawExtendGraph(x  , StarPosPlay, x + 32, StarPosPlay + 32, hStar_, TRUE);
        }
    }
 

}


void Score::Release()
{
    if (hStar_ > 0)
    {
        DeleteGraph(hStar_);
    }
}

void Score::SetPosition(int x, int y)
{
    transform_.position_.x = x;
    transform_.position_.y = y;
}

void Score::SetPosition(XMFLOAT3 pos)
{
}


float Score::easeOutQuart(float time)
{
    if (time >= 1.0f)
    {
        return 1.0f;
    }
    return 1 - std::pow(1 - time, 4);
}