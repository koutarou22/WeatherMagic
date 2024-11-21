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

	int padAnalogInput;//xboxの入力を受け取る
	XINPUT_STATE input;//xboxの入力を受け取る

	int keyTimer_; //キーが押されてから遷移までのタイマー
	bool keyPushed_; //キーが押されたか(暗転OKか)のフラグ

	const char* LevelText1 = "";
	const char* LevelText2 = "";
	const char* LevelText3 = "";
	array <const char*, 3> ResultMassage = { LevelText1,LevelText2,LevelText3 };
	

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

	/*void SetLevel(int level) { Level_ = level; }
	int GetLevel() { return Level_; }*/
};

