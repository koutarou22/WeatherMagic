#include "ChangeSnowUI.h"
#include"Camera.h"

ChangeSnowUI::ChangeSnowUI(GameObject* parent)
{
}

ChangeSnowUI::~ChangeSnowUI()
{
}

void ChangeSnowUI::Initialize()
{
	hChangeSnowUI = LoadGraph("Assets/UI/ChangeSnow.png");
}

void ChangeSnowUI::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	DrawGraph(x, y, hChangeSnowUI, TRUE);
}

void ChangeSnowUI::Release()
{
	DeleteGraph(hChangeSnowUI);
}
