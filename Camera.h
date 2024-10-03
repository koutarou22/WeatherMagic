#pragma once
#include"Engine/GameObject.h"
/// <summary>
/// ���X�N���[���̏��
/// </summary>
class Camera : public GameObject
{
public:
	Camera(GameObject* parent) :GameObject(parent) { value = 0; }
	~Camera() {}
	void SetValue(int v) { value = v; }
	int GetValue() { return value; }
private:
	int value;
};

