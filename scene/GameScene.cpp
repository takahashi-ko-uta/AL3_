#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"
#include "MathUtility.h"

#include "Object.h"

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
	
#pragma region スケーリング
	//// X,Y,Z方向のスケーリング
	//worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	////スケーリング行列を宣言
	//Matrix4 matScale;
	////スケーリング倍率を行列を宣言
	//matScale = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	//            0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	//matScale.m[0][0] = worldTransform_.scale_.x;
	//matScale.m[1][1] = worldTransform_.scale_.y;
	//matScale.m[2][2] = worldTransform_.scale_.z;

	//worldTransform_.matWorld_ = MathUtility ::Matrix4Identity();
	//worldTransform_.matWorld_ *= matScale;

	////行列の転送
	//worldTransform_.TransferMatrix();
#pragma endregion

#pragma region 回転Z
	//// X,Y,Z方向のスケーリング
	// worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	////スケーリング行列を宣言
	// Matrix4 matRotZ;
	////スケーリング倍率を行列を宣言
	// matRotZ = {
	//	1.0f, 0.0f, 0.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f, 0.0f,
	//     0.0f, 0.0f, 1.0f, 0.0f,
	//	0.0f, 0.0f, 0.0f, 1.0f
	// };

	// matRotZ.m[0][0] = cos(worldTransform_.rotation_.z);
	// matRotZ.m[0][1] = sin(worldTransform_.rotation_.z);
	// matRotZ.m[1][0] = -sin(worldTransform_.rotation_.z);
	// matRotZ.m[1][1] = cos(worldTransform_.rotation_.z);

	// worldTransform_.matWorld_ = MathUtility ::Matrix4Identity();
	// worldTransform_.matWorld_ *= matRotZ;

	////行列の転送
	// worldTransform_.TransferMatrix();
#pragma endregion

#pragma region 回転X
	//// X,Y,Z方向のスケーリング
	// worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	////スケーリング行列を宣言
	// Matrix4 matRotX;
	////スケーリング倍率を行列を宣言
	// matRotX = {
	//	1.0f, 0.0f, 0.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f, 0.0f,
	//     0.0f, 0.0f, 1.0f, 0.0f,
	//	0.0f, 0.0f, 0.0f, 1.0f
	// };

	// matRotX.m[1][1] = cos(worldTransform_.rotation_.x);
	// matRotX.m[1][2] = sin(worldTransform_.rotation_.x);
	// matRotX.m[2][1] = -sin(worldTransform_.rotation_.x);
	// matRotX.m[2][2] = cos(worldTransform_.rotation_.x);

	// worldTransform_.matWorld_ = MathUtility ::Matrix4Identity();
	// worldTransform_.matWorld_ *= matRotX;

	////行列の転送
	// worldTransform_.TransferMatrix();
#pragma endregion

#pragma region 回転Y
	//// X,Y,Z方向のスケーリング
	// worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	////スケーリング行列を宣言
	// Matrix4 matRotY;
	////スケーリング倍率を行列を宣言
	// matRotY = {
	//	1.0f, 0.0f, 0.0f, 0.0f,
	//	0.0f, 1.0f, 0.0f, 0.0f,
	//     0.0f, 0.0f, 1.0f, 0.0f,
	//	0.0f, 0.0f, 0.0f, 1.0f
	// };

	// matRotY.m[0][0] = cos(worldTransform_.rotation_.y);
	// matRotY.m[0][2] = -sin(worldTransform_.rotation_.y);
	// matRotY.m[2][0] = sin(worldTransform_.rotation_.y);
	// matRotY.m[2][2] = cos(worldTransform_.rotation_.y);

	// worldTransform_.matWorld_ = MathUtility ::Matrix4Identity();
	// worldTransform_.matWorld_ *= matRotY;

	////行列の転送
	// worldTransform_.TransferMatrix();
#pragma endregion

#pragma region 回転の合成
	//// X,Y,Z方向の回転
	//worldTransform_.rotation_ = {PI / 4, PI / 4, PI / 4};
	////回転行列を宣言
	//Matrix4 matRot;
	//Matrix4 matRotX, matRotY, matRotZ;
	////回転倍率を行列を宣言
	//matRot = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	//          0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	//matRotZ = MathUtility ::Matrix4Identity();
	//matRotX = MathUtility ::Matrix4Identity();
	//matRotY = MathUtility ::Matrix4Identity();
	//// Z軸回転の各要素
	//matRotZ.m[0][0] = cos(worldTransform_.rotation_.z);
	//matRotZ.m[0][1] = sin(worldTransform_.rotation_.z);
	//matRotZ.m[1][0] = -sin(worldTransform_.rotation_.z);
	//matRotZ.m[1][1] = cos(worldTransform_.rotation_.z);
	//// X軸回転の各要素
	//matRotX.m[1][1] = cos(worldTransform_.rotation_.x);
	//matRotX.m[1][2] = sin(worldTransform_.rotation_.x);
	//matRotX.m[2][1] = -sin(worldTransform_.rotation_.x);
	//matRotX.m[2][2] = cos(worldTransform_.rotation_.x);
	//// Y軸回転の各要素
	//matRotY.m[0][0] = cos(worldTransform_.rotation_.y);
	//matRotY.m[0][2] = -sin(worldTransform_.rotation_.y);
	//matRotY.m[2][0] = sin(worldTransform_.rotation_.y);
	//matRotY.m[2][2] = cos(worldTransform_.rotation_.y);

	////各軸用回転行列を宣言
	//matRot *= matRotZ *= matRotX *= matRotY;

	//

	//worldTransform_.matWorld_ = MathUtility ::Matrix4Identity();
	//worldTransform_.matWorld_ *= matRot;

	////行列の転送
	//worldTransform_.TransferMatrix();
