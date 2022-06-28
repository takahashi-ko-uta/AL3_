#pragma once
#include "Model.h"
#include "WorldTransform.h"

class PlayerBullet {
  public:
	/// <summary>
	///������
	/// </summary>
	/// <param name = "model">���f��</param>
	/// <param name = "position">�������W</param>
	void Initialize(Model* model, const Vector3& position,const Vector3& velocity);

	/// <summary>
	///�X�V
	/// </summary>
	void Update();

	/// <summary>
	///�X�V
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

	bool IsDead() const { return isDead_; }
  private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0;
	//���x
	Vector3 velocity_;
	//����
	static const int32_t kLifeTime = 60 * 5;
	//�f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;
	//�f�X�t���O
	bool isDead_ = false;

};