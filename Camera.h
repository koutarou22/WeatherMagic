#pragma once
#include"Engine/GameObject.h"
/// <summary>
/// 横スクロールの情報
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

