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
    pField->Reset(MapNumber_);//初期化処理

    Instantiate<Weather>(this);
    Instantiate<WeatherBackGround>(this);
    Player* pPlayer = nullptr;
    pPlayer = Instantiate<Player>(this);

    int MpPass = pPlayer->GetMp();//Mpの値を持ってくる
    pSceneManager->SetMagicPoint(MpPass);//PlaySceneでPlayerのMpをSet

    Instantiate<Camera>(this);
    Instantiate<Hp>(this);
    Instantiate<MP>(this);

    
}

//更新
void PlayScene::Update()
{
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}
