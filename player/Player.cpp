#include "Player.h"
#include "AxisIndicator.h"
#include "MathUtility.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "affinTransformation.h"
#include <cassert>
#include <random>


void Player::Initalize(Model* modelPlayer,Model* modelBullet) {//, uint32_t textureHandle
	// NULL�|�C���^�`�F�b�N
	assert(modelPlayer);
	assert(modelBullet);
	//�����Ƃ��Ď󂯎���ăf�[�^�������o�ϐ��ɋL�^����
	modelPlayer_ = modelPlayer;
	modelBullet_ = modelBullet;
	//textureHandle_ = textureHandle;
	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�ϊ��̏�����
	worldTransforms_.Initialize();
	worldTransform3DReticle_.Initialize();
}


void Player::Update() {
	Move();   //�ړ�����
	Rotate(); //���񏈗�
	Attack(); //�U������

	//���@�̃��[���h���W����3D���e�B�N���̃��[���h���W���v�Z
	{
		//���@����3D���e�B�N���ւ̋���
		const float kDistancePlayerTo3DReticle = 50.0f;
		//���@����3D���e�B�N���ւ̃I�t�Z�b�g�ւ̋���
		Vector3 offset = {0, 0, 1.0f};
		//���@�̃��[���h�s��̉�]�𔽉f
		offset = affinTransformation::VecMat(offset, worldTransforms_);
		//�x�N�g���̒����𐮂���
		offset = Vector3Math::Normalize(offset);
		offset.x *= kDistancePlayerTo3DReticle;
		offset.y *= kDistancePlayerTo3DReticle;
		offset.z *= kDistancePlayerTo3DReticle;
		//3D���e�B�N���̍��W��ݒ�
		worldTransform3DReticle_.translation_ = offset;
		affinTransformation::Transfer(worldTransform3DReticle_);
		worldTransform3DReticle_.TransferMatrix();
	}

	//�e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

	//�f�X�t���O���������e��r��
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });

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
	  "worldTransforms_.translation_:(%f,%f,%f)", worldTransforms_.translation_.x,
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


		//�f�o�b�N
		debugText_->SetPos(50, 70);
		debugText_->Printf("velocity:(%f,%f,%f)", velocity.x, velocity.y, velocity.z);

		//�e�𐶐����A������
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(modelBullet_, worldTransforms_.translation_,velocity);

		//�e��o�^����
		bullets_.push_back(std::move(newBullet));

		//���@����Ə��I�u�W�F�N�g�ւ̃x�N�g��
		velocity =
		  Vector3Math::diff(worldTransform3DReticle_.translation_, worldTransforms_.translation_);
		velocity = Vector3Math::Normalize(velocity);
		velocity.x * kBulletSpeed;
		velocity.y * kBulletSpeed;
		velocity.z * kBulletSpeed;
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
	//�������Ȃ�
}


void Player::Draw(ViewProjection& viewProjection) {
	modelPlayer_->Draw(worldTransforms_, viewProjection);//, textureHandle_
	//�e�`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
	modelBullet_->Draw(worldTransforms_, viewProjection);
}





