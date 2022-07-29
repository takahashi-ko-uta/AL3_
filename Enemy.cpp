#include "Enemy.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "affinTransformation.h"
#include <cassert>
#include <random>

void Enemy::Initalize(Model* model, uint32_t textureHandle)
{
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
	worldTransforms_.translation_ = Vector3(0.0f, 5.0f, 20.0f);
}

void Enemy::Update() 
{
	Vector3 move = {0, 0, 0};

	switch (phase_) {
	case Phase::Approach:
	default:
		//�ړ�
		move = {0.0f,0.0f,-0.2f};
		//����̈ʒu�ɓ��B�����痣�E
		if (worldTransforms_.translation_.z < 0.0f) 
		{
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:
		move = {-0.2f, 0.0f, -0.3f};
		break;
	}
	//���W�ړ�(�x�N�g�����Z)
	worldTransforms_.translation_ += move;
	affinTransformation::Transfer(worldTransforms_);



	//�s��X�V
	worldTransforms_.TransferMatrix();
}

void Enemy::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransforms_, viewProjection, textureHandle_);
}















