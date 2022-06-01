#include "Player.h"
#include "TextureManager.h"
#include <cassert>
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"
#include <random>

void Player::InitiaLize(Model* model, uint32_t textreHandle) {
	//NULLポインタチェック
	assert(model);

	//引数として受け取ってデータをメンバ変数に記憶する
	model_ = model;
	textureHandle_ = textreHandle;
	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	worldTransform_.Initialize();
}

void Player::Update() 
{ 
#pragma region プレイヤーの移動
	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	//キャラクター移動速度
	const float playerSpeed = 0.2;
	
	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_LEFT)) {
		move = {-playerSpeed, 0, 0};
	} 
	else if (input_->PushKey(DIK_RIGHT)) {
		move = {playerSpeed, 0, 0};
	} 
	else if (input_->PushKey(DIK_UP)) {
		move = {0, -playerSpeed, 0};
	} 
	else if (input_->PushKey(DIK_DOWN)) {
		move = {0, playerSpeed, 0};
	}
	//注視点移動(ベクトル加算)
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	worldTransform_.TransferMatrix();

	debugText_->SetPos(50, 150);
	debugText_->Printf(
	  "Root:(%f,%f,%f)",
		worldTransform_.translation_.x,
		worldTransform_.translation_.y,
	    worldTransform_.translation_.z);

#pragma endregion
}

void Player::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}
