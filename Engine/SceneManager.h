#pragma once
#include "global.h"
#include "GameObject.h"
#include<string>

enum SCENE_ID
{
	SCENE_ID_TITLE,
	SCENE_ID_LEVEL,
	SCENE_ID_PLAY,
	SCENE_ID_LOAD,
	SCENE_ID_GAMEOVER,
	SCENE_ID_CLEAR
};

//-----------------------------------------------------------
//シーン切り替えを担当するオブジェクト
//-----------------------------------------------------------
class SceneManager : public GameObject
{
public:

	//コンストラクタ
	//引数：parent	親オブジェクト（基本的にゲームマネージャー）
	SceneManager(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	////シーン切り替え（実際に切り替わるのはこの次のフレーム）
	////引数：next	次のシーンのID
	void ChangeScene(SCENE_ID next);


#if 0
#endif
	//--------------ステージクリア→ロード→別のステージに移動するなら使うかもしれない関数------------------
	/// <summary>
	/// クリアした回数を増やす（player.cppでしか使わない）
	/// </summary>
	void ClearCountPlus() { ClearCount_ += 100; }

	/// <summary>
	/// クリアした回数をゲット
	/// </summary>
	/// <returns></returns>
	int GetClearCount() { return ClearCount_; }

	/// <summary>
	/// クリアしたかどうかゲット clearcountが200以上ならクリアはんてい
	/// </summary>
	/// <returns></returns>
	bool GetClear() { return isGameClear_; }
	//--------------ステージクリア→ロード→別のステージに移動するなら使うかもしれない関数------------------
     
	/// <summary>
	/// MPの変数をセット
	/// </summary>
	/// <param name="mp">MP値</param>
	void SetMagicPoint(int mp) { MpReceive_ = mp; }

	/// <summary>
	/// MPの値を取得する
	/// </summary>
	/// <returns></returns>
	int GetMagicPoint()const { return MpReceive_; }

	




private:
	SCENE_ID currentSceneID_;	
	SCENE_ID nextSceneID_;	

	/// <summary>
	/// クリアした回数
	/// </summary>
	int ClearCount_;
	bool isGameClear_;

	int MpReceive_;//取ってきたMPを保存(格納)する変数
};