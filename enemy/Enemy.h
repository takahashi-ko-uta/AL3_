#pragma once
#include "Audio.h"
#include "DebugCamera.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "EnemyBullet.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "Vector3Math.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <list>
#include <math.h>
#include <memory>

//行動フェーズ
enum class Phase {
	Approach, //接近する
	Leave,    //離脱する
};

//自機のクラスの前方宣言
class Player;

class NotesHit;

class Enemy {
  public:
	void Initalize(Model* model, uint32_t textureHandle);
	void ApproachInitalize();

	void Update();
	void Move();

	void SetPlayer(Player* player) { player_ = player; }
	void SetNotesHit(NotesHit* notesHit) { notesHit_ = notesHit; }
	void Attack();
	//ワールド座標を取得
	Vector3 GetWorldPosition();
	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();
	//弾リストを取得
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullet() { return bullets_; }
	void Draw(ViewProjection& viewProjection);
	bool IsDead() const { return isDead_; }
	//発射間隔
	static const int kFireInterval = 60;

	

	float radius = 3.0f;

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
	NotesHit* notesHit_ = nullptr;

	//デスフラグ
	bool isDead_ = false;
};
