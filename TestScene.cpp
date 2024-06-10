#include "TestScene.h"
#include "Player.h"
#include "Bird.h"
#include "Field.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	Instantiate<Field>(this);
	Instantiate<Player>(this);
	Instantiate<Bird>(this);
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
