#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// ��̎��ɓG������G�t�F�N�g�N���X
/// </summary>

class FreezeEffect :
    public GameObject
{
    int freezeImage_;
    int frameCounter_; //���t���[�����`�悷�邩
    int eraseCounter_; //�摜�̉��Ԗڂ�\�����Ă��邩
    int animeFrame_; //�摜�̉��Ԗڂ�`�悷�邩

    //�G�t�F�N�g��Ԃ̃X�e�[�g
    enum FreezeState {
        S_Freeze, //�����Ă���
        S_MELT, //�����Ă���
        S_NONE //�����Ȃ�
    };
    FreezeState freezeSt_; //�G�t�F�N�g�̏�Ԃ�\���ϐ�

public:

    FreezeEffect(GameObject* parent);
    ~FreezeEffect();

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    //���ꂼ��̏�Ԃł̍X�V
    void UpdateFreeze();
    void UpdateMelt();

    //�A�N�Z�X�֐�
    void SetPosition(int x, int y);
};

