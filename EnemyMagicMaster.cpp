#include "EnemyMagicMaster.h"

EnemyMagicMaster::EnemyMagicMaster(GameObject* parent)
	:GameObject(parent,"EnemyMagicMaster")
{

	const char* name = "Assets/Chara/EnemyMagic_F.png";
	hImage_1 = LoadGraph(name);
	assert(hImage_1 > 0);
	hImage_2 = LoadGraph(name);
	assert(hImage_2 > 0);
	hImage_3 = LoadGraph(name);
	assert(hImage_3 > 0);
	hImage_4 = LoadGraph(name);
	assert(hImage_4 > 0);
	hImage_5 = LoadGraph(name);
	assert(hImage_5 > 0);

	Magic_.push_back(hImage_1);
	Magic_.push_back(hImage_2); 
	Magic_.push_back(hImage_3); 
	Magic_.push_back(hImage_4); 
	Magic_.push_back(hImage_5);
	
	//MagicArray_ = { hImage_1,hImage_2,hImage_3,hImage_4,hImage_5 };

}

EnemyMagicMaster::~EnemyMagicMaster()
{
}

void EnemyMagicMaster::Update()
{
}

void EnemyMagicMaster::Draw()
{
}

void EnemyMagicMaster::Release()
{
}
<<<<<<< HEAD
=======

int EnemyMagicMaster::GetEnemyMagic()
{
	return hImage_1;
}
>>>>>>> master
