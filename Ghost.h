#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// �e�ۂ��΂��Ă��邨�����N
/// </summary>
class Ghost : public GameObject
{
public:
	Ghost(GameObject* scene);
	~Ghost();
	void Update() override;
	void Draw() override;
	//�~�̓����蔻�������
	void SetPosition(int x, int y);
	bool ColliderCircle(float x, float y, float r);
	bool ColliderRect(float x, float y, float w, float h);
private:
	float sinAngle;
	int hImage_;
	int animeType_;//��
	int animeFrame_;//��
	int PictFlame_;
	int flameCounter_;

	int CoolDownAttack_ = 0;
	int timer_ = 90;
	enum State
	{
		S_WaIk = 0,
		S_Cry,
	};
	State state;

};
