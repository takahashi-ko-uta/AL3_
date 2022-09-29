#pragma once
#include "Audio.h"
#include "DebugCamera.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <math.h>
#include <memory>
#include <list>

class Player {
  public:
	void Initalize(Model* modelPlayer, Model* modelPLbullet);

	void Update();
	void Move();
	void Rotate();
	void Attack();
	Vector3 GetWorldPosition();
	int Life();
	// �Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();
	//�e���X�g���擾
	const std::list<std::unique_ptr<PlayerBullet>>& GetBullet() { return bullets_; }

	void Draw(ViewProjection& viewProjection);
	float radius = 3.0f;
  private:
	Model* model_ = nullptr;
	Model* modelPlayer_ = nullptr;
	Model* modelPLbullet_ = nullptr;
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	WorldTransform worldTransforms_;
	uint32_t textureHandle_ = 0;
	//�e
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	
	int life = 3;
	//���˃^�C�}�[
	int32_t FireTimer = 0;
	//���ˊԊu
	static const int kFireInterval = 30;
};