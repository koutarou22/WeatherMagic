#include "Camera.h"

namespace
{
    const int RIGHT_MOVE_CAMERA = 1200; // �E�ɓ���̈ʒu�ɒ������瓮��
    //const int LEFT_MOVE_CAMERA = -600; // ���ɓ���̈ʒu�ɒ������瓮��
}

void Camera::Update()
{
    if (player_)
    {
        float PCamera = player_->GetPosition().x;

        if (PCamera > RIGHT_MOVE_CAMERA / 2) {
            value_ = PCamera - RIGHT_MOVE_CAMERA / 2;
        }
       
    /*    else if (PCamera < LEFT_MOVE_CAMERA / 2) {
            value_ = PCamera - LEFT_MOVE_CAMERA / 2;
        }*/
    }
}
