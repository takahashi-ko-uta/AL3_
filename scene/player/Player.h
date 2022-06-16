#pragma once
#include "Model.h"
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

class Player {
  public:
	/// <summary>
	///
	/// </summary>
	void Initalize(Model* model,uint32_t textureHandle);

	/// <summary>
	///
	/// </summary>
	void Update();

	/// <summary>
	///
	/// </summary>
	void Draw(ViewProjection& viewProjection);

  public:
	Model *model_ = nullptr;
	Input *input_ = nullptr;
	DebugText* debugText_ = nullptr;
	WorldTransform worldTransforms_;
	uint32_t textureHandle_ = 0;
};
