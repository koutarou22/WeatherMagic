#pragma once
#include "Engine/GameObject.h"
class ChooseLevelScene :
    public GameObject
{
private:
	int hImage_;
	int Level_;//難易度（選択によって読みこむcsvを変える）
	int padAnalogInput;//xboxの入力を受け取る
	XINPUT_STATE input;//xboxの入力を受け取る

	int keyTimer_; //キーが押されてから遷移までのタイマー
	bool keyPushed_; //キーが押されたか(暗転OKか)のフラグ

	enum StageLevelChoose
	{
		EASY = 0,
		NORMAL,
		HARD
	};
	StageLevelChoose chooselevel_;

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ChooseLevelScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void SetLevel(int level) { Level_ = level; }
	int GetLevel() { return Level_; }
};

