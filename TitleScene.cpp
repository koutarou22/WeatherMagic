#include "DxLib.h"
#include "TitleScene.h"
#include "TestScene.h"
#include "Engine/SceneManager.h"

// タイトル画面のテキスト
const char* TITLE_TEXT = "Press P Key to start";
using std::string;

TitleScene::TitleScene(GameObject* parent)
    : GameObject(parent, "TitleScene")
{
}

void TitleScene::Initialize()
{
    hImage_ = LoadGraph("Assets/OIG3.jpg");
    assert(hImage_ >= 0);
    charImage_ = LoadGraph("Assets/Weather.png");
    assert(charImage_ >= 0);
    spaceImage_ = LoadGraph("Assets/Space.png");
    assert(spaceImage_ >= 0);

    soundHandle = LoadSoundMem("Assets/select01.mp3");
    assert(soundHandle != -1); // 音声ファイルの読み込みに失敗した場合のエラーチェック


}

void TitleScene::Update()
{
    // スペースキーが押されたらTestSceneに遷移
    if (CheckHitKey(KEY_INPUT_P)) {
        PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK); // 音声を再生
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TEST);
        PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK);
    }
}

void TitleScene::Draw()
{
    int x = (int)transform_.position_.x;
    int y = (int)transform_.position_.y;

    int screenWidth, screenHeight, colorBitDepth;
    GetScreenState(&screenWidth, &screenHeight, &colorBitDepth);

   
    // 画面全体に背景画像を描画
    DrawExtendGraph(0, 0, screenWidth, screenHeight, hImage_, FALSE);
    // タイトル画面のテキストを描画
    DrawString(700, 150, TITLE_TEXT, GetColor(255, 255, 255));
    DrawGraph(600, 40, charImage_, TRUE);
    
}

void TitleScene::Release()
{
}