#include "Field.h"
#include <assert.h>
#include"Player.h"
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
#include"ChooseLevelScene.h"
#include"MoveUI.h"
#include"JumpUI.h"
#include"AttackUI.h"
#include"ChangeRainUI.h"
#include"ChangeSunUI.h"
#include"ChangeWindUI.h"
#include"ChangeSnowUI.h"
#include"MoveStoneUI.h"

Field::Field(GameObject* scene) : GameObject(scene)
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");

	Map = nullptr; 
	hStageChipImage_= LoadGraph("Assets/BackImage/bgchar_remake.png");
	assert(hStageChipImage_ > 0);

	hBackGround_ = LoadGraph("Assets/BackImage/bg4.png");
	assert(hBackGround_ > 0);

	hBackGroundDark_ = LoadGraph("Assets/BackImage/background_dark.png");
	assert(hBackGroundDark_ > 0);

	NowStage_ = pSceneManager->GettLevelManager();
	Reset(NowStage_);

	goalWid_ = -1;
}

Field::~Field()
{
	if (hStageChipImage_ > 0)
	{
		DeleteGraph(hStageChipImage_);
	}
	if (hBackGround_ > 0)
	{
		DeleteGraph(hBackGround_);
	}
	if (Stage_BgmHandle > 0)
	{
		DeleteGraph(Stage_BgmHandle);
	}
	if (Map != nullptr)
	{
		delete[] Map;
		Map = nullptr;
	}

	if (isSnow != nullptr)
	{
		delete[] isSnow;
		isSnow = nullptr;
	}
}

void Field::Reset()
{
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

			//天候が雪の場合新しいブロックを描画する処理
			if (isSnow[y * width + x]) 
			{
				if (pWeather->GetWeatherState() == Snow)
				{
					DrawRectGraph(x * 32 - scroll, y * 32, 32 * 10, 32 * 2, 32, 32, hStageChipImage_, TRUE);
				}
			}
			else
			{
				DrawRectGraph(x * 32 - scroll, y * 32, 32 * (chip % 16), 32 * (chip / 16), 32, 32, hStageChipImage_, TRUE);
			}
		}
	}

}

void Field::Release()
{
	
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

	Weather* pWeather = GetParent()->FindGameObject<Weather>();

	if (Map != nullptr)
	{
		int index = chipY * width + chipX;
		if (index >= 0 && index < width * height)
		{
			switch (Map[index])
			{
			case 16: 
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
				if (pWeather != nullptr)
				{
					if (pWeather->GetWeatherState() == Snow)
					{
						return true;
					}
				}
			}
			break;
			}
		}
	}
	return false;
}

bool Field::IsHitClear(int x, int y)
{
	int chipX = x / 32;
	int chipY = y / 32;
	if (Map != nullptr)
	{
		int index = chipY * width + chipX;
		if (index >= 0 && index < width * height)
		{
			switch (Map[index])
			{
			case 6:
				return true;
			};
		}
	}
	return false;
}

bool Field::IsHitRock(int x, int y)
{
	int chipX = x / 32;
	int chipY = y / 32;
	if (Map != nullptr)
	{
		int index = chipY * width + chipX;
		if (index >= 0 && index < width * height)
		{
			switch (Map[index])
			{
			case 3:
				return true;
			}
		}
	}
	return false;
}

void Field::Reset(int num)
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");

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
		ret = csv.Load("Assets/Stage_csv/stage_easy.csv");
		break;
	case 1:
		ret = csv.Load("Assets/Stage_csv/stage_normal.csv");
		break;
	case 2:
		ret = csv.Load("Assets/Stage_csv/stage_hard.csv");
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


	WhereIsGoal(width, height, csv); //ゴールまでのWidthを取得

	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			isSnow[h * width + w] = false;

			//オブジェクトの情報をcsvに格納
			switch (csv.GetInt(w, h ))
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
			case 7:
			{
				isSnow[h * width + w] = true;
				break;
			}
			case 8:
			{
				MoveUI* pMUI = Instantiate<MoveUI>(GetParent());
				pMUI->SetPosition(w * 32, h * 32);
				break;
			}
			case 9:
			{
				JumpUI* pJUI = Instantiate<JumpUI>(GetParent());
				pJUI->SetPosition(w * 32, h * 32);
				break;
			}
			case 10:
			{
				AttackUI* pAUI = Instantiate<AttackUI>(GetParent());
				pAUI->SetPosition(w * 32, h * 32);
				break;
			}
			case 11:
			{
				ChangeRainUI* pCRUI = Instantiate<ChangeRainUI>(GetParent());
				pCRUI->SetPosition(w * 32, h * 32);
				break;
			}
			case 12:
			{
				ChangeSunUI* pCSUI = Instantiate<ChangeSunUI>(GetParent());
				pCSUI->SetPosition(w * 32, h * 32);
				break;
			}
			case 13:
			{
				ChangeWindUI* pCWUI = Instantiate<ChangeWindUI>(GetParent());
				pCWUI->SetPosition(w * 32, h * 32);
				break;
			}
			case 14:
			{
				ChangeSnowUI* pCSnUI = Instantiate<ChangeSnowUI>(GetParent());
				pCSnUI->SetPosition(w * 32, h * 32);
				break;
			}
			case 15:
			{
				MoveStoneUI* pMSUI = Instantiate<MoveStoneUI>(GetParent());
				pMSUI->SetPosition(w * 32, h * 32);
				break;
			}
			default:
				break;
			}
			Map[h * width + w] = csv.GetValue(w, h);
		}
	}
}

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
