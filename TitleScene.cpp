#include "DxLib.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "Engine/SceneManager.h"

// �^�C�g����ʂ̃e�L�X�g
const char* TITLE_TEXT = "Press P Key to start";
using std::string;

TitleScene::TitleScene(GameObject* parent)
    : GameObject(parent, "TitleScene")
{
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
    // �X�y�[�X�L�[�������ꂽ��TestScene�ɑJ��
    if (CheckHitKey(KEY_INPUT_P)) {
        PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK); // �������Đ�
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_PLAY);
        PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
    }
}

void TitleScene::Draw()
{
    int x = (int)transform_.position_.x;
    int y = (int)transform_.position_.y;

    int screenWidth, screenHeight, colorBitDepth;
    GetScreenState(&screenWidth, &screenHeight, &colorBitDepth);

   
    // ��ʑS�̂ɔw�i�摜��`��
    DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_, FALSE);
    // �^�C�g����ʂ̃e�L�X�g��`��
    DrawString(700, 150, TITLE_TEXT, GetColor(255, 255, 255));
    DrawGraph(600, 40, charImage_, TRUE);
    
}

void TitleScene::Release()
{
}