#pragma endregion

#pragma region 平行移動
	//// X,Y,Z方向の平行移動
	// worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	////平行移動行列を宣言
	// Matrix4 matTrans;
	////平行移動を行列を宣言
	// matTrans = MathUtility ::Matrix4Identity();

	// matTrans.m[3][0] += worldTransform_.translation_.x;
	// matTrans.m[3][1] += worldTransform_.translation_.y;
	// matTrans.m[3][2] += worldTransform_.translation_.z;

	// worldTransform_.matWorld_ = MathUtility ::Matrix4Identity();
	// worldTransform_.matWorld_ *= matTrans;
	////行列の転送
	// worldTransform_.TransferMatrix();
#pragma endregion

#pragma region 組み合わせ
	 //// X,Y,Z方向のスケーリング
	 //worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};
	 //// X,Y,Z方向の回転
	 ////worldTransform_.rotation_ = {PI / 4, PI / 4, PI / 4};
	 //worldTransform_.rotation_ = {PI / 4, PI / 4, PI / 4};
	 //// X,Y,Z方向の平行移動
	 //worldTransform_.translation_ = {5.0f, 5.0f, 5.0f};

	 ////スケーリング行列を宣言
	 //Matrix4 matScale;
	 ////回転行列を宣言
	 //Matrix4 matRot;
	 //Matrix4 matRotX, matRotY, matRotZ;
	 ////平行移動行列を宣言
	 //Matrix4 matTrans;

	 //matScale = MathUtility ::Matrix4Identity();
	 //matRot = MathUtility ::Matrix4Identity();
	 //matRotX = MathUtility ::Matrix4Identity();
	 //matRotY = MathUtility ::Matrix4Identity();
	 //matRotZ = MathUtility ::Matrix4Identity();
	 //matTrans = MathUtility ::Matrix4Identity();
	 //
	 ////倍率
	 //matScale.m[0][0] = worldTransform_.scale_.x;
	 //matScale.m[1][1] = worldTransform_.scale_.y;
	 //matScale.m[2][2] = worldTransform_.scale_.z;
	 //// Z軸回転の各要素
	 //matRotZ.m[0][0] = cos(worldTransform_.rotation_.z);
	 //matRotZ.m[0][1] = sin(worldTransform_.rotation_.z);
	 //matRotZ.m[1][0] = -sin(worldTransform_.rotation_.z);
	 //matRotZ.m[1][1] = cos(worldTransform_.rotation_.z);
	 //// X軸回転の各要素
	 //matRotX.m[1][1] = cos(worldTransform_.rotation_.x);
	 //matRotX.m[1][2] = sin(worldTransform_.rotation_.x);
	 //matRotX.m[2][1] = -sin(worldTransform_.rotation_.x);
	 //matRotX.m[2][2] = cos(worldTransform_.rotation_.x);
	 //// Y軸回転の各要素
	 //matRotY.m[0][0] = cos(worldTransform_.rotation_.y);
	 //matRotY.m[0][2] = -sin(worldTransform_.rotation_.y);
	 //matRotY.m[2][0] = sin(worldTransform_.rotation_.y);
	 //matRotY.m[2][2] = cos(worldTransform_.rotation_.y);
	 ////平行移動
	 //matTrans.m[3][0] += worldTransform_.translation_.x;
	 //matTrans.m[3][1] += worldTransform_.translation_.y;
	 //matTrans.m[3][2] += worldTransform_.translation_.z;

	 ////各軸用回転行列を宣言
	 //matRot *= matRotZ *= matRotX *= matRotY;

	 //worldTransform_.matWorld_ = MathUtility ::Matrix4Identity();
	 //worldTransform_.matWorld_ = matScale *= matRot *= matTrans;

	 ////行列の転送
	 //worldTransform_.TransferMatrix();
#pragma endregion

myApp::Transform(worldTransform_,
	5, 5, 5,
	PI / 4, PI / 4, 0, 
	10, 10, 10);
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
	#pragma region アフィン変換
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
#pragma endregion

	#pragma region 四角の描画

	
	/*for (int i = 0; i < 12; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(ten[hen[i][0]], ten[hen[i][1]], Vector4(255, 255, 255, 255));

		PrimitiveDrawer::GetInstance()->DrawLine3d(ten_move[hen[i][0]], ten_move[hen[i][1]], Vector4(255, 0, 0, 255));
		PrimitiveDrawer::GetInstance()->DrawLine3d(ten_tmg[hen[i][0]], ten_tmg[hen[i][1]], Vector4(0, 255, 0, 255));
		PrimitiveDrawer::GetInstance()->DrawLine3d(ten_rotX[hen[i][0]], ten_rotX[hen[i][1]], Vector4(0, 0, 255, 255));
		PrimitiveDrawer::GetInstance()->DrawLine3d(ten_rotY[hen[i][0]], ten_rotY[hen[i][1]], Vector4(255, 255, 0, 255));
		PrimitiveDrawer::GetInstance()->DrawLine3d(ten_rotZ[hen[i][0]], ten_rotZ[hen[i][1]], Vector4(255, 0, 255, 255));
	}*/
	//PrimitiveDrawer::GetInstance()->DrawLine3d(ten[i % 4], ten[(i + 1) % 4], Vector4(0, 70, 0, 255));			//1^4 
	//PrimitiveDrawer::GetInstance()->DrawLine3d(ten[i % 4 + 4], ten[(i + 1) % 4 + 4], Vector4(0, 70, 0, 255));	//5^8
	//PrimitiveDrawer::GetInstance()->DrawLine3d(ten[i % 4], ten[i % 4 +4], Vector4(0, 70, 0, 255));				//縦
    #pragma endregion
	

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
