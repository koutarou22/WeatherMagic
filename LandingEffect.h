#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// 着地したときに起きる砂埃的なアレ
/// </summary>
class LandingEffect : public GameObject {
public:
    LandingEffect(GameObject* parent);
    ~LandingEffect();

    void Update() override;
    void Draw() override;
    void SetPosition(int x, int y);
    /// <summary>
    /// 生きてた時の処理
    /// </summary>
    void Activate();

    /// <summary>
    /// 死んだときの処理
    /// </summary>
    void Deactivate();

    /// <summary>
    /// 生きてるか返す
    /// </summary>
    /// <returns></returns>
    bool IsActive() const;

private:
    static int hImage_;
    int animeFrame;
    int FrameCounter;
    int eraseCounter;
    bool isActive_; // アクティブ状態を管理するフラグ

    void Release();
};