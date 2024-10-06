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

Field::Field(GameObject* scene) : GameObject(scene)
{
	Map = nullptr; // まずここでMapでnullいれとく
	hImage_ = LoadGraph("Assets/BackImage/bgchar.png");
	assert(hImage_ > 0);

	/*hBackGround_ = LoadGraph("Assets/BackImage/bg5.png");*/
	hBackGround_ = LoadGraph("Assets/BackImage/background2.png");
	assert(hBackGround_ > 0);

	NowStage_ = 1; 
	Reset(); // Reset() メソッドを有効にする
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
	LoadStage(NowStage_);
	//if (Map != nullptr)
	//{
	//	delete[] Map;
	//	Map = nullptr;
	//}

	//CsvReader csv;
	//bool ret = csv.Load("Assets/New_Stage2.csv");
	//assert(ret);

	//width = csv.GetWidth();
	//height = 22/*csv.GetHeight()*/;
	//Map = new int[width * height];

	////for (int h = 0; h < height; h++)
	////{
	////	if (csv.GetString(0, h) == "")
	////	{
	////		height = h;
	////		break;
	////	}
	////	for (int w = 0; w < width; w++)
	////	{
	////		Map[h * width + w] = csv.GetInt(w,h);
	////	}
	////}

	//for (int h = 0; h < height; h++)
	//{
	//	for (int w = 0; w < width; w++)
	//	{
	//		switch (csv.GetInt(w, h /*+ height + 1*/))
	//		{
	//		case 0:
	//		{
	//			Player* pPlayer = GetParent()->FindGameObject<Player>();
	//			pPlayer->SetPosition(w * 32, h * 32);
	//			break;
	//		}
	//		
	//		case 1:
	//		{
	//			Ghost* pGhost = Instantiate<Ghost>(GetParent());
	//			pGhost->SetPosition(w * 32, h * 32);
	//			break;
	//		}
	//		
	//		case 2:
	//		{
	//			Slime* pSlime = Instantiate<Slime>(GetParent());
	//			pSlime->SetPosition(w * 32, h * 32);
	//			break;

	//		}
	//		case 3:
	//		{
	//			Rock* pRock = Instantiate<Rock>(GetParent());
	//			pRock->SetPosition(w * 32, h * 32);
	//			break;
	//		}

	//		case 4:
	//		{
	//			HealItem* pHeal = Instantiate<HealItem>(GetParent());
	//			pHeal->SetPosition(w * 32, h * 32);
	//			break;
	//		}

	//		case 5:
	//		{
	//			MpItem* pMp = Instantiate<MpItem>(GetParent());
	//			pMp->SetPosition(w * 32, h * 32);
	//			break;
	//		}

	//		case 6:
	//		{
	//			ClearFlag* pClear = Instantiate<ClearFlag>(GetParent());
	//			pClear->SetPosition(w * 32, h * 32);
	//			break;
	//		}
	//		
	//		default:
	//			break;
	//		}
	//		Map[h * width + w] = csv.GetValue(w, h);
	//	}
	//}
	////Update();


}	

void Field::Update()
{

}

void Field::Draw()
{
	
	int screenWidth, screenHeight, colorBitDepth;
	GetScreenState(&screenWidth, &screenHeight, &colorBitDepth);

	// 画面全体に背景画像を描画
	DrawExtendGraph(0, 0, screenWidth, screenHeight, hBackGround_, FALSE); 
	int scroll = 0;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		scroll = cam->GetValue();
	}

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int chip = Map[y * width + x];
			DrawRectGraph(x * 32 - scroll, y * 32, 32 * (chip % 16), 32 * (chip / 16), 32, 32, hImage_, TRUE);
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
	if (IsWallBlock(x, y-1))
	{
		return 32 - (y % 32);
	}
	return 0;
}

bool Field::IsWallBlock(int x, int y)
{
	int chipX = x / 32;
	int chipY = y / 32;

	switch (Map[chipY * width + chipX])
	{
	//case 3://new
	case 16://地面
	case 17:
	case 18:
	case 19:
	case 32:
	case 33:
	case 34:
	case 35:
		return true;
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
	case 200:
		return true;

	};

	return false;
}

void Field::LoadStage(int StageNumber)
{
	if (Map != nullptr)
	{
		delete[] Map;
		Map = nullptr;
	}

	CsvReader csv;
	bool ret = false;

	switch (StageNumber)
	{
	case 1:
		ret = csv.Load("Assets/Stage_csv/Stage1.csv");
		break;
	case 2:
		ret = csv.Load("Assets/Stage_csv/Stage2.csv");
		break;
	default:
		//assert(false); // 未知のステージ番号
		StageNumber = 1;
		break;
	}

	assert(ret);

	width = csv.GetWidth();
	height = 22;
	Map = new int[width * height];

	for (int h = 0; h < height; h++)
	{
			for (int w = 0; w < width; w++)
			{
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
				
				default:
				break;
			}
			Map[h * width + w] = csv.GetValue(w, h);
	     }
	}
}

void Field::NextLoadStage()
{
	NowStage_++; // ステージ番号を増やす
	LoadStage(NowStage_); // 次のステージをロード
}
