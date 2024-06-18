#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// íπÅiìGÅj
/// </summary>
class Bird : public GameObject
{
public:
	Bird(GameObject* scene);
	~Bird();
	void Update() override;
	void Draw() override;
	void SetPosition(int x, int y);
private:
	int hImage;
};
