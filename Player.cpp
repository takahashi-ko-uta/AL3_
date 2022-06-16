#include"player/Player.h"
#include "TextureManager.h"
#include <cassert>
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include <random>
#include "affinTransformation.h"


void Player::Initalize(Model* model, uint32_t textureHandle) 
{
	//NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎���ăf�[�^�������o�ϐ��ɋL�^����
	model_ = model;
	textureHandle_ = textureHandle;
	//�V���O���g���C���X�^���X���擾����
	input_= Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�ϊ��̏�����
	worldTransforms_.Initialize();
}

void Player::Update() 
{
#pragma region �L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = {0,0,0};
	//�ړ��x�N�g���̕ύX���鏈��
	if (input_->PushKey(DIK_UP))
	{
		move.y += 0.5f; 
	} 
	else if(input_->PushKey(DIK_DOWN)) 
	{
		move.y -= 0.5f;
	} 
	else if (input_->PushKey(DIK_LEFT)) 
	{
		move.x -= 0.5f;
	}
	else if (input_->PushKey(DIK_RIGHT))
	{
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

	debugText_->SetPos(50, 50);
	debugText_->Printf(
	  " worldTransforms_.translation_:(%f,%f,%f)", worldTransforms_.translation_.x,
	  worldTransforms_.translation_.y, worldTransforms_.translation_.z);
#pragma endregion


}

void Player::Draw(ViewProjection& viewProjection) 
{ 
	model_->Draw(worldTransforms_, viewProjection, textureHandle_);
}





