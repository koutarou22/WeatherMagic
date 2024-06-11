#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// ƒXƒ‰ƒCƒ€
/// </summary>
class Slime : public GameObject
{
public:
	Slime(GameObject* scene);
	~Slime();
	void Update() override;
	void Draw() override;
private:
	int hImage;
};

