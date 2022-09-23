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
#include "Vector3Math.h"

//�s���t�F�[�Y
enum class Phase {
	Approach, //�ڋ߂���
	Leave,	  //���E����
};

//���@�̃N���X�̑O���錾
class Player;

class Enemy {
  public:
	void Initalize(Model* model, uint32_t textureHandle);
	void ApproachInitalize();

	void Update();
	void Move();
	void Attack();
	//���[���h���W���擾
	Vector3 GetWorldPosition();
	// �Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();
	//�e���X�g���擾
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullet() { return bullets_; }
	void Draw(ViewProjection& viewProjection);
	bool IsDead() const { return isDead_; }
	//���ˊԊu
	static const int kFireInterval = 60;

	
	void SetPlayer(Player* player) { player_ = player; }

	float radius = 3.0f;
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
	//���L����
	Player* player_ = nullptr;

	//�f�X�t���O
	bool isDead_ = false;
};

