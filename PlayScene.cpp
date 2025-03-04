#include "PlayScene.h"
#include "Camera.h"
#include "Hp.h"
#include "Player.h"
#include "Field.h"
#include"MP.h"
#include "WeatherBackGround.h"
#include "Score.h"

namespace {
    const int ScorePositionX = 100;
    const int ScorePositionY = 500;
}

PlayScene::PlayScene(GameObject* parent) : GameObject(parent, "PlayScene"), MapNumber_(0),
MpPass_(0),StageBGMHandle_(-1),pSceneManager_(nullptr),pPlayer_(nullptr)
{
    StageBGMHandle_ = LoadSoundMem("Assets/Music/BGM/STAGE_BGM.mp3");
    assert(StageBGMHandle_ != -1);

    PlaySoundMem(StageBGMHandle_, DX_PLAYTYPE_LOOP);
}

PlayScene::~PlayScene()
{
    DeleteSoundMem(StageBGMHandle_);
}

void PlayScene::Initialize() 
{
    pSceneManager_ = (SceneManager*)FindObject("SceneManager");
    MapNumber_ = pSceneManager_->GettLevelManager();
    Field* pField = Instantiate<Field>(this);
    pField->Reset(MapNumber_);//初期化処理

    Instantiate<Hp>(this);
    Instantiate<MP>(this);

    Instantiate<WeatherBackGround>(this);
    Instantiate<Weather>(this);
    pPlayer_ = Instantiate<Player>(this);

    MpPass_ = pPlayer_->GetMp();//Mpの値を持ってくる
    pSceneManager_->SetMagicPoint(MpPass_);//PlaySceneでPlayerのMpをSet

    Instantiate<Camera>(this);
    Score* sc=Instantiate<Score>(this);
    sc->SetPosition(ScorePositionX, ScorePositionY);
    sc->SetPlaying(true);
}

//更新
void PlayScene::Update()
{
    int MpPass = pPlayer_->GetMp();//Mpの値を持ってくる
    pSceneManager_->SetMagicPoint(MpPass);//PlaySceneでPlayerのMpをSet
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}
