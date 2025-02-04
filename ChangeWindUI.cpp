#include "ChangeWindUI.h"
#include"Camera.h"

ChangeWindUI::ChangeWindUI(GameObject* parent)
	:GameObject(parent, "ChangeWindUI"), hChangeWindUI(-1)
{
}

ChangeWindUI::~ChangeWindUI()
{
}

void ChangeWindUI::Initialize()
{
	hChangeWindUI = LoadGraph("Assets/UI/ChangeWind.png");
}

void ChangeWindUI::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	DrawGraph(x, y, hChangeWindUI, TRUE);
}

void ChangeWindUI::Release()
{
	DeleteGraph(hChangeWindUI);
}
