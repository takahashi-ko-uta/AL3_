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
	float hen2[12][2];
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
	for (int i = 0; i < 12; i++) 
	{
		//PrimitiveDrawer::GetInstance()->DrawLine3d(hen[i][0], hen[i][1], Vector4(0, 70, 0, 255)); 
		PrimitiveDrawer::GetInstance()->DrawLine3d(ten[hen2[i][0]], ten[hen2[i][1]], Vector4(0, 70, 0, 255)); 
	}

	//PrimitiveDrawer::GetInstance()->DrawLine3d(box[i % 4], box[(i + 1) % 4], Vector4(0, 70, 0, 255));			//1^4 
	//PrimitiveDrawer::GetInstance()->DrawLine3d(box[i % 4 + 4], box[(i + 1) % 4 + 4], Vector4(0, 70, 0, 255));	//5^8
	//PrimitiveDrawer::GetInstance()->DrawLine3d(box[i % 4], box[i % 4 +4], Vector4(0, 70, 0, 255));				//縦

	/*
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 0), Vector3(5, 0, 0), Vector4(255, 0, 0, 255));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(5, 0, 0), Vector3(5, 5, 0), Vector4(255, 0, 0, 255));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(5, 5, 0), Vector3(0, 5, 0), Vector4(255, 0, 0, 255));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 5, 0), Vector3(0, 0, 0), Vector4(255, 0, 0, 255));

	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 5), Vector3(0, 5, 5), Vector4(255, 0, 0, 255));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 5), Vector3(5, 0, 5), Vector4(255, 0, 0, 255));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(5, 0, 5), Vector3(5, 5, 5), Vector4(255, 0, 0, 255));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(5, 5, 5), Vector3(0, 5, 5), Vector4(255, 0, 0, 255));

	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 0, 0), Vector3(0, 0, 5), Vector4(255, 0, 0, 255));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(5, 0, 0), Vector3(5, 0, 5), Vector4(255, 0, 0, 255));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(5, 5, 0), Vector3(5, 5, 5), Vector4(255, 0, 0, 255));
	PrimitiveDrawer::GetInstance()->DrawLine3d(Vector3(0, 5, 0), Vector3(0, 5, 5), Vector4(255, 0, 0, 255));*/

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
