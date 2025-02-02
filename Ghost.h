#pragma once
#include "Engine/GameObject.h"

class FreezeEffect;
class EnemyMagic;

/// <summary>
/// 弾丸を飛ばしてくるお化けの情報
/// </summary>
class Ghost : public GameObject
{
public:
	Ghost(GameObject* parent);
	~Ghost();
	void Update() override;
	void Draw() override;
	//円の当たり判定をする
	void SetPosition(int x, int y);
	bool ColliderCircle(float x, float y, float r);
	
	void Release() override;
private:
	EnemyMagic* emg;
	float sinAngle;
	int hImage_;
	int animeType_;//状況
	int animeFrame_;//駒
	int PictFlame_;
	int flameCounter_;

	int CoolDownAttack_ = 0;
	int timer_ = 90;
	int enemyHandle;
	enum State//結局使ってない
	{
		S_WaIk = 0,
		S_Cry,
	};
	State state;

	bool FreezeOne;//氷結を一回しか出せないようにする　※重くなったので

	int GhostDamageHandle;//ダメージ音
	int GhostAttackHandle;//攻撃音
	FreezeEffect* pFreeze;
};
