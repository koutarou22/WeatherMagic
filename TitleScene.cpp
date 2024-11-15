#include "DxLib.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "Engine/SceneManager.h"

// �^�C�g����ʂ̃e�L�X�g
const char* TITLE_TEXT = "Press P Key to start";
using std::string;

namespace
{
    const int TIMER = 255;
    const int MOJI_TIMER = 100;
}

TitleScene::TitleScene(GameObject* parent)
    : GameObject(parent, "TitleScene")
{
    hImage_ = -1;
    charImage_ = -1;
    spaceImage_ = -1;
    soundHandle = -1;

    keyTimer_ = TIMER;
    keyPushed_ = false;

    mojiTimer_ = MOJI_TIMER;
    mojiend_ = false;

    SetFontSize(16);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::Initialize()
{
    hImage_ = LoadGraph("Assets/Scene/Title.jpg");//�^�C�g���̔w�i
    assert(hImage_ >= 0);

    charImage_ = LoadGraph("Assets/Font/Weather.png");//�wWeatherMagic�x�̃^�C�g���t�H���g
    assert(charImage_ >= 0);

   /* spaceImage_ = LoadGraph("Assets/Space.png");//�wspace�x�������Ă���I�I�ȃt�H���g�@���ǖ��g�p
    assert(spaceImage_ >= 0);*/

    soundHandle = LoadSoundMem("Assets/Music/SE/select01.mp3");//P�����������Ɍ��ʉ����Ȃ�(�o�^)
    assert(soundHandle != -1); // �����t�@�C���̓ǂݍ��݂Ɏ��s�����ꍇ�̃G���[�`�F�b�N
}

void TitleScene::Update()
{
    padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);

    // �X�y�[�X�L�[��������邩�X�^�[�g�{�^����TestScene�ɑJ��
    if (CheckHitKey(KEY_INPUT_P) || input.Buttons[4]) {
        PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK); // �������Đ�
        keyPushed_ = true;
    }

    if (keyPushed_)
    {
        if (mojiend_)
        {
            keyTimer_--;
        }
        else
        {
            mojiTimer_--;
        }
    }

    //�^�C�}�[���I�������(�Ó]���I�������)
    if (keyTimer_ < 0)
    {
        SetFontSize(32); //���Ƃɂ��ǂ�
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_PLAY);
        PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
    }

    //�����^�C�}�[���I�������(�҂��҂��I�������)
    if (mojiTimer_ < 0)
    {
        mojiend_ = true;
    }
}

void TitleScene::Draw()
{
    int x = (int)transform_.position_.x;
    int y = (int)transform_.position_.y;

    int screenWidth, screenHeight, colorBitDepth;
    GetScreenState(&screenWidth, &screenHeight, &colorBitDepth);
  
//�������炷���Ó]���Ă���
#if 0
    if (keyPushed_)
    {
        static int al = TIMER;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, al);
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_, FALSE);
        al = keyTimer_;
    }
    else
    {
        // ��ʑS�̂ɔw�i�摜��`��
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_, FALSE);
        // �^�C�g����ʂ̃e�L�X�g��`��
        DrawString(700, 150, TITLE_TEXT, GetColor(255, 255, 255));
        DrawGraph(600, 40, charImage_, TRUE);
    }
#endif

//��������Push P~��������ƌ����ĈÓ]
#if 1
    if (keyPushed_&&mojiend_) //�����҂��҂��I�����
    {
        SetFontSize(16);
        static int al = TIMER;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, al);
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_, FALSE);
        al = keyTimer_;
    }
    else if(keyPushed_&&!mojiend_) //�����҂��҂������Ă���
    {
        //SetFontSize(18); //��u�������傫����������܂�
        // ��ʑS�̂ɔw�i�摜��`��
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_, FALSE);
        // �^�C�g����ʂ̃e�L�X�g��`��
        DrawString(700, 150, TITLE_TEXT, GetColor(255, 255, 0));
        DrawGraph(600, 40, charImage_, TRUE);
    }
    else //���������L�[��������ĂȂ�
    {
        // ��ʑS�̂ɔw�i�摜��`��
        DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_, FALSE);
        // �^�C�g����ʂ̃e�L�X�g��`��
        DrawString(700, 150, TITLE_TEXT, GetColor(255, 255, 255));
        DrawGraph(600, 40, charImage_, TRUE);
    }
#endif
}

void TitleScene::Release()
{
}