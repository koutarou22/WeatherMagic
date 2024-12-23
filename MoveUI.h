#pragma once
#include "Engine/GameObject.h"
class MoveUI :
    public GameObject
{
private:
	int hMoveUI;
public:
    MoveUI(GameObject* parent);

    ~MoveUI();

    //‰Šú‰»
	void Initialize() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;

	void SetPosition(int x, int y)
	{
		transform_.position_.x = x;
		transform_.position_.y = y+4;//”÷’²®
	}

};

