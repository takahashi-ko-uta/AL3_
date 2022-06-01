#include "Player.h"
#include "TextureManager.h"
#include <cassert>
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"
#include <random>

void Player::InitiaLize(Model* model, uint32_t textreHandle) {
	//NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎���ăf�[�^�������o�ϐ��ɋL������
	model_ = model;
	textureHandle_ = textreHandle;
	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	worldTransform_.Initialize();
}

void Player::Update() 
{ 
#pragma region �v���C���[�̈ړ�
	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = {0, 0, 0};
	//�L�����N�^�[�ړ����x
	const float playerSpeed = 0.2;
	
	//�����������ňړ��x�N�g����ύX
	if (input_->PushKey(DIK_LEFT)) {
		move = {-playerSpeed, 0, 0};
	} 
	else if (input_->PushKey(DIK_RIGHT)) {
		move = {playerSpeed, 0, 0};
	} 
	else if (input_->PushKey(DIK_UP)) {
		move = {0, -playerSpeed, 0};
	} 
	else if (input_->PushKey(DIK_DOWN)) {
		move = {0, playerSpeed, 0};
	}
	//�����_�ړ�(�x�N�g�����Z)
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	worldTransform_.TransferMatrix();

	debugText_->SetPos(50, 150);
	debugText_->Printf(
	  "Root:(%f,%f,%f)",
		worldTransform_.translation_.x,
		worldTransform_.translation_.y,
	    worldTransform_.translation_.z);

#pragma endregion
}

void Player::Draw(ViewProjection viewProjection_) {
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
}
