#include "JumpUI.h"
#include"Camera.h"

JumpUI::JumpUI(GameObject* parent)
{
}

JumpUI::~JumpUI()
{
}

void JumpUI::Initialize()
{
	hJumpUI = LoadGraph("Assets/UI/jump.png");
}

void JumpUI::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	DrawGraph(x, y, hJumpUI, TRUE);
}

void JumpUI::Release()
{
	DeleteGraph(hJumpUI);
}
