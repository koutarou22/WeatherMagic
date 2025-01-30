#pragma once
#include "Engine/GameObject.h"
#include<vector>
#include<array>
class EnemyMagicMaster :public GameObject
{
public:
	EnemyMagicMaster(GameObject* parent);
	~EnemyMagicMaster();
	void Update() override;
	void Draw() override;
	void Release() override;
	int GetEnemyMagic();
private:
	int hImage_1;
	int hImage_2;
	int hImage_3;
	int hImage_4;
	int hImage_5;
	std::array<int,5> MagicArray_;
	std::vector<int> Magic_;
};

