#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// 着地したときの砂塵エフェクトを管理するクラス
/// </summary>

class LandingEffect : public GameObject 
{
    int dustImage_;
    int frameCounter_; //何フレーム分描画するか
    int eraseCounter_; //画像の何番目を表示しているか
    int animeFrame_; //画像の何番目を描画するか
    bool isDraw_; //描画してよいか

public:
    LandingEffect(GameObject* parent);
    ~LandingEffect();

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    //アクセス関数
    void SetPosition(int x, int y);
    void SetIsDraw(bool _IsDraw) { isDraw_ = _IsDraw; }
    bool GetIsDraw() { return isDraw_; }



};