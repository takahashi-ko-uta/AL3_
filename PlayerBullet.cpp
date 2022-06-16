#include "PlayerBullet.h"
#include "TextureManager.h"
#include <cassert>
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include <random>
#include "affinTransformation.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position) 
{
	// NULLポインタチェック
	assert(model);

	//引数として受け取ってデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = TextureManager::Load("black.jpg");

	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
}

void PlayerBullet::Update()
{ 
	affinTransformation::Transfer(worldTransform_);
	worldTransform_.TransferMatrix();
	//affinTransformation::Par(worldTransform_, 0, 1); 
}


void PlayerBullet::Draw(const ViewProjection& viewProjection) 
{ 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}



