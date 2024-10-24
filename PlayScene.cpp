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

PlayScene::PlayScene(GameObject* parent) : GameObject(parent, "PlayScene"), MapNumber_(0) 
{
}

void PlayScene::Initialize() 
{
    SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");

    Field* pField = Instantiate<Field>(this);
    pField->Reset(); // Reset()

    Player* pPlayer = nullptr;
    pPlayer = Instantiate<Player>(this);

    int MpPass = pPlayer->GetMp();//Mpの値を持ってくる
    pSceneManager->SetMagicPoint(MpPass);//PlaySceneでPlayerのMpをSet

    Instantiate<Weather>(this);
    Instantiate<Camera>(this);
    Instantiate<Hp>(this);
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
