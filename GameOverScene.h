#pragma once
#include "Engine/GameObject.h"

class GameOverScene : public GameObject
{
	int hImage_;
	int padAnalogInput;//xboxの入力を受け取る
	XINPUT_STATE input;//xboxの入力を受け取る
	int keyTimer_; //キーが押されてから遷移までのタイマー
	bool keyPushed_; //キーが押されたか(暗転OKか)のフラグ

	int GameOverBGMHandle;

	//遷移用
	bool isLeft; //true:Retry(left) false:Title(right)
	void DrawScene(); //遷移の文字とか画像とか用
	void ChangeScene(); //シーン遷移実際にするところ
	void CheckRL(); //左右の判定
 
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	GameOverScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};