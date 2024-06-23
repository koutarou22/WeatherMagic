#pragma once
#include "global.h"
#include "GameObject.h"

//ÉQÅ[ÉÄÇ…ìoèÍÇ∑ÇÈÉVÅ[Éì
enum SCENE_ID
{
	SCENE_ID_TITLE,
	SCENE_ID_TEST,
	SCENE_ID_GAMEOVER,
	
};

class SceneManager : public GameObject
{
public:
	SceneManager(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void ChangeScene(SCENE_ID next);

private:
	SCENE_ID currentSceneID_;
	SCENE_ID nextSceneID_;
};