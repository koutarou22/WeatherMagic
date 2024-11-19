#pragma once
#include"Engine/GameObject.h"
class LoadScene : public GameObject
{
	int hImage_;
	int padAnalogInput;//xboxの入力を受け取る
	XINPUT_STATE input;//xboxの入力を受け取る
	int keyTimer_; //キーが押されてから遷移までのタイマー
	bool keyPushed_; //キーが押されたか(暗転OKか)のフラグ
	int mojiTimer_; //文字をぴかぴかするタイマー
	bool mojiend_; //ぴかぴか終わりかなフラグ

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	LoadScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
private:
	bool CheckR;
};

