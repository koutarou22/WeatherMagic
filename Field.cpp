#include "Field.h"
#include <assert.h>
#include"Player.h"
#include "Bird.h"
#include "Camera.h"
#include "Engine/CsvReader.h"


//switch文のcaseの数字はcsv内の値を示している
Field::Field(GameObject* scene) :GameObject(scene)
{
	hImage = LoadGraph("Assets/bgchar.png");
	assert(hImage > 0);

	Reset();
}

Field::~Field()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
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
	bool ret = csv.Load("Assets/stage1.csv");
	assert(ret);

	width = csv.GetWidth(0);
	height =csv.GetHeight();
	Map = new int[width * height];

	for (int h = 0; h < height; h++)
	{
		if (csv.GetString(0, h) == "")
		{
			height = h;
			break;
		}
		for (int w = 0; w < width; w++)
		{
			Map[h * width + w] = csv.GetInt(w,h);
		}
	}

	for (int h = 0; h < height; h++)
    {
		for (int w = 0; w < width; w++)
		{
			switch (csv.GetInt(w, h + height + 1))
			{
			case 0:
			{
				Player * pPlayer = GetParent()->FindGameObject<Player>();
				pPlayer->SetPosition(w * 32, h * 32);
			}
				break;
			case 1:
			{
				Bird* pBird = Instantiate<Bird>(GetParent());
				pBird->SetPosition(w * 32, h * 32);
			}
		    break;
			}
		}
	}
}	

void Field::Update()
{
	
}

void Field::Draw()
{
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		int scroll = cam->GetValue(); // カメラのスクロール値を取得

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int chip = Map[y * width + x];
				if (chip != 255) // 空のタイルは描画しない
				{
					// スクロール値を適用して背景タイルを描画
					DrawRectGraph((x * 32) - scroll, y * 32, 32 * (chip % 16), 32 * (chip / 16), 32, 32, hImage, TRUE);
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); // 半透明に設定
					DrawBox((x * 32) - scroll, y * 32, (x * 32 + 32) - scroll, y * 32 + 32, GetColor(255, 0, 0), TRUE); // 当たり判定の領域を赤色で描画
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // 透明度を元に戻す
				}
			}
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
