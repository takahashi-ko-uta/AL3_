#include "PlayerBullet.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "affinTransformation.h"
#include <cassert>
#include <random>

void PlayerBullet::Initialize(Model* model, const Vector3& position) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎���ăf�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	textureHandle_ = TextureManager::Load("black.jpg");

	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = {position.x,position.y,position.z};
}

void PlayerBullet::Update(WorldTransform worldTransform) {
	//for (size_t i = 0; i < 9; i++) {
	//	affinTransformation::Transfer(worldTransform_);
	//	worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;
	//	worldTransform_.TransferMatrix();
	//}
	affinTransformation::Transfer(worldTransform_);
	//worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;
	worldTransform_.TransferMatrix();
	// affinTransformation::Par(worldTransform_, 0, 1);
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}