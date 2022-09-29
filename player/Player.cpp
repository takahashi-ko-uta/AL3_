#include "Player.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "affinTransformation.h"
#include <cassert>
#include <random>
#include <string> 

void Player::Initalize(Model* modelPlayer, Model* modelPLbullet) {
	// NULL�|�C���^�`�F�b�N
	assert(modelPlayer);
	assert(modelPLbullet);

	//�����Ƃ��Ď󂯎���ăf�[�^�������o�ϐ��ɋL�^����
	model_ = modelPlayer;
	modelPLbullet_ = modelPLbullet;
	//textureHandle_ = textureHandle;
	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�ϊ��̏�����
	worldTransforms_.Initialize();
	worldTransforms_.translation_ = Vector3(0.0f, 0.0f, 0.0f);
	//life�̏�����
	life = 3;
}


void Player::Update() {
	Move();   //�ړ�����
	Rotate(); //���񏈗�
	Attack(); //�U������
	//�e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

	//�f�X�t���O���������e��r��
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });

}

int Player::Life() 
{
	int x;

	x = life;

	return x;
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

	////�f�o�b�N
	//debugText_->SetPos(50, 50);
	//debugText_->Printf(
	//  "worldTransforms_.translation_:(%f,%f,%f)", worldTransforms_.translation_.x,
	//  worldTransforms_.translation_.y, worldTransforms_.translation_.z);
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
	
}

void Player::Attack() {
	if (input_->PushKey(DIK_SPACE)) {
		//�e�̑��x
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		//���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
		//affinTransformation::VecMat(velocity, worldTransforms_);

		velocity.x = (velocity.x * worldTransforms_.matWorld_.m[0][0]) +
		         (velocity.y * worldTransforms_.matWorld_.m[1][0]) +
		         (velocity.z * worldTransforms_.matWorld_.m[2][0]) +
		         (0 * worldTransforms_.matWorld_.m[3][0]);

		velocity.y = (velocity.x * worldTransforms_.matWorld_.m[0][1]) +
		         (velocity.y * worldTransforms_.matWorld_.m[1][1]) +
		         (velocity.z * worldTransforms_.matWorld_.m[2][1]) +
		         (0 * worldTransforms_.matWorld_.m[3][1]);

		velocity.z = (velocity.x * worldTransforms_.matWorld_.m[0][2]) +
		         (velocity.y * worldTransforms_.matWorld_.m[1][2]) +
		         (velocity.z * worldTransforms_.matWorld_.m[2][2]) +
		         (0 * worldTransforms_.matWorld_.m[3][2]);


		//���˃^�C�}�[�J�E���g�_�E��
		FireTimer -= 1;
		//�w�莞�ԂɒB����
		if (FireTimer <= 0) {
			//�e�𐶐����A������
			std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
			newBullet->Initialize(modelPLbullet_, worldTransforms_.translation_, velocity);

			//�e��o�^����
			bullets_.push_back(std::move(newBullet));
			//�^�C�}�[��߂�
			FireTimer = kFireInterval;
		}
		
	} 
	else {
		FireTimer = 0;
	}

	
}

Vector3 Player::GetWorldPosition() 
{
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�ړ��������擾
	worldPos.x = worldTransforms_.translation_.x;
	worldPos.y = worldTransforms_.translation_.y;
	worldPos.z = worldTransforms_.translation_.z;

	return worldPos;
}

void Player::OnCollision() 
{ 
	life = life - 1;
}


void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransforms_, viewProjection);
	//�e�`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}





