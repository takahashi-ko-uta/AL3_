#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include <random>
#include <fstream>

#include "affinTransformation.h"

GameScene::GameScene() {}

GameScene::~GameScene()
{ 
	delete model_;
	delete modelSkydome_;
	delete debugCamera_;
	delete player_;
	delete enemy_;
	delete skydome_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//ファイル名を指定してテクスチャを読み込む
	textureHandle_PL_ = TextureManager::Load("mario.jpg");
	textureHandle_EN_ = TextureManager::Load("enemy.jpg");

	//モデル生成
	model_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	modelPlayer_ = Model::CreateFromOBJ("player", true);
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
	//player_->Initalize(model_,textureHandle_PL_);
	player_->Initalize(modelPlayer_,model_);

	//敵キャラの生成
	enemy_ = new Enemy();
	//敵キャラの初期化
	enemy_->Initalize(model_, textureHandle_EN_);
	
	//敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);

	skydome_ = new Skydome();
	skydome_->Initialze(modelSkydome_);
	
	LoadEnemyPopData();

}


void GameScene::Update()
{

	//デバックカメラの更新
	debugCamera_->Update();
	if (input_->PushKey(DIK_1))
	{
		flag = 1;
	}
	
	if (input_->PushKey(DIK_2)) {
		flag = 0;
		enemy_->SetPlayer(player_);
		skydome_->Initialze(modelSkydome_);
		enemy_->Initalize(model_, textureHandle_EN_);
		player_->Initalize(modelPlayer_, model_);
	}

	if (flag == 1) 
	{
		//自キャラの更新
		player_->Update();

		//敵キャラの更新
		enemy_->Update();

		skydome_->Update();
	}

	UpdateEnemyPopCommands();
	
}

void GameScene::CheckAllCollisons() 
{
	//判定対象AとBの座標
	Vector3 posA, posB;

	//自弾リストの取得
	const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullet();
	//敵弾リストの取得
	const std::list<std::unique_ptr<EnemyBullet>>& enemyBullets = enemy_->GetBullet();

#pragma region 自キャラと敵弾の当たり判定
	//自キャラの座標
	posA = player_->GetWorldPosition();
	//自キャラと敵弾全ての当たり判定
	for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets) 
	{
		posB = bullet->GetWorldPosition();
		Vector3 posC = Vector3Math::diff(posA, posB);//posAとposBの差分
		float L = (player_->radius + bullet->radius) * (player_->radius + bullet->radius);
		if ((posB.x - posA.x) * (posB.x - posA.x) +
			(posB.y - posA.y) * (posB.y - posA.y) +
			(posB.z - posA.z) * (posB.z - posA.z) >= L)
		{
			//自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			//敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}

#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
#pragma endregion

#pragma region 自弾と敵弾の当たり判定
#pragma endregion

}

void GameScene::AddEnemyBullet(std::unique_ptr<EnemyBullet> enemyBullet) 
{
	enemyBullets_.push_back(std::move(enemyBullet));
}

void GameScene::LoadEnemyPopData() 
{
	//ファイルを開く
	std::ifstream file;
	file.open("Resources/enemyPop.csv ");
	assert(file.is_open());

	//ファイルの内容を文字列ストリームにコピー
	enemyPopCommand << file.rdbuf();

	//ファイルを閉じる
	file.close();
}

void GameScene::UpdateEnemyPopCommands() 
{
	//待機処理
	if (waitFlag == true) {
		waitTimer--;
		if (waitTimer <= 0) {
			waitFlag = false;
		}
		return;
	}

	//1行分の文字列を入れる変数
	std::string line;

	//コマンド実行ループ
	while (std::getline(enemyPopCommand,line)) {
		//１行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		// ,区切りで行の先頭文字列を取得
		std::getline(line_stream, word, ',');

		// "//"から始まる行はコメント
		if (word.find("//") == 0) {
			//コメント行を飛ばす
			continue;
		}

		//POPコマンド
		if (word.find("POP") == 0) {
			//x座標
			std::getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			// y座標
			std::getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// z座標
			std::getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			//敵を発生させる
			enemy_->EnemyPosition(Vector3(x, y, z));
		}
		//WAITコマンド
		else if (word.find("WAIT") == 0) {
			std::getline(line_stream, word, ',');

			//待ち時間
			int32_t waitTime = atoi(word.c_str());

			//待機開始
			int waitFlag = true;
			float waitTimer = waitTime;

			//コマンドループを抜ける
			break;
		}
	}
	//デバック
	debugText_->SetPos(50, 90);
	debugText_->Printf("waitFlag:%f", waitFlag);

	debugText_->SetPos(50, 110);
	debugText_->Printf("waitTimer:%f", waitTimer);

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

	skydome_->Draw(viewProjection_);

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
