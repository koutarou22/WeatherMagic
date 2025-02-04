#pragma once
#include "Engine/GameObject.h"

class TitleScene : public GameObject
{
private:
	int hBack_;//タイトルの背景
	int hTitle_;//『WeatherMagic』のタイトルフォント
	int padAnalogInput_;//xboxの入力を受け取る
	XINPUT_STATE input_;//xboxの入力を受け取る
	int keyTimer_; //キーが押されてから遷移までのタイマー
	bool keyPushed_; //キーが押されたか(暗転OKか)のフラグ
	int mojiTimer_; //文字を光らせるタイマー
	bool mojiend_; //文字の光らせる処理が終わったか

	int TitleBGMHandle_;	//TitleのBGM

	bool CheckSelect_;//決定が押されたか確認する用
	int SelectSEHandle_;//決定を押したときの音

	int hStart_;//UIハンドル
	int hStartYellow_;//UIハンドル（黄色）
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

