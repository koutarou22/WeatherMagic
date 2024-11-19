#include "PlayScene.h"
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
#include "WeatherBackGround.h"

PlayScene::PlayScene(GameObject* parent) : GameObject(parent, "PlayScene"), MapNumber_(0) 
{
}

void PlayScene::Initialize() 
{
    SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
    MapNumber_ = pSceneManager->GetClearCount();
    Field* pField = Instantiate<Field>(this);
    pField->Reset(MapNumber_);//����������

    Instantiate<Weather>(this);
    Instantiate<WeatherBackGround>(this);
    Player* pPlayer = nullptr;
    pPlayer = Instantiate<Player>(this);

    int MpPass = pPlayer->GetMp();//Mp�̒l�������Ă���
    pSceneManager->SetMagicPoint(MpPass);//PlayScene��Player��Mp��Set

    Instantiate<Camera>(this);
    Instantiate<Hp>(this);
    Instantiate<MP>(this);

    
}

//�X�V
void PlayScene::Update()
{
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}
