#include "MoveUI.h"
#include"Camera.h"

MoveUI::MoveUI(GameObject* parent)
	:GameObject(parent, "MoveUI"), hMoveUI(-1)
{
}

MoveUI::~MoveUI()
{
}

void MoveUI::Initialize()
{
	hMoveUI = LoadGraph("Assets/UI/move.png");
}

void MoveUI::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	DrawGraph(x, y, hMoveUI, TRUE);
}

void MoveUI::Release()
{
	DeleteGraph(hMoveUI);
}
