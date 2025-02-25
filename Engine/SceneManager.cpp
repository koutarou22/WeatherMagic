#include "sceneManager.h"
#include"../TitleScene.h"
#include "../PlayScene.h"
#include "../GameOverScene.h"
#include "../ClearScene.h"
#include"../ChooseLevelScene.h"
#include"../StartScene.h"

SceneManager::SceneManager(GameObject* parent)
	: GameObject(parent, "SceneManager")
{
}

void SceneManager::Initialize()
{
	/*currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);*/

	currentSceneID_ = SCENE_ID_START;
	nextSceneID_ = currentSceneID_;
	Instantiate<StartScene>(this);
}

void SceneManager::Update()
{
	if (currentSceneID_ != nextSceneID_)
	{
		KillAllChildren();
		InitGraph();
		
		switch (nextSceneID_)
		{
        case SCENE_ID_START: Instantiate<StartScene>(this); break;
		case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
		case SCENE_ID_LEVEL: Instantiate<ChooseLevelScene>(this); break;
		case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
		case SCENE_ID_GAMEOVER: Instantiate<GameOverScene>(this); break;
		case SCENE_ID_CLEAR: Instantiate<ClearScene>(this); break;
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