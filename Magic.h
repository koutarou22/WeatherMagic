#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// �v���C���[�������@
/// </summary>
class Magic : public GameObject
{
public:
	Magic(GameObject* scene);
	~Magic();
	void Update() override;
	void Draw() override;
	void SetPosition(int x, int y);
private:
	int hImage_;
	int timer_;
	
};
