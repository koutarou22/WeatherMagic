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

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	Instantiate<Field>(this);
	Instantiate<Camera>(this);
	Instantiate<Slime>(this);
	Instantiate<Ghost>(this);
	Instantiate<Hp>(this);
	Instantiate<Player>(this);
	Instantiate<Rock>(this);
	
	
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
