#pragma once
#include "Engine/GameObject.h"
class UI : public GameObject
{
private:
	int hAttB;
	int hChaPad;
	int hJumpA;
	int hExplanLRB;
	int hStkL;
	int hStkR;
public:
	UI(GameObject* parent);
	~UI();
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

};

