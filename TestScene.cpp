#include "TestScene.h"
#include "Player.h"
#include "Bird.h"
#include "Field.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Instantiate<Field>(this);
	Instantiate<Player>(this);
	Instantiate<Bird>(this);
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
