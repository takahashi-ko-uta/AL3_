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
	//範囲forで全てのワールドトランスフォームを順に処理する
	for (WorldTransform& worldTransform : worldTransforms_) {

		//ワールドトランスフォームの初期化
		worldTransform.Initialize();

		//乱数エンジンを渡し、指定範囲からランダムな数値を得る
		float rRot = dist(engine);
		float rTransX = dist(engine);
		float rTransY = dist(engine);
		float rTransZ = dist(engine);
		// X,Y,Z方向のスケーリング
		worldTransform.scale_ = {1, 1, 1};
		// X,Y,Z方向の回転
		worldTransform.rotation_ = {rRot, rRot, rRot};
		// X,Y,Z方向の平行移動
		worldTransform.translation_ = {rTransX, rTransY, rTransZ};

		affinTransformation::Transfer(worldTransform);
		//行列の転送
		worldTransform.TransferMatrix();
	}
	//カメラ視点座標を指定
	viewProjection_.eye = {0, 0, -10};
	//カメラ注視点座標を設定
	viewProjection_.target = {10, 0, 0};
	//カメラ上方向ベクトルを指定
	viewProjection_.up = {cosf(PI / 4.0f), cosf(PI / 4.0f), 0.0f};
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	//デバックカメラの生成
	debugCamera_ = new DebugCamera(600, 600);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向は参照するビュープロジェクションを指定する
	// AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

	//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	Vector3 ten_move[8];

#pragma region スケーリング
	//// X,Y,Z方向のスケーリング
	// worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	////スケーリング行列を宣言
	// Matrix4 matScale;
	////スケーリング倍率を行列を宣言
	// matScale = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	//             0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

	// matScale.m[0][0] = worldTransform_.scale_.x;
	// matScale.m[1][1] = worldTransform_.scale_.y;
	// matScale.m[2][2] = worldTransform_.scale_.z;

	// worldTransform_.matWorld_ = MathUtility ::Matrix4Identity();
	// worldTransform_.matWorld_ *= matScale;

	////行列の転送
	// worldTransform_.TransferMatrix();
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
	// worldTransform_.rotation_ = {PI / 4, PI / 4, PI / 4};
	////回転行列を宣言
	// Matrix4 matRot;
	// Matrix4 matRotX, matRotY, matRotZ;
	////回転倍率を行列を宣言
	// matRot = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	//           0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
	// matRotZ = MathUtility ::Matrix4Identity();
	// matRotX = MathUtility ::Matrix4Identity();
	// matRotY = MathUtility ::Matrix4Identity();
	//// Z軸回転の各要素
	// matRotZ.m[0][0] = cos(worldTransform_.rotation_.z);
	// matRotZ.m[0][1] = sin(worldTransform_.rotation_.z);
	// matRotZ.m[1][0] = -sin(worldTransform_.rotation_.z);
	// matRotZ.m[1][1] = cos(worldTransform_.rotation_.z);
	//// X軸回転の各要素
	// matRotX.m[1][1] = cos(worldTransform_.rotation_.x);
	// matRotX.m[1][2] = sin(worldTransform_.rotation_.x);
	// matRotX.m[2][1] = -sin(worldTransform_.rotation_.x);
	// matRotX.m[2][2] = cos(worldTransform_.rotation_.x);
	//// Y軸回転の各要素
	// matRotY.m[0][0] = cos(worldTransform_.rotation_.y);
	// matRotY.m[0][2] = -sin(worldTransform_.rotation_.y);
	// matRotY.m[2][0] = sin(worldTransform_.rotation_.y);
	// matRotY.m[2][2] = cos(worldTransform_.rotation_.y);

	////各軸用回転行列を宣言
	// matRot *= matRotZ *= matRotX *= matRotY;

	//

	// worldTransform_.matWorld_ = MathUtility ::Matrix4Identity();
	// worldTransform_.matWorld_ *= matRot;

	////行列の転送
	// worldTransform_.TransferMatrix();
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
	// worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};
	//// X,Y,Z方向の回転
	////worldTransform_.rotation_ = {PI / 4, PI / 4, PI / 4};
	// worldTransform_.rotation_ = {PI / 4, PI / 4, PI / 4};
	//// X,Y,Z方向の平行移動
	// worldTransform_.translation_ = {5.0f, 5.0f, 5.0f};

	////スケーリング行列を宣言
	// Matrix4 matScale;
	////回転行列を宣言
	// Matrix4 matRot;
	// Matrix4 matRotX, matRotY, matRotZ;
	////平行移動行列を宣言
	// Matrix4 matTrans;

	// matScale = MathUtility ::Matrix4Identity();
	// matRot = MathUtility ::Matrix4Identity();
	// matRotX = MathUtility ::Matrix4Identity();
	// matRotY = MathUtility ::Matrix4Identity();
	// matRotZ = MathUtility ::Matrix4Identity();
	// matTrans = MathUtility ::Matrix4Identity();
	//
	////倍率
	// matScale.m[0][0] = worldTransform_.scale_.x;
	// matScale.m[1][1] = worldTransform_.scale_.y;
	// matScale.m[2][2] = worldTransform_.scale_.z;
	//// Z軸回転の各要素
	// matRotZ.m[0][0] = cos(worldTransform_.rotation_.z);
	// matRotZ.m[0][1] = sin(worldTransform_.rotation_.z);
	// matRotZ.m[1][0] = -sin(worldTransform_.rotation_.z);
	// matRotZ.m[1][1] = cos(worldTransform_.rotation_.z);
	//// X軸回転の各要素
	// matRotX.m[1][1] = cos(worldTransform_.rotation_.x);
	// matRotX.m[1][2] = sin(worldTransform_.rotation_.x);
	// matRotX.m[2][1] = -sin(worldTransform_.rotation_.x);
	// matRotX.m[2][2] = cos(worldTransform_.rotation_.x);
	//// Y軸回転の各要素
	// matRotY.m[0][0] = cos(worldTransform_.rotation_.y);
	// matRotY.m[0][2] = -sin(worldTransform_.rotation_.y);
	// matRotY.m[2][0] = sin(worldTransform_.rotation_.y);
	// matRotY.m[2][2] = cos(worldTransform_.rotation_.y);
	////平行移動
	// matTrans.m[3][0] += worldTransform_.translation_.x;
	// matTrans.m[3][1] += worldTransform_.translation_.y;
	// matTrans.m[3][2] += worldTransform_.translation_.z;

	////各軸用回転行列を宣言
	// matRot *= matRotZ *= matRotX *= matRotY;

	// worldTransform_.matWorld_ = MathUtility ::Matrix4Identity();
	// worldTransform_.matWorld_ = matScale *= matRot *= matTrans;

	////行列の転送
	// worldTransform_.TransferMatrix();
