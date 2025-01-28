#include "ChangeRainUI.h"
#include"Camera.h"

ChangeRainUI::ChangeRainUI(GameObject* parent)
{
}

ChangeRainUI::~ChangeRainUI()
{
}

void ChangeRainUI::Initialize()
{
	hChangeRainUI = LoadGraph("Assets/UI/ChangeRain.png");
}

void ChangeRainUI::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	DrawGraph(x, y, hChangeRainUI, TRUE);
}

void ChangeRainUI::Release()
{
	DeleteGraph(hChangeRainUI);
}
