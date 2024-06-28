#pragma once
#include"Engine/GameObject.h"
#include "Player.h"
#include "Magic.h"
/// <summary>
/// ÉJÉÅÉâ
/// </summary>
class Camera : public GameObject
{
public:
	Camera(GameObject* parent):GameObject(parent){ value_ = 0; }
	~Camera() {};
	void GetPlayerPos(Player* _player) { player_ = _player; }
	void GetPlayerPos(Magic* _magic) { magic_ = _magic; }
	void Update();
	void SetValue(int v) { value_ = v; }
	int GetValue() { return value_; }
private:
	Player* player_;
	Magic* magic_;
	int value_;
};

