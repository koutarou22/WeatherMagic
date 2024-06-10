#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// ƒvƒŒƒCƒ„[‚ª“Š‚°‚éÎ
/// </summary>
class Stone : public GameObject
{
public:
	Stone(GameObject* scene);
	~Stone();
	void Update() override;
	void Draw() override;
	void SetPosition(XMFLOAT3 pos);
private:
	int hImage;
	int timer;
};
