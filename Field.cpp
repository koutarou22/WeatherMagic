#include "Field.h"
#include <assert.h>
#include"Player.h"
#include "Bird.h"
#include "Camera.h"
#include "Engine/CsvReader.h"
#include "Slime.h"
#include "Ghost.h"
#include "HealItem.h"
#include "Rock.h"
#include "MpItem.h"
#include "ClearFlag.h"
#include "Engine/SceneManager.h"
#include "Weather.h"

Field::Field(GameObject* scene) : GameObject(scene)
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	
	Map = nullptr; // まずここでMapでnullいれとく
	hImage_ = LoadGraph("Assets/BackImage/bgchar_remake.png");
	assert(hImage_ > 0);

	/*hBackGround_ = LoadGraph("Assets/BackImage/bg5.png");*/
	hBackGround_ = LoadGraph("Assets/BackImage/background2.png");
	assert(hBackGround_ > 0);

	hBackGroundDark_ = LoadGraph("Assets/BackImage/background_dark.png");
	assert(hBackGroundDark_ > 0);

	NowStage_ = pSceneManager->GetClearCount();
	Reset(NowStage_); // Reset() 

	Stage_BgmHandle = LoadSoundMem("Assets/Music/BGM/STAGE_BGM.mp3");
	assert(Stage_BgmHandle != -1);

	ChangeVolumeSoundMem(128, Stage_BgmHandle);

	goalWid_ = -1;
}

Field::~Field()
{
	if (hImage_ > 0)
	{
		DeleteGraph(hImage_);
	}
	if (hBackGround_ > 0)
	{
		DeleteGraph(hBackGround_);
	}
	if (Map != nullptr)
	{
		delete[] Map;//Mapは動的配列なので[]をつける
	}
}

void Field::Reset()
{
	//LoadStage(NowStage_);
	
}

void Field::Update()
{
	padAnalogInput = GetJoypadXInputState(DX_INPUT_PAD1, &input);
}

void Field::Draw()
{
	int screenWidth, screenHeight, colorBitDepth;
	GetScreenState(&screenWidth, &screenHeight, &colorBitDepth);

	if (CheckHitKey(KEY_INPUT_Q) || input.Buttons[8] || input.Buttons[9])
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawExtendGraph(0, 0, screenWidth, screenHeight, hBackGroundDark_, TRUE);
	}

	// 画面全体に背景画像を描画
	DrawExtendGraph(0, 0, screenWidth, screenHeight, hBackGround_, FALSE);
	int scroll = 0;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		scroll = cam->GetValue();
	}

	Weather* pWeather = GetParent()->FindGameObject<Weather>();

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int chip = Map[y * width + x];

			if (isSnow[y * width + x]) //雪フラグ立ってて
			{
				if (pWeather->GetWeatherState() == Snow)//今雪なら
				{
					//hImage_ = LoadGraph("Assets/BackImage/bgchar_Snow.png");
					//足場チップに
					//薄いほう
					//DrawRectGraph(x * 32 - scroll, y * 32, 32 * 9, 32 * 2, 32, 32, hImage_, TRUE);
					//濃いほう
					DrawRectGraph(x * 32 - scroll, y * 32, 32 * 10, 32 * 2, 32, 32, hImage_, TRUE);
				}
			}
			else
			{
				DrawRectGraph(x * 32 - scroll, y * 32, 32 * (chip % 16), 32 * (chip / 16), 32, 32, hImage_, TRUE);
			}
			/*if (IsWallBlock(x * 32, y * 32))
			{
				DrawBox(x * 32 - scroll, y * 32, (x + 1) * 32 - scroll, (y + 1) * 32, GetColor(255, 0, 0), FALSE);
			}*/
		}
	}

}

int Field::CollisionRight(int x, int y)
{
	if (IsWallBlock(x + 1, y))
	{
		return (x + 1) % 32 + 1;
	}
	return 0;
}

int Field::CollisionDown(int x, int y)
{
	if (IsWallBlock(x, y + 1))
	{
		return (y + 1) % 32 + 1;
	}
	return 0;
}

int Field::CollisionLeft(int x, int y)
{
	if (IsWallBlock(x - 1, y))
	{
		return 32 - (x % 32);
	}
	return 0;
}

int Field::CollisionUp(int x, int y)
{
	if (IsWallBlock(x, y - 1))
	{
		return 32 - (y % 32);
	}
	return 0;
}

bool Field::IsWallBlock(int x, int y)
{
	int chipX = x / 32;
	int chipY = y / 32;

	//今が雪で、かつ雪チップのときに当たり判定をしたい
	Weather* pWea = GetParent()->FindGameObject<Weather>();

	switch (Map[chipY * width + chipX])
	{
		//case 3://ne
	case 16://地面
	case 17:
	case 18:
	case 19:
	case 32:
	case 33:
	case 34:
	case 35:
		return true;
	case 7:
	{
		if (pWea != nullptr)
		{
			if (pWea->GetWeatherState() == Snow)//今が雪
			{
				return true;
			}
		}
	}
	break;
	};

	return false;
}

bool Field::IsHitClear(int x, int y)
{
	int chipX = x / 32;
	int chipY = y / 32;
	switch (Map[chipY * width + chipX])
	{
	case 6:
		return true;
	};
	return false;
}





bool Field::IsHitRock(int x, int y)
{
	int chipX = x / 32;
	int chipY = y / 32;

	switch (Map[chipY * width + chipX])
	{
	case 3:
		return true;
	}

	return false;
}

