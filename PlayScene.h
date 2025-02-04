#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h";
#include"ChooseLevelScene.h"

class SceneManager;
class Player;

//テストシーンを管理するクラス
class PlayScene : public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayScene(GameObject* parent);
	~PlayScene();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
private:
	int MapNumber_;//どのcsvを読み込むか
	int MpPass; //Mpの値
	int StageBGMHandle; //BGM
	SceneManager* pSceneManager;
	Player* pPlayer;
};