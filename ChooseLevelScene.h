#pragma once
#include "Engine/GameObject.h"
#include<array>
#include<vector>

using std::array;

class ChooseLevelScene :
    public GameObject
{
private:
	int hBack_;//背景
	int	hLevelFont_;//『難易度を選択してください』のフォント
	int hDecideB_;   //決定UI
	int hDecideByellow_;//決定UI（黄色）

	int padAnalogInput_;//xboxの入力を受け取る
	XINPUT_STATE input_;//xboxの入力を受け取る

	int keyTimer_; //キーが押されてから遷移までのタイマー
	bool keyPushed_; //キーが押されたか(暗転OKか)のフラグ

	const char* LevelText1_ = "";
	const char* LevelText2_ = "";
	const char* LevelText3_ = "";

	enum StageLevelChoose //各難易度
	{
		EASY = 0,
		NORMAL = 1,
		HARD = 2,
	};
	//StageLevelChoose chooselevel_;
	std::vector<StageLevelChoose> level_arr_;//難易度の配列

	int currentlevel_;//選択中の難易度(SceneManagerに値を渡す他、値によってカーソルの位置が変わる)
	bool prevUp_;//↑を押したか
	bool prevDown_;//↓を押したか

	int Previous(int level);// 前の要素にアクセス（循環的）
	int Next(int currentIndex);// 次の要素にアクセス（循環的）

	int whitecolor_ = GetColor(255, 255, 255);
	int yellowcolor_ = GetColor(255, 255, 0);


	int SelectSEHandle_;//選択用SE
	int DecisionHandle_;//決定用SE

	bool CheckDecision_;//決定が押されたか確認する用

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	ChooseLevelScene(GameObject* parent);
	~ChooseLevelScene();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

