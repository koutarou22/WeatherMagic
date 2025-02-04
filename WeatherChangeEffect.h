#pragma once
#include "Engine/GameObject.h"

class WeatherChangeEffect :
    public GameObject
{
private:
    int effImage_;
	int frameCounter_; //���t���[�����`�悷�邩
	int eraseCounter_; //�摜�̉��Ԗڂ�\�����Ă��邩
	int animeFrame_; //�摜�̉��Ԗڂ�`�悷�邩
	bool isDraw_; //�`��E�X�V���Ă悢��

public:
	WeatherChangeEffect(GameObject* parent);
	~WeatherChangeEffect();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
	void Init(); //������ԂɃZ�b�g����
	//�A�N�Z�X�֐�
	void SetIsDraw(bool _IsDraw) { isDraw_ = _IsDraw; }
	bool GetIsDraw() { return isDraw_; }
};

