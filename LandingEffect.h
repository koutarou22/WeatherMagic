#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// ���n�����Ƃ��ɋN���鍻���I�ȃA��
/// </summary>
class LandingEffect : public GameObject {
public:
    LandingEffect(GameObject* parent);
    ~LandingEffect();

    void Update() override;
    void Draw() override;
    void SetPosition(int x, int y);
    /// <summary>
    /// �����Ă����̏���
    /// </summary>
    void Activate();

    /// <summary>
    /// ���񂾂Ƃ��̏���
    /// </summary>
    void Deactivate();

    /// <summary>
    /// �����Ă邩�Ԃ�
    /// </summary>
    /// <returns></returns>
    bool IsActive() const;

private:
    static int hImage_;
    int animeFrame;
    int FrameCounter;
    int eraseCounter;
    bool isActive_; // �A�N�e�B�u��Ԃ��Ǘ�����t���O

    void Release();
};