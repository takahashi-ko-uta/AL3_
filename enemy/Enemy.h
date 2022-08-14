#pragma once
#include "Audio.h"
#include "DebugCamera.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <math.h>
#include <memory>
#include <list>
#include "EnemyBullet.h"

//行動フェーズ
enum class Phase {
	Approach, //接近する
	Leave,	  //離脱する
};

//自機のクラスの前方宣言
class Player;

class Enemy {
  public:
	void Initalize(Model* model, uint32_t textureHandle);
	void ApproachInitalize();

	void Update();
	void Move();
	void Attack();
	//ワールド座標を取得
	Vector3 GetWorldPosition();

	void Draw(ViewProjection& viewProjection);

	//発射間隔
	static const int kFireInterval = 60;

	
	void SetPlayer(Player* player) { player_ = player; }


   private:
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	WorldTransform worldTransforms_;
	uint32_t textureHandle_ = 0;
	//フェーズ
	Phase phase_ = Phase::Approach;
	//弾
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	//発射タイマー
	int32_t FireTimer = 0;
	//自キャラ
	Player* player_ = nullptr;
};

