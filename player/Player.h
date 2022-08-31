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
#include <math.h>
#include <memory>
#include <list>

class Player {
  public:
	void Initalize(Model* model,Model* modelBullet); //, uint32_t textureHandle

	void Update();
	void Move();
	void Rotate();
	void Attack();
	Vector3 GetWorldPosition();
	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();
	//弾リストを取得
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullet() { return bullets_; }

	void Draw(ViewProjection& viewProjection);
	float radius = 3.0f;
  private:
	Model* modelPlayer_ = nullptr;
	Model* modelBullet_ = nullptr;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	WorldTransform worldTransforms_;
	uint32_t textureHandle_ = 0;
	//弾
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	
};