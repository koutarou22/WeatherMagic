#include "ChangeSunUI.h"
#include"Camera.h"

ChangeSunUI::ChangeSunUI(GameObject* parent)
	:GameObject(parent, "ChangeSunUI"), hChangeSunUI(-1)
{
}

ChangeSunUI::~ChangeSunUI()
{
}

void ChangeSunUI::Initialize()
{
	hChangeSunUI = LoadGraph("Assets/UI/ChangeSun.png");
}

void ChangeSunUI::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	DrawGraph(x, y, hChangeSunUI, TRUE);
}

void ChangeSunUI::Release()
{
	DeleteGraph(hChangeSunUI);
}
