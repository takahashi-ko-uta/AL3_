#pragma once
#include "Model.h"
#include "WorldTransform.h"

class EnemyBullet {
  public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();
	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();
	void NotCollision();
	Vector3 GetWorldPosition();

	int GetTrigger() const { return isTrigger_; }
	void Draw(const ViewProjection& viewProjection);

	bool IsDead() const { return isDead_; }
	float radius = 3.0f;

  private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0;
	uint32_t textureHandle_red = 0;
	uint32_t textureHandle_blue = 0;
	//速度
	Vector3 velocity_;
	//寿命
	static const int32_t kLifeTime = 60 * 5;
	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;
	bool isTrigger_ = false;
};