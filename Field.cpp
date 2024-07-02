#include "Field.h"
#include <assert.h>
#include"Player.h"
#include "Bird.h"
#include "Camera.h"
#include "Engine/CsvReader.h"
#include "Slime.h"

//switch����case�̐�����csv���̒l�������Ă���
Field::Field(GameObject* scene) :GameObject(scene)
{
	Map = nullptr;//�܂�������Map��null����Ƃ�
	hImage_ = LoadGraph("Assets/bgchar.png");
	assert(hImage_ > 0);

	hBackGround_ = LoadGraph("Assets/bg4.png");
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
		delete[] Map;//Map�͓��I�z��Ȃ̂�[]������
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
	bool ret = csv.Load("Assets/stage6.csv");
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

	for (int h = 0; h < height; h++) {
		for (int w = 0; w < width; w++) {
			switch (csv.GetInt(w, h/* + height + 1*/))
			{
			case 0:
			{
				Player* pPlayer = GetParent()->FindGameObject<Player>();
				pPlayer->SetPosition(w * 32, h * 32);
			}
			break;
			case 1:
			{
				Bird* pBird = Instantiate<Bird>(GetParent());
				pBird->SetPosition(w * 32, h * 32);
			}
			break;
			case 2:
			{
				Slime* pSlime = Instantiate<Slime>(GetParent());
				pSlime->SetPosition(w * 32, h * 32);
			}
			break;
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

	// ��ʑS�̂ɔw�i�摜��`��
	DrawExtendGraph(0, 0, screenWidth, screenHeight, hBackGround_, FALSE); 
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
	    scroll = cam->GetValue(); // �J�����̃X�N���[���l���擾
	}
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int chip = Map[y * width + x];
		    	DrawRectGraph(x * 32 - scroll, y * 32, 32 * (chip % 16), 32 * (chip / 16), 32, 32, hImage_, TRUE);//0
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
	 case 16://�n��
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