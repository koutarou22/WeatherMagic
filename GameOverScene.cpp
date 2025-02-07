#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include"GameOverScene.h"
#include "Debug.h"

namespace
{
	const int TIMER = 100;
	const int YELLOW = GetColor(255, 255, 0); //黄色
	const int WHITE = GetColor(255, 255, 255); //白

	const int scrHalf = 1280 / 2;//スクリーンの半分

	const int Cursor_x = 300;//x座標の計算用
	const int Cursor_y = 630;//"*"のy座標
	const int Cursor_Point_Left = scrHalf - Cursor_x - 20;//"*"の位置(左) 320
	const int Cursor_Point_Right = scrHalf + Cursor_x - 20;//"*"の位置(右) 920
	const int Retry_Position_x = scrHalf - Cursor_x;//"Retry"の座標x
	const int Title_Position_x = scrHalf + Cursor_x;//"Retry"の座標x

	const int DecideB_x = 580;//b決定ボタンのx座標
	const int DecideB_y = 660;//b決定ボタンのy座標

	const int Fontsize = 32;
}

GameOverScene::GameOverScene(GameObject* parent) : GameObject(parent, "GameOverScene")
{
	hBack_ = LoadGraph("Assets/Scene/GAME OVER1.png");
	assert(hBack_ > 0);

	keyTimer_ = TIMER;
	keyPushed_ = false;
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	GameOverBGMHandle_ = LoadSoundMem("Assets/Music/BGM/GAMEOVER_BGM.mp3");
	assert(GameOverBGMHandle_ != -1);

	PlaySoundMem(GameOverBGMHandle_, DX_PLAYTYPE_BACK);

	isLeft_ = true;
	RightCheck_ = false;
	LeftCheck_ = false;
  
	hDecideB_ = LoadGraph("Assets/UI/XboxBottunUI/decideB.png");
	assert(hDecideB_ > 0);

	hDecideBYellow_ = LoadGraph("Assets/UI/XboxBottunUI/decideB1.png");//B決定のUI（黄色）サイズ違う
	assert(hDecideBYellow_ > 0);

	SelectSEHandle_ = LoadSoundMem("Assets/Music/SE/Select/Select0.mp3");//選択時のSE
	assert(SelectSEHandle_ > 0);

	DecisionHandle_ = LoadSoundMem("Assets/Music/SE/SceneSwitch/Select02.mp3");//選択時のSE
	assert(DecisionHandle_ > 0);
}

GameOverScene::~GameOverScene()
{
	Release();
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
	//スペースキーorBボタンorスタートボタンが押されたらスタートボタンでTitleSceneに遷移
	if (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_RETURN) || input.Buttons[4] || input.Buttons[13]) 
	{
		keyPushed_ = true;
		PlaySoundMem(DecisionHandle_, DX_PLAYTYPE_BACK);
		StopSoundMem(GameOverBGMHandle_);
	}

	if (keyPushed_)
	{

		keyTimer_--;
	}

	ChangeScene(); //シーン遷移

	Debug::OutPrint(isLeft_, true);
}

void GameOverScene::Draw()
{
	if (keyPushed_)
	{
		static int al = TIMER;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, al);
		DrawGraph(0, 0, hBack_, TRUE);
		DrawGraph(DecideB_x, DecideB_y, hDecideBYellow_, TRUE);
		al = keyTimer_;
	}
	else
	{
		// 画面全体に背景画像を描画
		DrawGraph(0, 0, hBack_, TRUE);
		DrawGraph(DecideB_x, DecideB_y, hDecideB_, TRUE);
	}

	//Retryとtitle描く
	DrawScene();
}

void GameOverScene::Release()
{
	if (hBack_ > 0)
	{
		DeleteGraph(hBack_);
	}
	if (hDecideB_ > 0)
	{
		DeleteGraph(hDecideB_);
	}

	if (hDecideBYellow_ > 0)
	{
		DeleteGraph(hDecideBYellow_);
	}

	//SE BGM
	if (GameOverBGMHandle_ > 0)
	{
		DeleteSoundMem(GameOverBGMHandle_);
	}
	if (SelectSEHandle_ > 0)
	{
		DeleteSoundMem(SelectSEHandle_);
	}
	if (DecisionHandle_ > 0)
	{
		DeleteSoundMem(DecisionHandle_);
	}
}

void GameOverScene::DrawScene()
{
	if (isLeft_)
	{
		DrawFormatString(Cursor_Point_Left, Cursor_y, WHITE, "%s", "*");
	}
	else
	{
		DrawFormatString(Cursor_Point_Right, Cursor_y, WHITE, "%s", "*");
	}

	DrawFormatString(Retry_Position_x, Cursor_y,WHITE, "%s", "Retry");
	DrawFormatString(Title_Position_x, Cursor_y,WHITE, "%s", "Title");
}

void GameOverScene::ChangeScene()
{
	if (isLeft_)
	{
		//タイマーが終わったら(暗転が終わったら)
		if (keyTimer_ < 0)
		{
			SetFontSize(Fontsize); //もとにもどす
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_PLAY);
		}
	}
	else
	{
		//タイマーが終わったら(暗転が終わったら)
		if (keyTimer_ < 0)
		{
			SetFontSize(Fontsize); //もとにもどす
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_TITLE);
		}
	}
}

void GameOverScene::CheckRL()
{
	// 左入力のチェック
	if (CheckHitKey(KEY_INPUT_LEFT) || input.Buttons[2] || input.ThumbLX <= -10000)
	{
		if (!isLeft_)
		{
			isLeft_ = true;
			// 左右選択時のBGM入れるならここ
			PlaySoundMem(SelectSEHandle_, DX_PLAYTYPE_BACK);
		}
		LeftCheck_ = true;
		RightCheck_ = false;
	}
	else
	{
		LeftCheck_ = false;
	}

	if (CheckHitKey(KEY_INPUT_RIGHT) || input.Buttons[3] || input.ThumbLX >= 10000)
	{
		if (isLeft_)
		{
			isLeft_ = false;
			// 左右選択時のBGM入れるならここ
			PlaySoundMem(SelectSEHandle_, DX_PLAYTYPE_BACK);
		}
		RightCheck_ = true;
		LeftCheck_ = false;
	}
	else
	{
		RightCheck_ = false;
	}
}
