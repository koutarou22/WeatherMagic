#include "TestScene.h"
#include "Hp.h"
#include "Player.h"
#include "Bird.h"
#include "Field.h"
#include "Slime.h"
#include "Camera.h"
#include "Engine/SceneManager.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Instantiate<Field>(this);
	Instantiate<Camera>(this);
	Instantiate<Slime>(this);
	Slime* slime1 = Instantiate<Slime>(this);
	slime1->SetPosition(3000, 0); // 初期座標 (0,0) を指定
	Slime* slime2 = Instantiate<Slime>(this);
	slime2->SetPosition(3400, 200); // 初期座標 (100,200) を指定
	Slime* slime3 = Instantiate<Slime>(this);
	slime3->SetPosition(2300, 0);
	Instantiate<Hp>(this);
	Instantiate<Player>(this);
	
	
	//Instantiate<Bird>(this);

	Instantiate<Weather>(this);
}

//更新
void TestScene::Update()
{
	
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
