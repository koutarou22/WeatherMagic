#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// ���n�����Ƃ��̍��o�G�t�F�N�g���Ǘ�����N���X
/// </summary>

class LandingEffect : public GameObject 
{
    int dustImage_;
    int frameCounter_; //���t���[�����`�悷�邩
    int eraseCounter_; //�摜�̉��Ԗڂ�\�����Ă��邩
    int animeFrame_; //�摜�̉��Ԗڂ�`�悷�邩
    bool isDraw_; //�`�悵�Ă悢��

public:
    LandingEffect(GameObject* parent);
    ~LandingEffect();

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    //�A�N�Z�X�֐�
    void SetPosition(int x, int y);
    void SetIsDraw(bool _IsDraw) { isDraw_ = _IsDraw; }
    bool GetIsDraw() { return isDraw_; }



};