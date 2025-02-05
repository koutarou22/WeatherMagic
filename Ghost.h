#pragma once
#include "Engine/GameObject.h"
#include"EnemyMagic.h"

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
	void SetPosition(int x, int y);
	bool ColliderCircle(float x, float y, float r);
	
	void Release() override;
private:
	EnemyMagic* emg;
	FreezeEffect* pFreeze;
	float SinAngle_;
	int hGhost_;
	
	//アニメーション用の変数
	int AnimeType_;//状況
	int AnimeFrame_;//駒
	int PictFlame_;
	int FlameCounter_;

	int EnemyHandle_;

	//球を再度打てるようになるまでのクールタイム格納用変数
	int CoolDownAttack_;

	int GhostDamageHandle;//ダメージ音
	int GhostAttackHandle;//攻撃音

	/// <summary>
	/// 攻撃の情報・処理
	/// </summary>
	void GhostAttack();

	/// <summary>
	/// ゴーストの動きの情報・処理
	/// </summary>
	void GhostMove();

	void HitMagic();

};
