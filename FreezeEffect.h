#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// 雪の時に敵が凍るエフェクトクラス
/// </summary>

class FreezeEffect :
    public GameObject
{
    int freezeImage_;
    int frameCounter_; //何フレーム分描画するか
    int eraseCounter_; //画像の何番目を表示しているか
    int animeFrame_; //画像の何番目を描画するか

    //エフェクト状態のステート
    enum FreezeState {
        S_Freeze, //凍っている
        S_MELT, //解けている
        S_NONE //何もなし
    };
    FreezeState freezeSt_; //エフェクトの状態を表す変数

public:

    FreezeEffect(GameObject* parent);
    ~FreezeEffect();

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    //それぞれの状態での更新
    void UpdateFreeze();
    void UpdateMelt();

    //アクセス関数
    void SetPosition(int x, int y);
};

