#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include <math.h>

#include "affinTransformation.h"
#include "myWorldTransform.h"

#define PI 3.141592

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	//3Dモデル
	Model* model_ = nullptr;
	//ワールドトランスフォームビュープロジェクション
	WorldTransform worldTransforms_[100];
	//ビュープロジェクション
	ViewProjection viewProjection_;
	//デバックカメラ
	DebugCamera* debugCamera_ = nullptr;
	//カメラ上方向の角度
	float viewAngle = 0.0f;
#pragma region アフィン変換
	float ten_ori[8][4] = {
  //元の
	  {0.0f, 0.0f, 0.0f, 1.0f},
      {5.0f, 0.0f, 0.0f, 1.0f},
      {5.0f, 0.0f, 5.0f, 1.0f},
	  {0.0f, 0.0f, 5.0f, 1.0f},
      {0.0f, 5.0f, 0.0f, 1.0f},
      {5.0f, 5.0f, 0.0f, 1.0f},
	  {5.0f, 5.0f, 5.0f, 1.0f},
      {0.0f, 5.0f, 5.0f, 1.0f}
    };
	float ten_h[8][4] = {}; //保存

	Vector3 ten[8] = {
	  {0.0f, 0.0f, 0.0f},
      {5.0f, 0.0f, 0.0f},
      {5.0f, 0.0f, 5.0f},
      {0.0f, 0.0f, 5.0f},
	  {0.0f, 5.0f, 0.0f},
      {5.0f, 5.0f, 0.0f},
      {5.0f, 5.0f, 5.0f},
      {0.0f, 5.0f, 5.0f}
    };

	Vector3 ten_hoz[8] = {};  //保存用
	Vector3 ten_move[8] = {}; //移動
	Vector3 ten_tmg[8] = {};  //倍率
	Vector3 ten_rotX[8] = {}; //回転X
	Vector3 ten_rotY[8] = {}; //回転Y
	Vector3 ten_rotZ[8] = {}; //回転Z
	int hen[12][2] = {
	  {0, 1},
      {1, 2},
      {2, 3},
      {3, 0},

	  {4, 5},
      {5, 6},
      {6, 7},
      {7, 4},

	  {0, 4},
      {1, 5},
      {2, 6},
      {3, 7},
	};

	float afin_1[4][4] = {
  //移動
	  {1.0f, 0.0f, 0.0f, 5.0f},
	  {0.0f, 1.0f, 0.0f, 5.0f},
	  {0.0f, 0.0f, 1.0f, 0.0f},
	  {0.0f, 0.0f, 0.0f, 1.0f}
    };
	float afin_2[4][4] = {
  //倍率
	  {2.0f, 0.0f, 0.0f, 0.0f},
	  {0.0f, 2.0f, 0.0f, 0.0f},
	  {0.0f, 0.0f, 2.0f, 0.0f},
	  {0.0f, 0.0f, 0.0f, 1.0f}
    };

	float afin_3[4][4] = {
  //回転(X軸)
	  {1.0f, 0.0f,               0.0f,                0.0f},
	  {0.0f, (float)cos(PI / 4), (float)-sin(PI / 4), 0.0f},
	  {0.0f, (float)sin(PI / 4), (float)cos(PI / 4),  0.0f},
	  {0.0f, 0.0f,               0.0f,                1.0f}
    };
	float afin_4[4][4] = {
  //回転(Y軸)
	  {(float)cos(PI / 4),  0.0f, (float)sin(PI / 4), 0.0f},
	  {0.0f,                1.0f, 0.0f,               0.0f},
	  {(float)-sin(PI / 4), 0.0f, (float)cos(PI / 4), 0.0f},
	  {0.0f,                0.0f, 0.0f,               1.0f}
    };
	float afin_5[4][4] = {
  //回転(Z軸)
	  {(float)cos(PI / 4), (float)-sin(PI / 4), 0.0f, 0.0f},
	  {(float)sin(PI / 4), (float)cos(PI / 4),  0.0f, 0.0f},
	  {0.0f,               0.0f,                1.0f, 0.0f},
	  {0.0f,               0.0f,                0.0f, 1.0f}
    };
#pragma endregion
	

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
