#pragma once
#include "Engine/GameObject.h"

class TitleScene : public GameObject
{
private:
	int hImage_;
	int charImage_;
	int spaceImage_;
	int padAnalogInput;//xboxの入力を受け取る
	XINPUT_STATE input;//xboxの入力を受け取る
	int keyTimer_; //キーが押されてから遷移までのタイマー
	bool keyPushed_; //キーが押されたか(暗転OKか)のフラグ
	int mojiTimer_; //文字をぴかぴかするタイマー
	bool mojiend_; //ぴかぴか終わりかなフラグ

	int TitleBGMHandle;	//TitleのBGM

	bool CheckSelect;//決定が押されたか確認する用
	int SelectHandle;//決定を押したときの音

	int hStart;//UIハンドル
	int hStartYellow;//UIハンドル（黄色）
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);
	~TitleScene();
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

};

