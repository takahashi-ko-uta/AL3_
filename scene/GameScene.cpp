#include "GameScene.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>
#include <random>

#include "affinTransformation.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");
	//モデル生成
	model_ = Model::Create();

	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌ・ツイスターの乱数エンジン
	std::mt19937_64 engine(seed_gen());
	//乱数範囲の指定
	std::uniform_real_distribution<float> dist(-10, 10); // dist(最大値,最小値)

	//ワールドトランスフォームの初期化
	//キャラクターの大元
	worldTransforms_[PartID::kRoot].Initialize();
	//脊髄
	worldTransforms_[PartID::kSpine].Initialize();
	worldTransforms_[PartID::kSpine].parent_ = &worldTransforms_[PartID::kRoot];
	worldTransforms_[PartID::kSpine].translation_ = {0, 0, 0};

	//上半身
	//胸
	worldTransforms_[PartID::kChest].Initialize();
	worldTransforms_[PartID::kChest].parent_ = &worldTransforms_[PartID::kSpine];
	worldTransforms_[PartID::kChest].translation_ = {0, 0, 0};

	//頭
	worldTransforms_[PartID::kHead].Initialize();
	worldTransforms_[PartID::kHead].parent_ = &worldTransforms_[PartID::kChest];
	worldTransforms_[PartID::kHead].translation_ = {0, 2.5f, 0};

	//左腕
	worldTransforms_[PartID::kArmL].Initialize();
	worldTransforms_[PartID::kArmL].parent_ = &worldTransforms_[PartID::kChest];
	worldTransforms_[PartID::kArmL].translation_ = {-2.5f, 0, 0};

	//右腕
	worldTransforms_[PartID::kArmR].Initialize();
	worldTransforms_[PartID::kArmR].parent_ = &worldTransforms_[PartID::kChest];
	worldTransforms_[PartID::kArmR].translation_ = {2.5f, 0, 0};

	//下半身
	//尻
	worldTransforms_[PartID::kHip].Initialize();
	worldTransforms_[PartID::kHip].parent_ = &worldTransforms_[PartID::kSpine];
	worldTransforms_[PartID::kHip].translation_ = {0, -2.5f, 0};

	//左足
	worldTransforms_[PartID::kLegL].Initialize();
	worldTransforms_[PartID::kLegL].parent_ = &worldTransforms_[PartID::kHip];
	worldTransforms_[PartID::kLegL].translation_ = {-2.5f, -2.5f, 0};

	//右足
	worldTransforms_[PartID::kLegR].Initialize();
	worldTransforms_[PartID::kLegR].parent_ = &worldTransforms_[PartID::kHip];
	worldTransforms_[PartID::kLegR].translation_ = {2.5f, -2.5f, 0};

	//カメラ垂直方向視野角を設定
	//viewProjection_.fovAngleY = 10 * PI / 180;
	//アスペクト比を設定
	//viewProjection_.aspectRatio = 2.0f;

	//ニアクリップ距離を設定
	// viewProjection_.nearZ = 52.0f;
	//ファークリップ距離を設定
	// viewProjection_.farZ = 53.0f;

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	//デバックカメラの生成
	debugCamera_ = new DebugCamera(600, 600);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向は参照するビュープロジェクションを指定する
	// AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

	Vector3 ten_move[8];
}
void GameScene::Update() {
	//デバックカメラの更新
	debugCamera_->Update();

	// Fov変更処理

	//上キーで視野角が広がる
	if (input_->PushKey(DIK_UP)) {
		viewProjection_.fovAngleY += 0.01f;
		viewProjection_.fovAngleY = min(viewProjection_.fovAngleY, PI);
	}

	//下キーで視野角が狭まる
	else if (input_->PushKey(DIK_DOWN)) {
		viewProjection_.fovAngleY -= 0.01f;
		viewProjection_.fovAngleY = max(viewProjection_.fovAngleY, 0);
	}
	//行列の再計算
	viewProjection_.UpdateMatrix();

	//デバック
	debugText_->SetPos(50, 110);
	debugText_->Printf("fovAngleY(Degree):%f", viewProjection_.fovAngleY * 180 / PI);

	


#pragma region キャラクターの移動処理
	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	//左右キーを押したときmove(移動量)を変化
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= 0.1f;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += 0.1f;
	}

	// translationにmoveを加算
	worldTransforms_[PartID::kRoot].translation_ += move;
	affinTransformation::Translate(worldTransforms_[PartID::kRoot]);
	worldTransforms_[PartID::kRoot].TransferMatrix();

	//デバック
	debugText_->SetPos(50, 130);
	debugText_->Printf(
	  "worldTransform_[PartID::kChest].rotation:%f,%f,%f",
		worldTransforms_[PartID::kChest].rotation_.x,
		worldTransforms_[PartID::kChest].rotation_.y,
		worldTransforms_[PartID::kChest].rotation_.z);

	
	
#pragma endregion

	
#pragma region 子の更新
	for (int i = 1; i < kNumPartId; i++) {
		affinTransformation::Transfer(worldTransforms_[i]);
		worldTransforms_[i].matWorld_ *= worldTransforms_[i].parent_->matWorld_;
		worldTransforms_[i].TransferMatrix();
	}
#pragma endregion

#pragma region 上半身の回転
	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_U)) 
	{
		worldTransforms_[PartID::kChest].rotation_.y -= 0.1f;
	}
	else if (input_->PushKey(DIK_I)) 
	{
		worldTransforms_[PartID::kChest].rotation_.y += 0.1f;
	}
#pragma endregion

#pragma region 下半身の回転
	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_J)) {
		worldTransforms_[PartID::kHip].rotation_.y -= 0.1f;
	} else if (input_->PushKey(DIK_K)) {
		worldTransforms_[PartID::kHip].rotation_.y += 0.1f;
	}
#pragma endregion
}

void GameScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画

	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);
	//モデルカメラを連動
	for (size_t i = 2; i < kNumPartId; i++) {
		model_->Draw(worldTransforms_[i], viewProjection_, textureHandle_);
	}

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	///
	// 3Dモデル描画
	// model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
