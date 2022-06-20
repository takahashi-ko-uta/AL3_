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
	void Initialize(Model* model, const Vector3& position);

	/// <summary>
	///�X�V
	/// </summary>
	void Update(WorldTransform worldTransform);

	/// <summary>
	///�X�V
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

  private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0;
};