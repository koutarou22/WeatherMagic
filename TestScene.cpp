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
	/*Instantiate<Slime>(this, 100, 200);*/
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