#pragma endregion
}
void GameScene::Update() {
	//デバックカメラの更新
	debugCamera_->Update();

	//視点移動の移動ベクトル
	{
		//視点の移動ベクトル
		Vector3 move = {0.0f, 0.0f, 0.0f};
		//視点の移動の速さ
		const float kEyeSpeed = 0.2f;

		//押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_W)) {
			move.z += kEyeSpeed;
		} else if (input_->PushKey(DIK_S)) {
			move.z -= kEyeSpeed;
		}

		//視点移動(ベクトルの加算)
		viewProjection_.eye += move;

		//行列の再計算
		viewProjection_.UpdateMatrix();

		//デバック用テキスト
		debugText_->SetPos(50, 50);
		debugText_->Printf(
		  "eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
	}

	//注視点移動の移動ベクトル
	{
		//注視点の移動ベクトル
		Vector3 move = {0.0f, 0.0f, 0.0f};
		//注視点の移動の速さ
		const float kEyeSpeed = 0.2f;

		//押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_LEFT)) {
			move.x -= kEyeSpeed;
		} else if (input_->PushKey(DIK_RIGHT)) {
			move.x += kEyeSpeed;
		}

		//注視点移動(ベクトルの加算)
		viewProjection_.eye += move;

		//行列の再計算
		viewProjection_.UpdateMatrix();

		//デバック用テキスト
		debugText_->SetPos(50, 70);
		debugText_->Printf(
		  "eye:(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y,
		  viewProjection_.target.z);
	}

	//上方向回転処理
	{
		//上方向の回転の速さ[ラジアン/frame]
		const float kUpRotSpeed = 0.05f;

		//押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_SPACE)) {
			viewAngle += kUpRotSpeed;
			// 2πを超えたら戻す
			viewAngle = fmodf(viewAngle, PI * 2.0f);
		}

		//上方向ベクトルを計算
		viewProjection_.up = {cosf(viewAngle), sinf(viewAngle), 0.0f};

		//行列の再計算
		viewProjection_.UpdateMatrix();

		//デバック用テキスト
		debugText_->SetPos(50, 90);
		debugText_->Printf(
		  "up:(%f,%f,%f)", viewProjection_.up.x, viewProjection_.up.y, viewProjection_.up.z);
	}
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
	/*for (WorldTransform& worldTransform : worldTransforms_) {
	    model_->Draw(worldTransform, debugCamera_->GetViewProjection(), textureHandle_);
	}*/

	for (WorldTransform& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, viewProjection_, textureHandle_);
	}

/// <summary>
/// ここに3Dオブジェクトの描画処理を追加できる
/// </summary>
///
// 3Dモデル描画
// model_->Draw(worldTransform_, viewProjection_, textureHandle_);
//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)


#pragma region 四角の描画

/*for (int i = 0; i < 12; i++) {
	PrimitiveDrawer::GetInstance()->DrawLine3d(ten[hen[i][0]], ten[hen[i][1]], Vector4(255, 255,
255, 255));

	PrimitiveDrawer::GetInstance()->DrawLine3d(ten_move[hen[i][0]], ten_move[hen[i][1]],
Vector4(255, 0, 0, 255)); PrimitiveDrawer::GetInstance()->DrawLine3d(ten_tmg[hen[i][0]],
ten_tmg[hen[i][1]], Vector4(0, 255, 0, 255));
	PrimitiveDrawer::GetInstance()->DrawLine3d(ten_rotX[hen[i][0]], ten_rotX[hen[i][1]], Vector4(0,
0, 255, 255)); PrimitiveDrawer::GetInstance()->DrawLine3d(ten_rotY[hen[i][0]], ten_rotY[hen[i][1]],
Vector4(255, 255, 0, 255)); PrimitiveDrawer::GetInstance()->DrawLine3d(ten_rotZ[hen[i][0]],
ten_rotZ[hen[i][1]], Vector4(255, 0, 255, 255));
}*/
// PrimitiveDrawer::GetInstance()->DrawLine3d(ten[i % 4], ten[(i + 1) % 4], Vector4(0, 70, 0, 255));
// //1^4 PrimitiveDrawer::GetInstance()->DrawLine3d(ten[i % 4 + 4], ten[(i + 1) % 4 + 4], Vector4(0,
// 70, 0, 255));	//5^8 PrimitiveDrawer::GetInstance()->DrawLine3d(ten[i % 4], ten[i % 4 +4],
// Vector4(0, 70, 0, 255));				//縦
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
