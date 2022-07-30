#pragma once
#include "Audio.h"
#include "DebugCamera.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <math.h>
#include <memory>
#include <list>
#include "EnemyBullet.h"

//�s���t�F�[�Y
enum class Phase {
	Approach, //�ڋ߂���
	Leave,	  //���E����
};



class Enemy {
  public:
	void Initalize(Model* model, uint32_t textureHandle);
	void ApproachInitalize();

	void Update();
	void Move();
	void Attack();

	void Draw(ViewProjection& viewProjection);



	//���ˊԊu
	static const int kFireInterval = 60;

   private:
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	WorldTransform worldTransforms_;
	uint32_t textureHandle_ = 0;
	//�t�F�[�Y
	Phase phase_ = Phase::Approach;
	//�e
	std::list<std::unique_ptr<EnemyBullet>> bullets_;
	//���˃^�C�}�[
	int32_t FireTimer = 0;
};

//Enemy::Enemy() {}
//
//Enemy::~Enemy() {}