void Field::Reset(int num)
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	PlaySoundMem(Stage_BgmHandle, DX_PLAYTYPE_LOOP);


	if (Map != nullptr)
	{
		delete[] Map;
		Map = nullptr;
	}

	CsvReader csv;
	bool ret = false;

	switch (num)
	{
	case 0:
		ret = csv.Load("Assets/Stage_csv/stage0.csv");
		//ret = csv.Load("Assets/Stage_csv/debug.csv");//ForTestPlay
		break;
	case 100:
		ret = csv.Load("Assets/Stage_csv/debug.csv");
		break;
	default:
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
		ret = csv.Load("Assets/Stage_csv/debug.csv");
		break;
	}

	assert(ret);

	width = csv.GetWidth();
	height = 23;
	Map = new int[width * height];
	isSnow = new bool[width * height];

	WhereIsGoal(width, height, csv); //ゴールのwidthをとってくる

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			isSnow[h * width + w] = false;
			switch (csv.GetInt(w, h /*+ height + 1*/))
			{
			case 0:
			{
				Player* pPlayer = GetParent()->FindGameObject<Player>();
				pPlayer->SetPosition(w * 32, h * 32);
				break;
			}

			case 1:
			{
				Ghost* pGhost = Instantiate<Ghost>(GetParent());
				pGhost->SetPosition(w * 32, h * 32);
				break;
			}

			case 2:
			{
				Slime* pSlime = Instantiate<Slime>(GetParent());
				pSlime->SetPosition(w * 32, h * 32);
				break;

			}
			case 3:
			{
				Rock* pRock = Instantiate<Rock>(GetParent());
				pRock->SetPosition(w * 32, h * 32);
				break;
			}

			case 4:
			{
				HealItem* pHeal = Instantiate<HealItem>(GetParent());
				pHeal->SetPosition(w * 32, h * 32);
				break;
			}

			case 5:
			{
				MpItem* pMp = Instantiate<MpItem>(GetParent());
				pMp->SetPosition(w * 32, h * 32);
				break;
			}

			case 6:
			{
				ClearFlag* pClear = Instantiate<ClearFlag>(GetParent());
				pClear->SetPosition(w * 32, h * 32);

				break;
			}
			case 7: //雪の時
			{
				isSnow[h * width + w] = true;
				break;
			}

			default:
				break;
			}
			Map[h * width + w] = csv.GetValue(w, h);
		}
	}
}

//void Field::Reset(int StageNumber)
//{
//	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
//
//	if (Map != nullptr)
//	{
//		delete[] Map;
//		Map = nullptr;
//	}
//
//	CsvReader csv;
//	bool ret = false;
//
//	switch (StageNumber)
//	{
//	case 1:
//		ret = csv.Load("Assets/Stage_csv/debug.csv");
//		//ret = csv.Load("Assets/Stage_csv/debug.csv");//ForTestPlay
//		break;
//	case 2:
//		ret = csv.Load("Assets/Stage_csv/stage0.csv");
//		break;
//	default:
//		StageNumber = 1;
//		break;
//	}
//
//	assert(ret);
//
//	width = csv.GetWidth();
//	height = 23;
//	Map = new int[width * height];
//	isSnow = new bool[width * height];
//
//	WhereIsGoal(width, height, csv); //ゴールのwidthをとってくる
//
//	for (int h = 0; h < height; h++)
//	{
//		for (int w = 0; w < width; w++)
//		{
//			isSnow[h * width + w] = false;
//			switch (csv.GetInt(w, h /*+ height + 1*/))
//			{
//			case 0:
//			{
//				Player* pPlayer = GetParent()->FindGameObject<Player>();
//				pPlayer->SetPosition(w * 32, h * 32);
//				break;
//			}
//
//			case 1:
//			{
//				Ghost* pGhost = Instantiate<Ghost>(GetParent());
//				pGhost->SetPosition(w * 32, h * 32);
//				break;
//			}
//
//			case 2:
//			{
//				Slime* pSlime = Instantiate<Slime>(GetParent());
//				pSlime->SetPosition(w * 32, h * 32);
//				break;
//
//			}
//			case 3:
//			{
//				Rock* pRock = Instantiate<Rock>(GetParent());
//				pRock->SetPosition(w * 32, h * 32);
//				break;
//			}
//
//			case 4:
//			{
//				HealItem* pHeal = Instantiate<HealItem>(GetParent());
//				pHeal->SetPosition(w * 32, h * 32);
//				break;
//			}
//
//			case 5:
//			{
//				MpItem* pMp = Instantiate<MpItem>(GetParent());
//				pMp->SetPosition(w * 32, h * 32);
//				break;
//			}
//
//			case 6:
//			{
//				ClearFlag* pClear = Instantiate<ClearFlag>(GetParent());
//				pClear->SetPosition(w * 32, h * 32);
//				break;
//			}
//			case 7: //雪の時
//			{
//				isSnow[h * width + w] = true;
//				break;
//			}
//
//			default:
//				break;
//			}
//			Map[h * width + w] = csv.GetValue(w, h);
//		}
//	}
//}
//
//void Field::NextLoadStage()
//{
//	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
//	//if (pSceneManager != nullptr)
//	//{
//	//	NowStage_ = pSceneManager->GetNextStage();  // SceneManagerから次のステージ番号を取得
//	//}
//	NowStage_++;
//	LoadStage(NowStage_); // 次のステージをロード
//}


void Field::WhereIsGoal(int w, int h, CsvReader c)
{
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			if (c.GetInt(i, j) == 6)
			{
				goalWid_ = i;
			}
		}
	}
}

void Field::StopPlayBGM()
{
	StopSoundMem(Stage_BgmHandle);
}
