#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// ���i�G�j���݂̎g���ĂȂ�
/// </summary>
class Bird : public GameObject
{
public:
	Bird(GameObject* scene);
	~Bird();
	void Update() override;
	void Draw() override;
	//�~�̓����蔻�������
	void SetPosition(int x, int y);
	bool ColliderCircle(float x, float y, float r);

private:
	float sinAngle;
	int hImage;

};
