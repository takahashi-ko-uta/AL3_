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
	/// <summary>
	///
	/// </summary>
	void Initalize(Model* model, uint32_t textureHandle);

	/// <summary>
	///
	/// </summary>
	void Update();

	void Move();
	void Rotate();
	void Attack();
	Vector3 GetWorldPosition();
	/// <summary>
	///
	/// </summary>
	void Draw(ViewProjection& viewProjection);

  private:
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	WorldTransform worldTransforms_;
	uint32_t textureHandle_ = 0;
	//’e
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
};