#include "AttackUI.h"
#include"Camera.h"

AttackUI::AttackUI(GameObject* parent)
{
}

AttackUI::~AttackUI()
{
}

void AttackUI::Initialize()
{
	hAttackUI = LoadGraph("Assets/UI/attack.png");
}

void AttackUI::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;

	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr) {
		x -= cam->GetValue();
	}

	DrawGraph(x, y, hAttackUI, TRUE);
}

void AttackUI::Release()
{
	DeleteGraph(hAttackUI);
}
