#include "ChooseLevelScene.h"
#include"Engine/SceneManager.h"

namespace
{
    const int TIMER = 100;
    const int SCREENSIZE_HALF = 610;
    const int CURSOR_POINT = 580;
}
int ChooseLevelScene::Previous(int level)
{
	if(level_arr.empty()) 
        return -1;  // �z�񂪋�̏ꍇ

	// �C���f�b�N�X��0�Ȃ�A�O�̗v�f�͔z��̍Ō�̗v�f�i2�̏ꍇ��0�j
	return level_arr[(currentlevel - 1 + level_arr.size()) % level_arr.size()];
}

int ChooseLevelScene::Next(int currentIndex)
{
	if (level_arr.empty())
        return -1;  // �z�񂪋�̏ꍇ

	// �C���f�b�N�X���Ō�Ȃ�A���͍ŏ��̗v�f�i2�̏ꍇ��0�j
	return level_arr[(currentIndex + 1) % level_arr.size()];
}
ChooseLevelScene::ChooseLevelScene(GameObject* parent)
    : GameObject(parent, "ChooseLevelScene"), hImage_back(-1), keyPushed_(false), keyTimer_(TIMER),
    prevUp(false),prevDown(false)
{
    SetFontSize(32);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    level_arr.push_back(EASY);
    level_arr.push_back(NORMAL);
    level_arr.push_back(HARD);

    LevelText1 = "EASY";
    LevelText2 = "NORMAL";
    LevelText3 = "HARD";

}

void ChooseLevelScene::Initialize()
{
	hImage_back = LoadGraph("Assets/Scene/ChooseLevelBack.png");//�^�C�g���̔w�i
	assert(hImage_back >= 0);

    hDecideB = LoadGraph("Assets/UI/XboxBottunUI/decideB3.png");//B�����UI
    assert(hDecideB > 0);
}

void ChooseLevelScene::Update()
{
	padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);

	/*SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_PLAY);*/

    //if (CheckHitKey(KEY_INPUT_A) /*|| input.Buttons[4]*/)
    //{
    //    Level_ = 0;
    //    chooselevel_ = EASY;
    //}
    //if (CheckHitKey(KEY_INPUT_S) /*|| input.Buttons[4]*/)
    //{
    //    Level_ = 100;
    //    chooselevel_ = NORMAL;
    //}
    //if (CheckHitKey(KEY_INPUT_D) /*|| input.Buttons[4]*/)
    //{
    //    Level_ = 200;
    //    chooselevel_ = HARD;
    //}

    
    if (CheckHitKey(KEY_INPUT_UP) || input.Buttons[0] || input.ThumbLY >= 15000 )
    {
        if (!prevUp) 
        {
            currentlevel = Previous(currentlevel);
        }
        prevUp = true;
    }
    else {
        prevUp = false;
    }
 
    if (CheckHitKey(KEY_INPUT_DOWN) || input.Buttons[1] || input.ThumbLY <= -15000)
    {
        if (!prevDown)
        {
            currentlevel = Next(currentlevel);
        }
        prevDown = true;
    }
    else
    {
        prevDown = false;
    }


    // SPACE�L�[orStart�{�^��orB�{�^���������ꂽ��X�^�[�g�{�^����PlayScene�ɑJ��
    if (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_RETURN) || input.Buttons[4] || input.Buttons[13])
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
        //SetFontSize(32); //���Ƃɂ��ǂ�
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->SetLevelManager(currentlevel);
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
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_back, FALSE);
        DrawGraph(570, 600, hDecideB, TRUE);//������
        //DrawGraph(0, 350, hDecideB, TRUE);//��Փx�̉�
        al = keyTimer_;
    }
    else
    {
        // ��ʑS�̂ɔw�i�摜��`��
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_back, FALSE);
        DrawGraph(570, 600, hDecideB, TRUE);//������
        //DrawGraph(0, 350, hDecideB, TRUE);//��Փx�̉�
    }


    DrawFormatString(0, 0, GetColor(255, 255, 255), "��Փx��I�����Ă�������");
    //DrawFormatString(0, 120, GetColor(255, 255, 255), "��Փx�F %d", currentlevel);

    if (!keyPushed_) {
        switch (currentlevel)
        {
        case 0:
            DrawFormatString(CURSOR_POINT, 200, GetColor(255, 255, 255), "*");
            break;
        case 1:
            DrawFormatString(CURSOR_POINT, 250, GetColor(255, 255, 255), "*");
            break;
        case 2:
            DrawFormatString(CURSOR_POINT, 300, GetColor(255, 255, 255), "*");
            break;
        default:
            break;
        }
    }

    DrawFormatString(SCREENSIZE_HALF, 200, GetColor(255, 255, 255), LevelText1);
    DrawFormatString(SCREENSIZE_HALF, 250, GetColor(255, 255, 255), LevelText2);
    DrawFormatString(SCREENSIZE_HALF, 300, GetColor(255, 255, 255), LevelText3);
}

void ChooseLevelScene::Release()
{
    DeleteGraph(hDecideB);
    DeleteGraph(hImage_back);
}
