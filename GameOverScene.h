#pragma once
#include "Engine/GameObject.h"

class GameOverScene : public GameObject
{
	int hBack_;//背景
	int hDecideB_;//決定UI
	int hDecideBYellow_;//決定UI（黄色）
	int padAnalogInput;//xboxの入力を受け取る
	XINPUT_STATE input;//xboxの入力を受け取る
	int keyTimer_; //キーが押されてから遷移までのタイマー
	bool keyPushed_; //キーが押されたか(暗転OKか)のフラグ

	int GameOverBGMHandle_;

	//遷移用
	bool isLeft_; //true:Retry(left) false:Title(right)
	void DrawScene(); //遷移の文字とか画像用
	void ChangeScene(); //シーン遷移実際にするところ
	void CheckRL(); //左右の判定


	bool RightCheck_;//右を何回も押して音が出るのを防ぐ用
	bool LeftCheck_; //左を何回も押して音が出るのを防ぐ用
	int SelectSEHandle_;//選択用SE
	int DecisionHandle_;//決定用SE
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	GameOverScene(GameObject* parent);
	~GameOverScene();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};