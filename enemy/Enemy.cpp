#include "enemy/Enemy.h"
#include "player/Player.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "affinTransformation.h"
#include <cassert>
#include <random>

void Enemy::Initalize(Model* modelEnemy, Model* modelENbullet) 
{
	// NULLポインタチェック
	assert(modelEnemy);
	assert(modelENbullet);
	//引数として受け取ってデータをメンバ変数に記録する
	model_ = modelEnemy;
	modelEnemy_ = modelEnemy;
	modelENbullet_ = modelENbullet;
	//textureHandle_ = textureHandle;
	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//接近フェーズの初期化
	ApproachInitalize();

	//ワールド変換の初期化
	worldTransforms_.Initialize();
	worldTransforms_.translation_ = Vector3(0.0f, 5.0f, 20.0f);
}

void Enemy::ApproachInitalize() 
{
	//発射タイマー初期化
	FireTimer = kFireInterval;
}

void Enemy::Update() 
{ 
	Move();
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}

	//デスフラグが立った弾を排除
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) { return bullet->IsDead(); });
}

void Enemy::Move() 
{
	Vector3 move = {0, 0, 0};
	
	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌ・ツイスターの乱数エンジン
	std::mt19937_64 engine(seed_gen());
	//乱数範囲の指定
	std::uniform_real_distribution<float> dist(0, 3); // dist(最大値,最小値)

	

	switch (phase_) {
	case Phase::Approach:
	default:
#pragma region 攻撃
		//発射タイマーカウントダウン
		FireTimer -= 1;
		//指定時間に達した
		if (FireTimer <= 0) 
		{
			//弾を発射
			Attack();
			//タイマーを戻す
			FireTimer = kFireInterval;
		}
#pragma endregion

#pragma region 移動
		
		switch (movePattern) {
		case 0: //左上
			if (worldTransforms_.translation_.x > -25.0f) {
				worldTransforms_.translation_.x -= 0.1f;
				if (worldTransforms_.translation_.y < 15) {
					worldTransforms_.translation_.y += 0.05f;
				}
			} else {
				phase_ = Phase::Leave;
			}
			break;
		case 1: //右上
			if (worldTransforms_.translation_.x < 25.0f) {
				worldTransforms_.translation_.x += 0.1f;
				if (worldTransforms_.translation_.y < 15) {
					worldTransforms_.translation_.y += 0.05f;
				}
			} else {
				phase_ = Phase::Leave;
			}

			break;
		case 2: //右下
			if (worldTransforms_.translation_.x < 25.0f) {
				worldTransforms_.translation_.x += 0.1f;
				if (worldTransforms_.translation_.y > -15) {
					worldTransforms_.translation_.y -= 0.05f;
				}
			} else {
				phase_ = Phase::Leave;
			}
			break;
		case 3: //左下
			if (worldTransforms_.translation_.x > -25.0f) {
				worldTransforms_.translation_.x -= 0.1f;
				if (worldTransforms_.translation_.y > -15) {
					worldTransforms_.translation_.y -= 0.05f;
				}
			} else {
				phase_ = Phase::Leave;
			}
			break;
		}



#pragma endregion
		

		////既定の位置に到達したら離脱
		//if (worldTransforms_.translation_.z < 0.0f) {
		//	phase_ = Phase::Leave;
		//}
		break;
	case Phase::Leave:
	   movePattern =  dist(engine);
	   phase_ = Phase::Approach;
		break;
	}
	//座標移動(ベクトル加算)
	//worldTransforms_.translation_ += move;
	worldTransforms_.translation_.z =20; 
	affinTransformation::Transfer(worldTransforms_);
	//行列更新
	worldTransforms_.TransferMatrix();
}

void Enemy::Attack() {
	assert(player_);

	//弾の速度
	const float kBulletSpeed = 0.5 * 0.1f;//バグで速いため0.1をかけている(要修正)--------------------------------

	//Vector3 velocity(0, 0, kBulletSpeed);
	Vector3 PLvec = player_->GetWorldPosition();//自キャラのワールド座標を取得
	Vector3 ENvec = GetWorldPosition();			//敵キャラのワールド座標を取得
	Vector3 SPvec = Vector3Math::diff(PLvec, ENvec); //敵キャラ→自キャラの差分ベクトルを求める
	SPvec = Vector3Math::Normalize(SPvec);				//ベクトルの正規化
	Vector3 velocity(
		SPvec.x * kBulletSpeed,
		SPvec.y * kBulletSpeed,
		SPvec.z * kBulletSpeed); //ベクトルの長さを、速さに合わせる

	//速度ベクトルを自機の向きに合わせて回転させる
	velocity.x = (velocity.x * worldTransforms_.matWorld_.m[0][0]) +
	             (velocity.y * worldTransforms_.matWorld_.m[1][0]) +
	             (velocity.z * worldTransforms_.matWorld_.m[2][0]) +
	             (0 * worldTransforms_.matWorld_.m[3][0]);

	velocity.y = (velocity.x * worldTransforms_.matWorld_.m[0][1]) +
	             (velocity.y * worldTransforms_.matWorld_.m[1][1]) +
	             (velocity.z * worldTransforms_.matWorld_.m[2][1]) +
	             (0 * worldTransforms_.matWorld_.m[3][1]);

	velocity.z = (velocity.x * worldTransforms_.matWorld_.m[0][2]) +
	             (velocity.y * worldTransforms_.matWorld_.m[1][2]) +
	             (velocity.z * worldTransforms_.matWorld_.m[2][2]) +
	             (0 * worldTransforms_.matWorld_.m[3][2]);

	//デバック
	debugText_->SetPos(50, 70);
	debugText_->Printf("velocity:(%f,%f,%f)", velocity.x, velocity.y, velocity.z);

	//弾を生成し、初期化
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(modelENbullet_, worldTransforms_.translation_, velocity);

	//弾を登録する
	bullets_.push_back(std::move(newBullet));

}

Vector3 Enemy::GetWorldPosition() 
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動成分を取得
	worldPos.x = worldTransforms_.translation_.x;
	worldPos.y = worldTransforms_.translation_.y;
	worldPos.z = worldTransforms_.translation_.z;

	return worldPos;
}

void Enemy::OnCollision() { life = life - 1; }

int Enemy::Life() {
	int x;

	x = life;

	return x;
}

void Enemy::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransforms_, viewProjection);
	//弾描画
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}













