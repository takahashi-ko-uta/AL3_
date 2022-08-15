#include "enemy/Enemy.h"
#include "player/Player.h"
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

	//�ڋ߃t�F�[�Y�̏�����
	ApproachInitalize();

	//���[���h�ϊ��̏�����
	worldTransforms_.Initialize();
	worldTransforms_.translation_ = Vector3(0.0f, 5.0f, 20.0f);
}

void Enemy::ApproachInitalize() 
{
	//���˃^�C�}�[������
	FireTimer = kFireInterval;
}

void Enemy::Update() 
{ 
	Move();
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}

	//�f�X�t���O���������e��r��
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) { return bullet->IsDead(); });
}

void Enemy::Move() 
{
	Vector3 move = {0, 0, 0};
	switch (phase_) {
	case Phase::Approach:
	default:
		//���˃^�C�}�[�J�E���g�_�E��
		FireTimer -= 1;
		//�w�莞�ԂɒB����
		if (FireTimer == 0) 
		{
			//�e�𔭎�
			Attack();
			//�^�C�}�[��߂�
			FireTimer = kFireInterval;
		}

		//�ړ�
		move = {0.0f, 0.0f, -0.1f};
		//����̈ʒu�ɓ��B�����痣�E
		if (worldTransforms_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:
		move = {-0.2f, 0.0f, -0.2f};
		break;
	}
	//���W�ړ�(�x�N�g�����Z)
	worldTransforms_.translation_ += move;
	affinTransformation::Transfer(worldTransforms_);
	//�s��X�V
	worldTransforms_.TransferMatrix();
}

void Enemy::Attack() {
	assert(player_);

	//�e�̑��x
	const float kBulletSpeed = 0.1f;

	//Vector3 velocity(0, 0, kBulletSpeed);
	Vector3 PLvec = player_->GetWorldPosition();//���L�����̃��[���h���W���擾
	Vector3 ENvec = GetWorldPosition();			//�G�L�����̃��[���h���W���擾
	Vector3 SPvec = Vector3Math::diff(PLvec, ENvec); //�G�L���������L�����̍����x�N�g�������߂�
	SPvec = Vector3Math::Normalize(SPvec);				//�x�N�g���̐��K��
	Vector3 velocity(
		SPvec.x * kBulletSpeed,
		SPvec.y * kBulletSpeed,
		SPvec.z * kBulletSpeed); //�x�N�g���̒������A�����ɍ��킹��

	//���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
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
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransforms_.translation_, velocity);

	//�e��o�^����
	bullets_.push_back(std::move(newBullet));

}

Vector3 Enemy::GetWorldPosition() 
{
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�ړ��������擾
	worldPos.x = worldTransforms_.translation_.x;
	worldPos.y = worldTransforms_.translation_.y;
	worldPos.z = worldTransforms_.translation_.z;

	return worldPos;
}

void Enemy::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransforms_, viewProjection, textureHandle_);
	//�e�`��
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}












