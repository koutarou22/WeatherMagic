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
	void SetPosition(XMFLOAT3 pos);
private:
	int hImage;
	int timer;
};
