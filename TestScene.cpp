#include "TestScene.h"
#include "Engine/SceneManager.h"
#include "Camera.h"
#include "Hp.h"
#include "Player.h"
#include "Bird.h"
#include "Field.h"
#include "Slime.h"
#include "Rock.h"
#include "Ghost.h"
#include "Damage.h"
#include "HealItem.h"
#include "MpItem.h"
#include "ClearFlag.h"
#include"MP.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
    Field* pField = Instantiate<Field>(this);
    pField->Reset(); // Reset() メソッドを呼び出す
    Instantiate<Camera>(this);
    Instantiate<Hp>(this);
    Instantiate<MP>(this);
    Instantiate<Player>(this);
   // Instantiate<MpItem>(this);
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
