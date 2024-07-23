#include "DxLib.h"
#include "RoadScene.h"
#include "TestScene.h"
#include "Engine/SceneManager.h"
#include "Field.h"

const char* Load_TEXT = "Load Now";

RoadScene::RoadScene(GameObject* parent)
    : GameObject(parent, "RoadScene")
{
}

void RoadScene::Initialize()
{
   /* hImage_ = LoadGraph("Assets/OIG3.jpg");
    assert(hImage_ >= 0);*/
}

void RoadScene::Update()
{
    if (CheckHitKey(KEY_INPUT_Q))
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        if (pSceneManager != nullptr)
        {
            Field* pField = FindGameObject<Field>();
            if (pField != nullptr)
            {
                pField->NextLoadStage(); // ���̃X�e�[�W�����[�h
            }
            pSceneManager->ChangeScene(SCENE_ID_TEST); // TestScene�ɖ߂�
        }
    }
   
}


void RoadScene::Draw()
{
    //int x = (int)transform_.position_.x;
    //int y = (int)transform_.position_.y;

    //int screenWidth, screenHeight, colorBitDepth;
    //GetScreenState(&screenWidth, &screenHeight, &colorBitDepth);

    //// ��ʑS�̂ɔw�i�摜��`��
    //DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_, FALSE);
    //// �^�C�g����ʂ̃e�L�X�g��`��
    //DrawString(0, 0, TITLE_TEXT, GetColor(255, 255, 255));

}

void RoadScene::Release()
{
}
