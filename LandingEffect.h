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
    void SetIsDraw(bool _IsDraw) { isDraw_ = _IsDraw; }
    bool GetIsDraw() { return isDraw_; }


private:
    int hImage_;
    int animeFrame;
    int FrameCounter;
    int eraseCounter;
    bool isDraw_;

    void Release();
};