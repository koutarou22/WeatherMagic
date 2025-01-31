#pragma once
#include "Engine/GameObject.h"
class ChangeSnowUI :
    public GameObject
{
	int hChangeSnowUI;
public:
	ChangeSnowUI(GameObject* parent);

	~ChangeSnowUI();

	//‰Šú‰»
	void Initialize() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;

	void SetPosition(int x, int y)
	{
		transform_.position_.x = x - 100;
		transform_.position_.y = y + 4;//”÷’²®
	}
};

