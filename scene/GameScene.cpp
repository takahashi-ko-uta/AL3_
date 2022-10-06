#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include <random>

#include "affinTransformation.h"

GameScene::GameScene() {}

GameScene::~GameScene()
{ 
	delete model_;
	delete debugCamera_;
	delete player_;
	delete enemy_;
	delete notesHit_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//ファイル名を指定してテクスチャを読み込む
	textureHandle_PL_ = TextureManager::Load("mario.jpg");
	textureHandle_EN_ = TextureManager::Load("enemy.jpg");
	textureHandle_Black_ = TextureManager::Load("black.jpg");
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

		scene = 0;
		//タイトル用
		titlePic[0] = TextureManager::Load("title1.png");
		title[0] = Sprite::Create(titlePic[0], {0, 0});
	}
	

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	//デバックカメラの生成
	debugCamera_ = new DebugCamera(600, 600);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向は参照するビュープロジェクションを指定する
	//AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());
	
	Vector3 ten_move[8];

	//自キャラの生成
	player_ = new Player();
	//自キャラの初期化
	player_->Initalize(model_,textureHandle_PL_);

	//ノーツの当たり判定取るやつ
	notesHit_ = new NotesHit();
	notesHit_->Initalize(model_, textureHandle_Black_);


	//敵キャラの生成
	enemy_ = new Enemy();
	//bullet_ = new EnemyBullet();
	//敵キャラの初期化
	enemy_->Initalize(model_, textureHandle_EN_);

	//敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);
	enemy_->SetNotesHit(notesHit_);

	

}


void GameScene::Update()
{
	//デバックカメラの更新
	debugCamera_->Update();


	
	
	if (scene == 0) { //タイトル
	}
	if (input_->TriggerKey(DIK_SPACE)) {
		scene = 1;
	}

	switch (scene) {
	case 0://タイトル
		if (input_->TriggerKey(DIK_SPACE)) {
			scene = 1;
		}
		break;

	case 1://ゲーム
#pragma region 各更新処理
		//自キャラの更新
		player_->Update();

		//敵キャラの更新
		enemy_->Update();

		// notesHitの更新
		notesHit_->Update();

		//衝突判定
		CheckAllCollisons();

		//成功判定
		TriggerJudge();
#pragma endregion
		
		break;

	}
	
	
}

void GameScene::CheckAllCollisons() 
{
	//判定対象AとBの座標
	Vector3 posA, posB;

	//自弾リストの取得
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullet();
	//敵弾リストの取得
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy_->GetBullet();

#pragma region NotesHitと敵弾の当たり判定
	//自キャラの座標
	posA = notesHit_->GetWorldPosition();

	//自キャラと敵弾全ての当たり判定
	for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets) {
		//敵弾の座標
		posB = bullet->GetWorldPosition();

		const float AR = 1;
		const float BR = 1;

		float A = pow((posB.x - posA.x), 2) + pow((posB.y - posA.y), 2) + pow((posB.z - posA.z), 2);
		float B = pow((AR + BR), 2);

		if (A <= B) {
			//自キャラの衝突時コールバックを呼び出す
			notesHit_->OnCollision();
			//敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
		else
		{
			bullet->NotCollision();
		}
	}

	
	
#pragma endregion

#pragma region 自キャラと敵弾の当たり判定
	{
		////自キャラの座標
		// posA = player_->GetWorldPosition();

		////自キャラと敵弾全ての当たり判定
		// for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets) {
		//	//敵弾の座標
		//	posB = bullet->GetWorldPosition();

		//	const float AR = 1;
		//	const float BR = 1;

		//	float A = pow((posB.x - posA.x), 2) + pow((posB.y - posA.y), 2) + pow((posB.z - posA.z),
		//2); 	float B = pow((AR + BR), 2);

		//	if (A <= B) {
		//		//自キャラの衝突時コールバックを呼び出す
		//		player_->OnCollision();
		//		//敵弾の衝突時コールバックを呼び出す
		//		bullet->OnCollision();
		//	} else {
		//		bullet->NotCollision();
		//	}
		//}

		// debugText_->SetPos(50, 90);
		// debugText_->Printf(
		//   "posA:(%f,%f,%f) , posB:(%f,%f,%f)", posA.x, posA.y, posA.z, posB.x, posB.y, posB.z);
	}
#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
	posA = enemy_->GetWorldPosition();
	//自弾と敵キャラ全ての当たり判定
	for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) {
		//自弾の座標
		posB = bullet->GetWorldPosition();

		const float AR = 1;
		const float BR = 1;

		float A = pow((posB.x - posA.x), 2) + pow((posB.y - posA.y), 2) + pow((posB.z - posA.z), 2);
		float B = pow((AR + BR), 2);

		if (A <= B) {
			//自キャラの衝突時コールバックを呼び出す
			enemy_->OnCollision();
			//敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}
#pragma endregion

#pragma region 自弾と敵弾の当たり判定
	//自キャラと敵弾全ての当たり判定
	for (const std::unique_ptr<EnemyBullet>& enemybullet : enemyBullets) {
		//自弾と敵キャラ全ての当たり判定
		for (const std::unique_ptr<PlayerBullet>& playerbullet : playerBullets) {
			//自弾の座標
			posA = playerbullet->GetWorldPosition();
			//自弾の座標
			posB = enemybullet->GetWorldPosition();

			const float AR = 1;
			const float BR = 1;

			float A =
			  pow((posB.x - posA.x), 2) + pow((posB.y - posA.y), 2) + pow((posB.z - posA.z), 2);
			float B = pow((AR + BR), 2);

			if (A <= B) {
				//自キャラの衝突時コールバックを呼び出す
				enemybullet->OnCollision();
				//敵弾の衝突時コールバックを呼び出す
				playerbullet->OnCollision();
			}
		}
	}
#pragma endregion
}

void GameScene::TriggerJudge() 
{
	
	bool playerTrigger = false;
	bool bulletTrigger = false;
	//敵弾リストの取得
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy_->GetBullet();

	playerTrigger = player_->GetTrigger();
	for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets) {
		//敵弾の座標
		bulletTrigger = bullet->GetTrigger();
		
		if (playerTrigger == true && bulletTrigger == true) {
			judge = judge + 1;
		}
	}

	debugText_->SetPos(50, 70);
	debugText_->Printf("judge:%d ,PLtri:%d , BLtri:%d", judge,playerTrigger,bulletTrigger);
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
	
	

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	/// 
	//3Dモデル描画
	
	//自キャラの描画
	player_->Draw(viewProjection_);

	//敵キャラの描画
	enemy_->Draw(viewProjection_);

	//notesHitの更新
	notesHit_->Draw(viewProjection_);

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
	switch (scene) {
	case 0:
		title[titlenum]->Draw();
		break;
	case 1:

		break;
	}
	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
	
}
