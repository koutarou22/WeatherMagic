#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include"GameOverScene.h"

namespace
{
	const int TIMER = 100;
}

GameOverScene::GameOverScene(GameObject* parent) : GameObject(parent, "GameOverScene")
{

  hImage_ = LoadGraph("Assets/Scene/GAME OVER1.png");
  assert(hImage_ > 0);

	keyTimer_ = TIMER;
	keyPushed_ = false;
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void GameOverScene::Initialize()
{
	// ゲームオーバーシーンの初期化処理...
}

void GameOverScene::Update()
{
	padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);
	// スペースキーが押されたらスタートボタンでTitleSceneに遷移
	if (CheckHitKey(KEY_INPUT_SPACE) ||  input.Buttons[4]) {
		keyPushed_ = true;
	}

	if (keyPushed_)
	{

		keyTimer_--;
	}

	//タイマーが終わったら(暗転が終わったら)
	if (keyTimer_ < 0)
	{
		SetFontSize(32); //もとにもどす
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

void GameOverScene::Draw()
{
	if (keyPushed_)
	{
		static int al = TIMER;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, al);
		DrawGraph(0, 0, hImage_, TRUE);
		al = keyTimer_;
	}
	else
	{
		// 画面全体に背景画像を描画
		DrawGraph(0, 0, hImage_, TRUE);
	}


	/*  DrawString(0, 0, "GAME OVER", GetColor(255, 255, 255));
	  DrawString(0, 20, "Press SPACE to return to title", GetColor(255, 255, 255));*/
}

void GameOverScene::Release()
{

}