#pragma once
#include "Engine/GameObject.h"
#include<array>
#include<vector>

using std::array;

class ChooseLevelScene :
    public GameObject
{
private:
	int hImage_back;//背景
	int	hLevelFont;//『難易度を選択してください』のフォント
	int hDecideB;   //決定UI

	int padAnalogInput;//xboxの入力を受け取る
	XINPUT_STATE input;//xboxの入力を受け取る

	int keyTimer_; //キーが押されてから遷移までのタイマー
	bool keyPushed_; //キーが押されたか(暗転OKか)のフラグ

	const char* LevelText1 = "";
	const char* LevelText2 = "";
	const char* LevelText3 = "";
	const char* Explanation1 = "";
	const char* Explanation2 = "";
	const char* Explanation3 = "";

	array <const char*, 3> LevelMassage = { LevelText1,LevelText2,LevelText3 };//使わないかも
	array <const char*, 3> ExplanationMassage = { Explanation1,Explanation2,Explanation3 };//使わないかも

	enum StageLevelChoose
	{
		EASY = 0,
		NORMAL = 1,
		HARD = 2,
	};

	StageLevelChoose chooselevel_;
	std::vector<StageLevelChoose> level_arr;
	int currentlevel = 0;//難易度（選択によって読みこむcsvを変える）
	bool prevUp;//↑を押したか
	bool prevDown;//↓を押したか

	int Previous(int level);// 前の要素にアクセス（循環的）
	int Next(int currentIndex);// 次の要素にアクセス（循環的）

	int whitecolor = GetColor(255, 255, 255);
	int yellowcolor = GetColor(255, 255, 0);


	int SelectSEHandle;//選択用SE
	int DecisionHandle;//決定用SE

	bool CheckDecision;//決定が押されたか確認する用

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

	/*void SetLevel(int level) { Level_ = level; }
	int GetLevel() { return Level_; }*/
};

