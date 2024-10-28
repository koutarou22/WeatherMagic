//#include "DxLib.h"
//#include "LoadScene.h"
//#include "PlayScene.h"
//#include "Engine/SceneManager.h"
//#include "Field.h"
//#include "ResultScore.h"
//#include "Player.h"
//
//const char* Load_TEXT = "Load Now";
//
//LoadScene::LoadScene(GameObject* parent)
//    : GameObject(parent, "LoadScene")
//{
//}
//
//void LoadScene::Initialize()
//{
//}
//
//void LoadScene::Update()
//{
//    SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
//	Instantiate<Player>(this);
//	Instantiate<ResultScore>(this);
//    if (CheckHitKey(KEY_INPUT_R))
//    {
//        pSceneManager->ChangeScene(SCENE_ID_PLAY);
//    }
//}
//
//
//void LoadScene::Draw()
//{
//	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
//
//	switch (pSceneManager->GetClearCount())
//	{
//	case 100:
//
//		DrawString(0, 0, "現在ロード画面にいます", GetColor(255, 255, 255));
//		DrawString(0, 50, "Rキーで次のステージへ", GetColor(255, 255, 255));
//
//		DrawString(0, 100, "Stage2", GetColor(255, 255, 255));
//		DrawString(0, 120, "名無し", GetColor(255, 255, 255));
//		break;
//	case 200:
//		DrawString(0, 100, "Stage3 Final Stage", GetColor(255, 255, 255));
//		DrawString(0, 120, "不気味な森林", GetColor(255, 255, 255));
//		break;
//	default:
//		break;
//	}
//}
//
//void LoadScene::Release()
//{
//}
