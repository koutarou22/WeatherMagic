#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include"GameOverScene.h"
#include "Debug.h"

namespace
{
	const int TIMER = 100;
	const int YELLOW = GetColor(255, 255, 0); //黄色
	const int WHITE = GetColor(255, 250, 255); //白
}

GameOverScene::GameOverScene(GameObject* parent) : GameObject(parent, "GameOverScene")
{

	hImage_ = LoadGraph("Assets/Scene/GAME OVER1.png");
	assert(hImage_ > 0);

	keyTimer_ = TIMER;
	keyPushed_ = false;
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	GameOverBGMHandle = LoadSoundMem("Assets/Music/BGM/GAMEOVER_BGM.mp3");
	assert(GameOverBGMHandle != -1);

	PlaySoundMem(GameOverBGMHandle, DX_PLAYTYPE_BACK);

	isLeft = true;
  
	hdecB = LoadGraph("Assets/UI/XboxBottunUI/decideB.png");
	assert(hdecB > 0);
}

void GameOverScene::Initialize()
{
}

void GameOverScene::Update()
{
	padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);

	//左右選択
	CheckRL(); 

	//キー確定~暗転まで
	//スペースキーが押されたらスタートボタンでTitleSceneに遷移
	if (CheckHitKey(KEY_INPUT_SPACE) || input.Buttons[4]) {
		keyPushed_ = true;
		StopSoundMem(GameOverBGMHandle);
	}

	if (keyPushed_)
	{

		keyTimer_--;
	}

	ChangeScene(); //シーン遷移

	Debug::OutPrint(isLeft, true);
}

void GameOverScene::Draw()
{
	if (keyPushed_)
	{
		static int al = TIMER;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, al);
		DrawGraph(0, 0, hImage_, TRUE);
		DrawGraph(580, 660, hdecB, TRUE);
		al = keyTimer_;
	}
	else
	{
		// 画面全体に背景画像を描画
		DrawGraph(0, 0, hImage_, TRUE);
		DrawGraph(580, 660, hdecB, TRUE);
	}

	//Retryとtitle描く
	DrawScene();


	/*  DrawString(0, 0, "GAME OVER", GetColor(255, 255, 255));
	  DrawString(0, 20, "Press SPACE to return to title", GetColor(255, 255, 255));*/
}

void GameOverScene::Release()
{

}

void GameOverScene::DrawScene()
{
	int scrHalf = 1280 / 2;
	int ma = 300; //ごめんなさい！
	int y = 630;
	if (isLeft)
	{
		DrawFormatString(scrHalf - ma-20, y, WHITE, "%s", "*");
	}
	else
	{
		DrawFormatString(scrHalf + ma-20, y, WHITE, "%s", "*");
	}

	DrawFormatString(scrHalf - ma, y,WHITE, "%s", "Retry");
	DrawFormatString(scrHalf + ma, y,WHITE, "%s", "Title");
}

void GameOverScene::ChangeScene()
{
	if (isLeft)
	{
		//タイマーが終わったら(暗転が終わったら)
		if (keyTimer_ < 0)
		{
			SetFontSize(32); //もとにもどす
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_PLAY);
		}
	}
	else
	{
		//タイマーが終わったら(暗転が終わったら)
		if (keyTimer_ < 0)
		{
			SetFontSize(32); //もとにもどす
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_TITLE);
		}
	}
}

void GameOverScene::CheckRL()
{
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		isLeft = true;
		//左右選択時のBGM入れるならここ
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		isLeft = false;
		//左右選択時のBGM入れるならここ
	}
}