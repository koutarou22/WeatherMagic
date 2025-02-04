#pragma once
#include "Engine/GameObject.h"

/// <summary>
///クリアのシーン
/// </summary>
class ClearScene : public GameObject
{
	int hBack_;

	int hGameClear_;

	int hTitleMenu_;//UIハンドル
	int hTitleMenuYellow_;//黄色UI
	int padAnalogInput_;//xboxの入力を受け取る
	XINPUT_STATE input_;//xboxの入力を受け取る
	int keyTimer_; //キーが押されてから遷移までのタイマー
	bool keyPushed_; //キーが押されたか(暗転OKか)のフラグ

	int ClearBGMHandle_;
	int DecisionHandle_;


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

