#include "Player.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "affinTransformation.h"
#include <cassert>
#include <random>

void Player::Initalize(Model* model, uint32_t textureHandle) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎���ăf�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	textureHandle_ = textureHandle;
	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�ϊ��̏�����
	worldTransforms_.Initialize();
}

void Player::Update() {
	Move();   //�ړ�����
	Rotate(); //���񏈗�
	Attack(); //�U������
	//�e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}
}

void Player::Move() {
#pragma region �L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = {0, 0, 0};
	//�ړ��x�N�g���̕ύX���鏈��
	if (input_->PushKey(DIK_UP)) {
		move.y += 0.5f;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= 0.5f;
	} else if (input_->PushKey(DIK_LEFT)) {
		move.x -= 0.5f;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += 0.5f;
	}

	//���W�ړ�(�x�N�g�����Z)
	worldTransforms_.translation_ += move;
	affinTransformation::Transfer(worldTransforms_);

#pragma region �ړ�����
	//�ړ����E���W
	const float kMoveLimitX = 35.0f;
	const float kMoveLimitY = 20.0f;

	//�͈͂𒴂��Ȃ�����
	worldTransforms_.translation_.x = max(worldTransforms_.translation_.x, -kMoveLimitX);
	worldTransforms_.translation_.x = min(worldTransforms_.translation_.x, +kMoveLimitX);
	worldTransforms_.translation_.y = max(worldTransforms_.translation_.y, -kMoveLimitY);
	worldTransforms_.translation_.y = min(worldTransforms_.translation_.y, +kMoveLimitY);

#pragma endregion

	//�s��X�V
	worldTransforms_.TransferMatrix();

	//�f�o�b�N
	debugText_->SetPos(50, 50);
	debugText_->Printf(
	  " worldTransforms_.translation_:(%f,%f,%f)", worldTransforms_.translation_.x,
	  worldTransforms_.translation_.y, worldTransforms_.translation_.z);
#pragma endregion
}

void Player::Rotate() {
	Vector3 RotY = {0.0f, 0.0f, 0.0f};
	if (input_->PushKey(DIK_U)) {
		RotY.y += 0.01f;
	} else if (input_->PushKey(DIK_I)) {
		RotY.y -= 0.01f;
	}

	worldTransforms_.rotation_ += RotY;
	affinTransformation::Transfer(worldTransforms_);
	//�s��X�V
	worldTransforms_.TransferMatrix();
	//�f�o�b�N
	debugText_->SetPos(50, 70);
	debugText_->Printf(
	  " worldTransforms_.rotation_:(%f,%f,%f)", worldTransforms_.rotation_.x,
	  worldTransforms_.rotation_.y, worldTransforms_.rotation_.z);
}

void Player::Attack() {
	if (input_->PushKey(DIK_SPACE)) {
		//�e�𐶐����A������
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, worldTransforms_.translation_);

		//�e��o�^����
		bullets_.push_back(std::move(newBullet));
	}
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransforms_, viewProjection, textureHandle_);
	//�e�`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}





