#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene()
{ 
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
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	//デバックカメラの生成
	debugCamera_ = new DebugCamera(600, 600);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向は参照するビュープロジェクションを指定する
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
	//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());
	float hen[12][2];
	float ten_1[8][4];

	Vector3 ten_move[8];
	//X,Y,Z方向のスケーリング
	worldTransform_.scale_ = {1,1,1};
	//スケーリング行列を宣言
	Matrix4 matScale;
	//--スケーリング倍率を行列を宣言
	
	//行列の転送
}

void GameScene::Update() 
{
	//デバックカメラの更新
	debugCamera_->Update();
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
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);


	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	/// 
	//3Dモデル描画
	//model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)

	for (size_t i = 0; i < 8; i++) {//移動
		ten_h[i][0] = (ten_ori[i][0] * afin_1[0][0]) + (ten_ori[i][1] * afin_1[0][1]) + (ten_ori[i][2] * afin_1[0][2]) + (ten_ori[i][3] * afin_1[0][3]);
		ten_h[i][1] = (ten_ori[i][0] * afin_1[1][0]) + (ten_ori[i][1] * afin_1[1][1]) + (ten_ori[i][2] * afin_1[1][2]) + (ten_ori[i][3] * afin_1[1][3]);
		ten_h[i][2] = (ten_ori[i][0] * afin_1[2][0]) + (ten_ori[i][1] * afin_1[2][1]) + (ten_ori[i][2] * afin_1[2][2]) + (ten_ori[i][3] * afin_1[2][3]);
		ten_h[i][3] = (ten_ori[i][0] * afin_1[3][0]) + (ten_ori[i][1] * afin_1[3][1]) + (ten_ori[i][2] * afin_1[3][2]) + (ten_ori[i][3] * afin_1[3][3]);
		
		ten_hoz[i] = {ten_h[i][0], ten_h[i][1], ten_h[i][2]};
		ten_move[i] = ten_hoz[i];
	}
	for (size_t i = 0; i < 8; i++) {//倍
		ten_h[i][0] = (ten_ori[i][0] * afin_2[0][0]) + (ten_ori[i][1] * afin_2[0][1]) + (ten_ori[i][2] * afin_2[0][2]) + (ten_ori[i][3] * afin_2[0][3]);
		ten_h[i][1] = (ten_ori[i][0] * afin_2[1][0]) + (ten_ori[i][1] * afin_2[1][1]) + (ten_ori[i][2] * afin_2[1][2]) + (ten_ori[i][3] * afin_2[1][3]);
		ten_h[i][2] = (ten_ori[i][0] * afin_2[2][0]) + (ten_ori[i][1] * afin_2[2][1]) + (ten_ori[i][2] * afin_2[2][2]) + (ten_ori[i][3] * afin_2[2][3]);
		ten_h[i][3] = (ten_ori[i][0] * afin_2[3][0]) + (ten_ori[i][1] * afin_2[3][1]) + (ten_ori[i][2] * afin_2[3][2]) + (ten_ori[i][3] * afin_2[3][3]);

		ten_hoz[i] = {ten_h[i][0], ten_h[i][1], ten_h[i][2]};
		ten_tmg[i] = ten_hoz[i];
	}
	for (size_t i = 0; i < 8; i++) { //回転x
		ten_h[i][0] = (ten_ori[i][0] * afin_3[0][0]) + (ten_ori[i][1] * afin_3[0][1]) +
		              (ten_ori[i][2] * afin_3[0][2]) + (ten_ori[i][3] * afin_3[0][3]);
		ten_h[i][1] = (ten_ori[i][0] * afin_3[1][0]) + (ten_ori[i][1] * afin_3[1][1]) +
		              (ten_ori[i][2] * afin_3[1][2]) + (ten_ori[i][3] * afin_3[1][3]);
		ten_h[i][2] = (ten_ori[i][0] * afin_3[2][0]) + (ten_ori[i][1] * afin_3[2][1]) +
		              (ten_ori[i][2] * afin_3[2][2]) + (ten_ori[i][3] * afin_3[2][3]);
		ten_h[i][3] = (ten_ori[i][0] * afin_3[3][0]) + (ten_ori[i][1] * afin_3[3][1]) +
		              (ten_ori[i][2] * afin_3[3][2]) + (ten_ori[i][3] * afin_3[3][3]);

		ten_hoz[i] = {ten_h[i][0], ten_h[i][1], ten_h[i][2]};
		ten_rotX[i] = ten_hoz[i];
	}
	for (size_t i = 0; i < 8; i++) { //回転y
		ten_h[i][0] = (ten_ori[i][0] * afin_4[0][0]) + (ten_ori[i][1] * afin_4[0][1]) +
		              (ten_ori[i][2] * afin_4[0][2]) + (ten_ori[i][3] * afin_4[0][3]);
		ten_h[i][1] = (ten_ori[i][0] * afin_4[1][0]) + (ten_ori[i][1] * afin_4[1][1]) +
		              (ten_ori[i][2] * afin_4[1][2]) + (ten_ori[i][3] * afin_4[1][3]);
		ten_h[i][2] = (ten_ori[i][0] * afin_4[2][0]) + (ten_ori[i][1] * afin_4[2][1]) +
		              (ten_ori[i][2] * afin_4[2][2]) + (ten_ori[i][3] * afin_4[2][3]);
		ten_h[i][3] = (ten_ori[i][0] * afin_4[3][0]) + (ten_ori[i][1] * afin_4[3][1]) +
		              (ten_ori[i][2] * afin_4[3][2]) + (ten_ori[i][3] * afin_4[3][3]);

		ten_hoz[i] = {ten_h[i][0], ten_h[i][1], ten_h[i][2]};
		ten_rotY[i] = ten_hoz[i];
	}
	for (size_t i = 0; i < 8; i++) {//回転z
		ten_h[i][0] = (ten_ori[i][0] * afin_5[0][0]) + (ten_ori[i][1] * afin_5[0][1]) + (ten_ori[i][2] * afin_5[0][2]) + (ten_ori[i][3] * afin_5[0][3]);
		ten_h[i][1] = (ten_ori[i][0] * afin_5[1][0]) + (ten_ori[i][1] * afin_5[1][1]) + (ten_ori[i][2] * afin_5[1][2]) + (ten_ori[i][3] * afin_5[1][3]);
		ten_h[i][2] = (ten_ori[i][0] * afin_5[2][0]) + (ten_ori[i][1] * afin_5[2][1]) + (ten_ori[i][2] * afin_5[2][2]) + (ten_ori[i][3] * afin_5[2][3]);
		ten_h[i][3] = (ten_ori[i][0] * afin_5[3][0]) + (ten_ori[i][1] * afin_5[3][1]) + (ten_ori[i][2] * afin_5[3][2]) + (ten_ori[i][3] * afin_5[3][3]);

		ten_hoz[i] = {ten_h[i][0], ten_h[i][1], ten_h[i][2]};
		ten_rotZ[i] = ten_hoz[i];
	}
	
	for (int i = 0; i < 12; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(ten[hen[i][0]], ten[hen[i][1]], Vector4(255, 255, 255, 255));

		PrimitiveDrawer::GetInstance()->DrawLine3d(ten_move[hen[i][0]], ten_move[hen[i][1]], Vector4(255, 0, 0, 255));
		PrimitiveDrawer::GetInstance()->DrawLine3d(ten_tmg[hen[i][0]], ten_tmg[hen[i][1]], Vector4(0, 255, 0, 255));
		PrimitiveDrawer::GetInstance()->DrawLine3d(ten_rotX[hen[i][0]], ten_rotX[hen[i][1]], Vector4(0, 0, 255, 255));
		PrimitiveDrawer::GetInstance()->DrawLine3d(ten_rotY[hen[i][0]], ten_rotY[hen[i][1]], Vector4(255, 255, 0, 255));
		PrimitiveDrawer::GetInstance()->DrawLine3d(ten_rotZ[hen[i][0]], ten_rotZ[hen[i][1]], Vector4(255, 0, 255, 255));
	}
	//PrimitiveDrawer::GetInstance()->DrawLine3d(ten[i % 4], ten[(i + 1) % 4], Vector4(0, 70, 0, 255));			//1^4 
	//PrimitiveDrawer::GetInstance()->DrawLine3d(ten[i % 4 + 4], ten[(i + 1) % 4 + 4], Vector4(0, 70, 0, 255));	//5^8
	//PrimitiveDrawer::GetInstance()->DrawLine3d(ten[i % 4], ten[i % 4 +4], Vector4(0, 70, 0, 255));				//縦

	

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
