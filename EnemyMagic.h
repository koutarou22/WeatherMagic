#pragma once
#include"Engine/GameObject.h"
/// <summary>
/// �G���ł��Ă��閂�@�̏��
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
	VECTOR direction_;//����
	float speed_;//�e�ۂ̑��x
	int animeType_;//��
	int animeFrame_;//��
	int PictFlame_;
	int flameCounter_;

	float prevPlPosX; //����ł��n�߂����̃v���C���[��x���W
	bool isDraw; //EnemyMagic��`�悷�邩
};
