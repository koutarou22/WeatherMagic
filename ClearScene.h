#pragma once
#include "Engine/GameObject.h"

/// <summary>
///クリアのシーン
/// </summary>
class ClearScene : public GameObject
{
	int hImage_;

	int hGameClear_;

	int hTitleMenu;//UIハンドル
	int padAnalogInput;//xboxの入力を受け取る
	XINPUT_STATE input;//xboxの入力を受け取る
	int keyTimer_; //キーが押されてから遷移までのタイマー
	bool keyPushed_; //キーが押されたか(暗転OKか)のフラグ

	int ClearBGMHandle;
	int DecisionHandle;


public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ClearScene(GameObject* parent);
	~ClearScene();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

