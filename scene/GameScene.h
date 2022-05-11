﻿#pragma once

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
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;
	//デバックカメラ
	DebugCamera* debugCamera_ = nullptr;
	float ten_ori[8][4] = {
	  {0.0f, 0.0f, 0.0f, 1.0f},
      {5.0f, 0.0f, 0.0f, 1.0f},
      {5.0f, 0.0f, 5.0f, 1.0f},
	  {0.0f, 0.0f, 5.0f, 1.0f},
      {0.0f, 5.0f, 0.0f, 1.0f},
      {5.0f, 5.0f, 0.0f, 1.0f},
      {5.0f, 5.0f, 5.0f, 1.0f},
      {0.0f, 5.0f, 5.0f, 1.0f}
    };

	float ten_1[8][4] = {};//移動
	float ten_2[8][4] = {};//倍率
	float ten_3[8][4] = {};//回転

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




	int hen2[12][2] = {
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

	/*float afin[3][3] = {
	  {1.0f, 0.0f, 5.0f},
	  {0.0f, 1.0f, 5.0f},
	  {0.0f, 0.0f, 1.0f}
    };*/

	float afin_1[4][4] = {		//移動
	  {1.0f, 0.0f, 0.0f, 5.0f},
	  {0.0f, 1.0f, 0.0f, 5.0f},
	  {0.0f, 0.0f, 1.0f, 0.0f},
	  {0.0f, 0.0f, 0.0f, 1.0f}
    };
	float afin_2[4][4] = {		//倍率
	  {2.0f, 0.0f, 0.0f, 0.0f},
	  {0.0f, 2.0f, 0.0f, 0.0f},
	  {0.0f, 0.0f, 2.0f, 0.0f},
	  {0.0f, 0.0f, 0.0f, 1.0f}
    };
	float afin_3[4][4] = {		//回転
	  {(float)cos(PI / 4), (float)-sin(PI / 4), 0.0f, 0.0f},
	  {(float)sin(PI / 4), (float) cos(PI / 4),  0.0f, 0.0f},
	  {0.0f, 0.0f, 1.0f, 0.0f},
	  {0.0f, 0.0f, 0.0f, 1.0f}
    };
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
