#pragma once
#include "Engine/GameObject.h"
/// <summary>
/// MpÌlð]¿µÂ»µÄ\¦·é(¢À)
/// </summary>
class Score : public GameObject
{
private:
	int hImage_;

	int NumStars = 0;
	//int animeType_;//óµ
	//int animeFrame_;//î
	//int PictFlame_;
	//int flameCounter_;
public:

	Score(GameObject* parent);
	~Score();
	//ú»
	void Initialize() override;

	//XV
	void Update() override;

	//`æ
	void Draw() override;
	//Jú
	void Release() override;
	void SetPosition(int x, int y);
	void SetPosition(XMFLOAT3 pos);
};

