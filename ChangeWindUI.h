#pragma once
#include "Engine/GameObject.h"
class ChangeWindUI :
    public GameObject
{
	int hChangeWindUI;
public:
	ChangeWindUI(GameObject* parent);

	~ChangeWindUI();

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

