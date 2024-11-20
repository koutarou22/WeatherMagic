#include "PlayScene.h"
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
#include "Score.h"

PlayScene::PlayScene(GameObject* parent) : GameObject(parent, "PlayScene"), MapNumber_(0) 
{
}

void PlayScene::Initialize() 
{
    pSceneManager = (SceneManager*)FindObject("SceneManager");
    MapNumber_ = pSceneManager->GetClearCount();
    Field* pField = Instantiate<Field>(this);
    pField->Reset(MapNumber_);//����������

    Instantiate<Weather>(this);
    Instantiate<WeatherBackGround>(this);
    pPlayer = nullptr;
    pPlayer = Instantiate<Player>(this);

    MpPass = pPlayer->GetMp();//Mp�̒l�������Ă���
    pSceneManager->SetMagicPoint(MpPass);//PlayScene��Player��Mp��Set

    Instantiate<Camera>(this);
    Instantiate<Hp>(this);
    Instantiate<MP>(this);

    Score* sc=Instantiate<Score>(this);
    sc->SetPosition(100,500);
    bool b = true;
    sc->SetPlaying(b);
}

//�X�V
void PlayScene::Update()
{
    int MpPass = pPlayer->GetMp();//Mp�̒l�������Ă���
    pSceneManager->SetMagicPoint(MpPass);//PlayScene��Player��Mp��Set
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}
