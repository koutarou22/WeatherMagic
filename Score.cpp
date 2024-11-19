#include "Score.h"
#include "Player.h"
#include "Engine/SceneManager.h"
#include"cmath"
#include<array>

namespace {
    const float max = 1.70158f;//easeBackOut‚ÌÅ‘å’l
}

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
    StarMoveX = easeOutQuart(frame_Star);
    frame_Star += 1.0f / 60.0f;

    if (frame_Star >= 1.0f) {
        IsStarMoveEnd = true;
    }

    if (IsStarMoveEnd)
    {
        MessageMoveX = easeBackOut(frame_Message);
        frame_Message += 1.0f / 60.0f;
    }
}

void Score::Draw() 
{
    SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
    int mp = pSceneManager->GetMagicPoint(); // GetMp

    float Width = 66.0f;  //ŠÔŠu‚ğ’²®
    int StarCount = 0;    //ŒÂ”‚ğw’è

    //ˆê’U•¶š‚Å•]‰¿•¶‚ğo‚·i“à—e‚Í•ÏX‰Âj
    const char* Message_3Star = "Excellent!!";
    const char* Message_2Star = "Good!";
    const char* Message_1Star = "Nice!";

    std::array<const char*, 3> ResultMassage = { Message_1Star, Message_2Star,Message_3Star };

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

    for (int i = 0; i < StarCount; i++) 
    {
        float x = i * Width;
        float y = transform_.position_.y;//Œ©‚¸‚ç‚¢‚©‚çŠi”[‚µ‚½‚¾‚¯
        DrawExtendGraph(x * StarMoveX, y, x + 64, y + 64 , hImage_, TRUE);
    }
    
    if (IsStarMoveEnd) {
        DrawFormatString(0 * MessageMoveX, 120, GetColor(0, 255, 0), ResultMassage[StarCount - 1]);
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

float Score::easeOutQuart(float time)
{
    if (time >= 1.0f)
    {
        return 1.0f;
    }
    return 1 - std::pow(1 - time, 4);
}

float Score::easeBackOut(float time)
{
    return 1.0f - std::pow(1.0f - time, 2) * (1.0f + max * (1.0f - time));
}
