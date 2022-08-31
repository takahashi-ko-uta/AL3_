#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "DebugText.h"

class Skydome 
{
  public:
	void Initialze(Model* model);

	void Update();

	void Draw(ViewProjection& viewProjection);

  private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	DebugText* debugText_ = nullptr;
	Input* input_ = nullptr;
};
