#include "TestScene.h"
#include "Hp.h"
#include "Player.h"
#include "Bird.h"
#include "Field.h"
#include "Slime.h"
#include "Camera.h"
#include "Engine/SceneManager.h"
#include "Rock.h"
#include "Ghost.h"
#include "Damage.h"
#include "HealItem.h"
#include "MpItem.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	
	/*Instantiate<Field>(this);*/
	Field* pFailed = Instantiate<Field>(this);
	pFailed->Reset();
	Instantiate<Camera>(this);
	//Instantiate<Slime>(this);
	//Instantiate<Ghost>(this);
	Instantiate<Hp>(this);
	//Instantiate<Damage>(this);
	Instantiate<Player>(this);
	//Instantiate<HealItem>(this);
	//Instantiate<Rock>(this);
	Instantiate<MpItem>(this);
	
	
	//Instantiate<Bird>(this);

	Instantiate<Weather>(this);
}

//�X�V
void TestScene::Update()
{
	
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
