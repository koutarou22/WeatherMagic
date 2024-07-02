#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// プレイヤーが放つ魔法
/// </summary>
class Magic : public GameObject
{
public:
	Magic(GameObject* scene);
	~Magic();
	void Update() override;
	void Draw() override;
	void SetPosition(int x, int y);
	void Setposition(XMFLOAT3 pos);
private:
	int hImage_;
	int timer_;
	
};
