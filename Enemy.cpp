#include "Enemy.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "affinTransformation.h"
#include <cassert>
#include <random>

void Enemy::Initalize(Model* model, uint32_t textureHandle)
{
	// NULLポインタチェック
	assert(model);

	//引数として受け取ってデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;
	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ワールド変換の初期化
	worldTransforms_.Initialize();
	worldTransforms_.translation_ = Vector3(0.0f, 5.0f, 20.0f);
}

void Enemy::Update() 
{
	Vector3 move = {0, 0, 0};

	switch (phase_) {
	case Phase::Approach:
	default:
		//移動
		move = {0.0f,0.0f,-0.2f};
		//既定の位置に到達したら離脱
		if (worldTransforms_.translation_.z < 0.0f) 
		{
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:
		move = {-0.2f, 0.0f, -0.3f};
		break;
	}
	//座標移動(ベクトル加算)
	worldTransforms_.translation_ += move;
	affinTransformation::Transfer(worldTransforms_);



	//行列更新
	worldTransforms_.TransferMatrix();
}

void Enemy::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransforms_, viewProjection, textureHandle_);
}















