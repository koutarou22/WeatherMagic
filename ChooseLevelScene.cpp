#include "ChooseLevelScene.h"
#include"Engine/SceneManager.h"

namespace
{
    const int TIMER = 100;
}
ChooseLevelScene::ChooseLevelScene(GameObject* parent)
	: GameObject(parent, "ChooseLevelScene"),hImage_(-1),Level_(0)
{
}

void ChooseLevelScene::Initialize()
{
	hImage_ = LoadGraph("Assets/Scene/Title.jpg");//�^�C�g���̔w�i
	//assert(hImage_ >= 0);
}

void ChooseLevelScene::Update()
{
	padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);

	/*SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_PLAY);*/

    if (CheckHitKey(KEY_INPUT_A) /*|| input.Buttons[4]*/)
    {
        Level_ = 0;
    }
    if (CheckHitKey(KEY_INPUT_S) /*|| input.Buttons[4]*/)
    {
        Level_ = 100;
    }
    if (CheckHitKey(KEY_INPUT_D) /*|| input.Buttons[4]*/)
    {
        Level_ = 200;
    }


    // SPACE�L�[�������ꂽ��X�^�[�g�{�^����PlayScene�ɑJ��
    if (CheckHitKey(KEY_INPUT_SPACE) || input.Buttons[4])
    {
        keyPushed_ = true;
    }

    if (keyPushed_)
    {
        keyTimer_--;
    }


    //�^�C�}�[���I�������(�Ó]���I�������)
    if (keyTimer_ < 0)
    {
        SetFontSize(32); //���Ƃɂ��ǂ�
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_PLAY);
    }

}

void ChooseLevelScene::Draw()
{
    int screenWidth, screenHeight, colorBitDepth;
    GetScreenState(&screenWidth, &screenHeight, &colorBitDepth);

    if (keyPushed_)
    {
        static int al = TIMER;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, al);
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_, FALSE);
        al = keyTimer_;
    }
    else
        // ��ʑS�̂ɔw�i�摜��`��
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_, FALSE);

    DrawFormatString(0, 0, GetColor(0, 0, 0), "��Փx: %d", Level_);
}

void ChooseLevelScene::Release()
{
}
