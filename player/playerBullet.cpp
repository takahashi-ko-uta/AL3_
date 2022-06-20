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

void PlayerBullet::Update() {
	affinTransformation::Transfer(worldTransform_);
	worldTransform_.TransferMatrix();
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}