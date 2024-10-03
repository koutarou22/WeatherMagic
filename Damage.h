#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// スライムが攻撃をくらった時の表示
/// ※ただその時だけ画像が出るだけなので処理は単純
/// </summary>
class Damage :public GameObject
{
private:
	int hImage_;
	int Timer_ = 90;
	int animeFrame_;
	int flameCounter_;
public:

	Damage(GameObject* parent);
	~Damage();
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;
	//開放
	void Release() override;
	void SetPosition(int x, int y);
	void SetPosition(XMFLOAT3 pos);

};

