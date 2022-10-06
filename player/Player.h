#pragma once
#include "Audio.h"
#include "DebugCamera.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <list>
#include <math.h>
#include <memory>


class EnemyBullet;

class Player {
  public:
	void Initalize(Model* model, uint32_t textureHandle);

	void Update();
	void Move();
	void Rotate();
	void Attack();
	Vector3 GetWorldPosition();
	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();
	bool GetTrigger() const { return isTrigger_; } 
	
	//弾リストを取得
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullet() { return bullets_; }

	void Draw(ViewProjection& viewProjection);
	float radius = 6.0f; //元は3.0f
  private:
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	WorldTransform worldTransforms_;
	uint32_t textureHandle_ = 0;
	uint32_t textureHandle_red = 0;
	uint32_t textureHandle_blue = 0;
	//弾
	std::list<std::unique_ptr<PlayerBullet>> bullets_;

	bool isTrigger_ = false; 

};