#pragma once
#include"Engine/GameObject.h"
/// <summary>
/// 敵が打ってくる魔法の情報
/// </summary>
class EnemyMagic:public GameObject
{
public:
	EnemyMagic(GameObject* scene);
	~EnemyMagic();
	void Update() override;
	void Draw() override;
	void SetPosition(int x, int y);
	void SetPosition(XMFLOAT3 pos);
	void SetDirection(VECTOR _direction) { direction_ = _direction; }
	void SetSpeed(float _speed) { speed_ = _speed; }
	bool ColliderCircle(float x, float y, float r);
	void LoadMagicImage();
	void Release() override;

	int GetImageHandle() {	return hImage_;}
	void SetIsDraw(bool d) { isDraw = d; }
	bool GetIsDraw() { return isDraw; }
private:
	int hImage_;
	int timer_;
	VECTOR direction_;//方向
	float speed_;//弾丸の速度
	int animeType_;//状況
	int animeFrame_;//駒
	int PictFlame_;
	int flameCounter_;

	float prevPlPosX; //球を打ち始めた時のプレイヤーのx座標
	bool isDraw; //EnemyMagicを描画するか
};
