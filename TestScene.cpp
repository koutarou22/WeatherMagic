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

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
    Field* pField = Instantiate<Field>(this);
    pField->Reset(); // Reset() ���\�b�h���Ăяo��
    Instantiate<Camera>(this);
    Instantiate<Hp>(this);
    Instantiate<MP>(this);
    Instantiate<Player>(this);
   // Instantiate<MpItem>(this);
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
