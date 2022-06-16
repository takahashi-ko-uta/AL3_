#include "PlayerBullet.h"
#include "TextureManager.h"
#include <cassert>
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include <random>
#include "affinTransformation.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position) 
{
	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎���ăf�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	textureHandle_ = TextureManager::Load("black.jpg");

	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
}

void PlayerBullet::Update()
{ 
	affinTransformation::Transfer(worldTransform_);
	worldTransform_.TransferMatrix();
	//affinTransformation::Par(worldTransform_, 0, 1); 
}


void PlayerBullet::Draw(const ViewProjection& viewProjection) 
{ 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}



