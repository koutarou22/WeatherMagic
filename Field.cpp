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

//switch•¶‚Ìcase‚Ì”Žš‚Ícsv“à‚Ì’l‚ðŽ¦‚µ‚Ä‚¢‚é
Field::Field(GameObject* scene) :GameObject(scene)
{
	Map = nullptr;//‚Ü‚¸‚±‚±‚ÅMap‚Ånull‚¢‚ê‚Æ‚­
	//hImage_ = LoadGraph("Assets/bgchar.png");
	hImage_ = LoadGraph("Assets/bgchar.png");
	
	assert(hImage_ > 0);

	hBackGround_ = LoadGraph("Assets/bg5.png");
	assert(hBackGround_ > 0);

	Reset();
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
		delete[] Map;//Map‚Í“®“I”z—ñ‚È‚Ì‚Å[]‚ð‚Â‚¯‚é
	}
}

void Field::Reset()
{
	if (Map != nullptr)
	{
		delete[] Map;
		Map = nullptr;
	}

	CsvReader csv;
	bool ret = csv.Load("Assets/stage9(in).csv");
	assert(ret);

	width = csv.GetWidth();
	height = 22/*csv.GetHeight()*/;
	Map = new int[width * height];

	//for (int h = 0; h < height; h++)
	//{
	//	if (csv.GetString(0, h) == "")
	//	{
	//		height = h;
	//		break;
	//	}
	//	for (int w = 0; w < width; w++)
	//	{
	//		Map[h * width + w] = csv.GetInt(w,h);
	//	}
	//}

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
			
			default:
				break;
			}
			Map[h * width + w] = csv.GetValue(w, h);
		}
	}

}	

void Field::Update()
{
	
}

void Field::Draw()
{
	
	int screenWidth, screenHeight, colorBitDepth;
	GetScreenState(&screenWidth, &screenHeight, &colorBitDepth);

	// ‰æ–Ê‘S‘Ì‚É”wŒi‰æ‘œ‚ð•`‰æ
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
	 case 16://’n–Ê
	 case 17:
	 case 18:
	 case 19:
	 case 32:
	 case 33:
	 case 34:
	 case 35:
		 return true;
		 
	};

	return false;
}

bool Field::IsHitClear(int x, int y)
{
	int chipX = x / 32;
	int chipY = y / 32;
	switch (Map[chipY * width + chipX])
	{
	case 128://’n–Ê
	case 129:
	case 130:
	case 131:
	case 132:
	case 133:
	case 144:
	case 145:
	case 146:
	case 147:
	case 148:
	case 149:
	case 160:
	case 161:
	case 162:
	case 163:
	case 164:
	case 165:
	case 176:
	case 177:
	case 178:
	case 179:
	case 180:
	case 181:
	case 192:
	case 193:
	case 194:
	case 195:
	case 196:
	case 197:
		return true;

	};

	return false;
}
