#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include <math.h>

#include "affinTransformation.h"
#include "player/Player.h"
#include "enemy/Enemy.h"
#include "Skydome.h"

#include <sstream>

#define PI 3.141592

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	GameScene();

	~GameScene();

	void Initialize();
	//テクスチャハンドル
	uint32_t textureHandle_PL_ = 0;// 自機のテクスチャ
	uint32_t textureHandle_EN_ = 0;// 敵のテクスチャ

	//3Dモデル
	Model* model_ = nullptr;
	Model* modelSkydome_ = nullptr;
	Model* modelPlayer_ = nullptr;
	//ワールドトランスフォームビュープロジェクション
	WorldTransform worldTransforms_[100];
	//ビュープロジェクション
	ViewProjection viewProjection_;
	//デバックカメラ
	DebugCamera* debugCamera_ = nullptr;
	//デバックカメラ有効
	//カメラ上方向の角度
	float viewAngle = 0.0f;

	//自キャラ
	Player* player_ = nullptr;
	
	//敵キャラ
	Enemy* enemy_ = nullptr;

	Skydome* skydome_ = nullptr;

	void Update();
	void CheckAllCollisons();
	void AddEnemyBullet(std::unique_ptr<EnemyBullet>enemyBullet);


	void Draw();

	//敵発生データの読み込み
	void LoadEnemyPopData();
	//敵発生コマンドの更新
	void UpdateEnemyPopCommands();


  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	Audio* audio_ = nullptr;
	std::list<std::unique_ptr<EnemyBullet>> enemyBullets_;

	// 敵発生コマンド
	std::stringstream enemyPopCommand;
	int waitFlag = true;
	float waitTimer = 10.0f;
	int flag = 0;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
