#pragma once
#include "Engine/GameObject.h"
class Logo :
    public GameObject
{
private:
	int hImage_;
public:
    Logo(GameObject* parent);
	~Logo();
	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;
	//ŠJ•ú
	void Release() override;
};

