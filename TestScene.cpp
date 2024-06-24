#include "TestScene.h"
#include "Hp.h"
#include "Player.h"
#include "Bird.h"
#include "Field.h"
#include "Slime.h"
#include "Camera.h"
#include "Engine/SceneManager.h"

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
	Slime* slime1 = Instantiate<Slime>(this);
	slime1->SetPosition(3000, 0); // �������W (0,0) ���w��
	Slime* slime2 = Instantiate<Slime>(this);
	slime2->SetPosition(3400, 200); // �������W (100,200) ���w��
	Slime* slime3 = Instantiate<Slime>(this);
	slime3->SetPosition(2300, 0);
	Instantiate<Hp>(this);
	Instantiate<Player>(this);
	
	
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
