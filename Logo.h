#pragma once
#include "Engine/GameObject.h"
class Logo :
    public GameObject
{
private:
	int hImage_;
public:
    Logo(GameObject* parent);
	~Logo();
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;
	//開放
	void Release() override;
};

