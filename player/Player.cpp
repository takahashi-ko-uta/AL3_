#include "Player.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "affinTransformation.h"
#include <cassert>
#include <random>

void Player::Initalize(Model* model, uint32_t textureHandle) {
	// NULLポインタチェック
	assert(model);

	//引数として受け取ってデータをメンバ変数に記録する
	model_ = model;
	textureHandle_ = textureHandle;
	textureHandle_red = TextureManager::Load("red.png");
	textureHandle_blue = TextureManager::Load("blue.jpg");
	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ワールド変換の初期化
	worldTransforms_.Initialize();
	worldTransforms_.translation_ = Vector3(0.0f, 0.0f, 0.0f);
	worldTransforms_.scale_ = Vector3(2.0f, 1.0f, 1.0f);
}

void Player::Update() {
	Move();   //移動処理
	Rotate(); //旋回処理
	Attack(); //攻撃処理
	//弾更新
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

	//デスフラグが立った弾を排除
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });
}

void Player::Move() {
#pragma region キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	{
		////移動ベクトルの変更する処理
		// if (input_->PushKey(DIK_UP)) {
		//	move.y += 0.5f;
		// } else if (input_->PushKey(DIK_DOWN)) {
		//	move.y -= 0.5f;
		// } else if (input_->PushKey(DIK_LEFT)) {
		//	move.x -= 0.5f;
		// } else if (input_->PushKey(DIK_RIGHT)) {
		//	move.x += 0.5f;
		// }
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
#pragma endregion
}

void Player::Rotate() {
	Vector3 RotY = {0.0f, 0.0f, 0.0f};
	if (input_->PushKey(DIK_U)) {
		RotY.y += 0.01f;
	} else if (input_->PushKey(DIK_I)) {
		RotY.y -= 0.01f;
	}

	worldTransforms_.rotation_ += RotY;
	affinTransformation::Transfer(worldTransforms_);
	//行列更新
	worldTransforms_.TransferMatrix();
}

void Player::Attack() {
	{
		// if (input_->PushKey(DIK_SPACE)) {
		//	//弾の速度
		//	const float kBulletSpeed = 1.0f;
		//	Vector3 velocity(0, 0, kBulletSpeed);
		//	//速度ベクトルを自機の向きに合わせて回転させる
		//	// affinTransformation::VecMat(velocity, worldTransforms_);

		//	velocity.x = (velocity.x * worldTransforms_.matWorld_.m[0][0]) +
		//	             (velocity.y * worldTransforms_.matWorld_.m[1][0]) +
		//	             (velocity.z * worldTransforms_.matWorld_.m[2][0]) +
		//	             (0 * worldTransforms_.matWorld_.m[3][0]);

		//	velocity.y = (velocity.x * worldTransforms_.matWorld_.m[0][1]) +
		//	             (velocity.y * worldTransforms_.matWorld_.m[1][1]) +
		//	             (velocity.z * worldTransforms_.matWorld_.m[2][1]) +
		//	             (0 * worldTransforms_.matWorld_.m[3][1]);

		//	velocity.z = (velocity.x * worldTransforms_.matWorld_.m[0][2]) +
		//	             (velocity.y * worldTransforms_.matWorld_.m[1][2]) +
		//	             (velocity.z * worldTransforms_.matWorld_.m[2][2]) +
		//	             (0 * worldTransforms_.matWorld_.m[3][2]);

		//	//デバック
		//	debugText_->SetPos(50, 70);
		//	debugText_->Printf("velocity:(%f,%f,%f)", velocity.x, velocity.y, velocity.z);

		//	//弾を生成し、初期化
		//	std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		//	newBullet->Initialize(model_, worldTransforms_.translation_, velocity);

		//	//弾を登録する
		//	bullets_.push_back(std::move(newBullet));
		//}
	}

	 if (input_->TriggerKey(DIK_SPACE)) 
	 {
		isTrigger_ = true;
	 }
	 else
	 {
		 isTrigger_ = false;
	 }
}

Vector3 Player::GetWorldPosition() {
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動成分を取得
	worldPos.x = worldTransforms_.translation_.x;
	worldPos.y = worldTransforms_.translation_.y;
	worldPos.z = worldTransforms_.translation_.z;

	return worldPos;
}

void Player::OnCollision() {
	//何もしない
}

void Player::Draw(ViewProjection& viewProjection) {

	//model_->Draw(worldTransforms_, viewProjection, textureHandle_);
	if (isTrigger_ == true) //押したとき
	{
		model_->Draw(worldTransforms_, viewProjection, textureHandle_red);
	}
	else //押していない時
	{
		model_->Draw(worldTransforms_, viewProjection, textureHandle_blue);
	}

	//弾描画
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}