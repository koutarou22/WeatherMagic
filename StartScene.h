#pragma once
#include"Engine/GameObject.h"
class StartScene :
    public GameObject
{
private:
    int hLogo_;    //ゲームのロゴ
	int keyTimer_; //遷移までのタイマー
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	StartScene(GameObject* parent);

	~StartScene();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

