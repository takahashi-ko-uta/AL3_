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




class Enemy {
  public:
	void Initalize(Model* model, uint32_t textureHandle);

	/// <summary>
	///
	/// </summary>
	void Update();

	void Draw(ViewProjection& viewProjection);

   private:
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	WorldTransform worldTransforms_;
	uint32_t textureHandle_ = 0;
};

//Enemy::Enemy() {}
//
//Enemy::~Enemy() {}
