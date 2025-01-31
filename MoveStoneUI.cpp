#include "MoveStoneUI.h"
#include"Camera.h"

MoveStoneUI::MoveStoneUI(GameObject* parent)
{
}

MoveStoneUI::~MoveStoneUI()
{
}

void MoveStoneUI::Initialize()
{
	hMoveStoneUI=LoadGraph("Assets/UI/MoveStone.png");
}

void MoveStoneUI::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	DrawGraph(x, y, hMoveStoneUI, TRUE);
}

void MoveStoneUI::Release()
{
	DeleteGraph(hMoveStoneUI);
}
