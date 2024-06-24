#include "sceneManager.h"

#include"../TitleScene.h"
#include "../TestScene.h"
#include "../GameOverScene.h"


SceneManager::SceneManager(GameObject* parent)
	: GameObject(parent, "SceneManager")
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
}

void SceneManager::Update()
{
	if (currentSceneID_ != nextSceneID_)
	{
		KillAllChildren();

		switch (nextSceneID_)
		{
		case SCENE_ID_TEST: Instantiate<TestScene>(this); break;
		case SCENE_ID_GAMEOVER: Instantiate<GameOverScene>(this); break;
		case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
		}
		currentSceneID_ = nextSceneID_;
	}
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;
}