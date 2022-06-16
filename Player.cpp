#include"player/Player.h"
#include "TextureManager.h"
#include <cassert>
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include <random>
#include "affinTransformation.h"


void Player::Initalize(Model* model, uint32_t textureHandle) 
{
	//NULLポインタチェック
	assert(model);

	//引数として受け取ってデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;
	//シングルトンインスタンスを取得する
	input_= Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ワールド変換の初期化
	worldTransforms_.Initialize();
}

void Player::Update() 
{
#pragma region キャラクターの移動ベクトル
	Vector3 move = {0,0,0};
	//移動ベクトルの変更する処理
	if (input_->PushKey(DIK_UP))
	{
		move.y += 0.5f; 
	} 
	else if(input_->PushKey(DIK_DOWN)) 
	{
		move.y -= 0.5f;
	} 
	else if (input_->PushKey(DIK_LEFT)) 
	{
		move.x -= 0.5f;
	}
	else if (input_->PushKey(DIK_RIGHT))
	{
		move.x += 0.5f;
	}

	//座標移動(ベクトル加算)
	worldTransforms_.translation_ += move;
	affinTransformation::Transfer(worldTransforms_);

#pragma region 移動制限
	//移動限界座標
	const float kMoveLimitX = 35.0f;
	const float kMoveLimitY = 20.0f;

	//範囲を超えない処理
	worldTransforms_.translation_.x = max(worldTransforms_.translation_.x, -kMoveLimitX);
	worldTransforms_.translation_.x = min(worldTransforms_.translation_.x, +kMoveLimitX);
	worldTransforms_.translation_.y = max(worldTransforms_.translation_.y, -kMoveLimitY);
	worldTransforms_.translation_.y = min(worldTransforms_.translation_.y, +kMoveLimitY);

#pragma endregion

	//行列更新
	worldTransforms_.TransferMatrix();

	debugText_->SetPos(50, 50);
	debugText_->Printf(
	  " worldTransforms_.translation_:(%f,%f,%f)", worldTransforms_.translation_.x,
	  worldTransforms_.translation_.y, worldTransforms_.translation_.z);
#pragma endregion


}

void Player::Draw(ViewProjection& viewProjection) 
{ 
	model_->Draw(worldTransforms_, viewProjection, textureHandle_);
}





